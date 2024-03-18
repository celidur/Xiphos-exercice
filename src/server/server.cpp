#include "server.hpp"

#include <iostream>
#include <cstring>
#include <csignal>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

const std::string VERSION = "3cdd5d19178a54d2e51b5098d43b57571241d0ab"; // Example git version
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
        send(client_socket, VERSION.c_str(), VERSION.size(), 0);
    } else {
        std::string msg = "REJECTED";
        send(client_socket, msg.c_str(), msg.size(), 0);
    }

    close(client_socket);
}
