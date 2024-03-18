#include "server.hpp"

#include <iostream>
#include <cstring>
#include <csignal>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <algorithm>
#include <array>


std::atomic<bool> running(true);

int SocketServer::server_fd = -1;

SocketServer::SocketServer(const std::string& socketPath) : socketPath(socketPath) {
    setupSocket();
}

SocketServer::~SocketServer() {
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
    close(server_fd);
    unlink(socketPath.c_str());
}

void SocketServer::run() {
    while (running) {
        int client_socket = accept(server_fd, NULL, NULL);
        if (client_socket < 0) {
            if (!running) {
                std::cout << "Server shutting down..." << std::endl;
                break;
            }
            perror("accept");
            continue;
        }
        threads.emplace_back(&SocketServer::handleClient, this, client_socket);
    }
}

void SocketServer::setupSocket() {
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, socketPath.c_str());

    unlink(socketPath.c_str());

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on " << socketPath << std::endl;
}

void SocketServer::handleClient(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);
    std::string command(buffer);

    if (command == "VERSION") {
        std::string git_version = getCurrentGitCommit();
        send(client_socket, git_version.c_str(), git_version.size(), 0);
    } else {
        std::string msg = "REJECTED";
        send(client_socket, msg.c_str(), msg.size(), 0);
    }

    close(client_socket);
}


std::string SocketServer::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string SocketServer::getCurrentGitCommit() {
    try {
        std::string gitCommitHash = exec("git rev-parse HEAD");
        // Remove the newline character at the end of the hash
        gitCommitHash.erase(std::remove(gitCommitHash.begin(), gitCommitHash.end(), '\n'), gitCommitHash.end());
        return gitCommitHash;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error getting current Git commit: " << e.what() << std::endl;
        return "";
    }
}