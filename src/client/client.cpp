#include "client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

SocketClient::SocketClient(const std::string& socketPath)
    : socketPath(socketPath), sock(0) {
    connectToServer();
}

void SocketClient::connectToServer() {
    struct sockaddr_un serv_addr;
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        exit(EXIT_FAILURE);
    }

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, socketPath.c_str());

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SocketClient::sendMessage(const std::string& message) {
    send(sock, message.c_str(), message.size(), 0);
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    std::cout << buffer << std::endl;

    close(sock);
}
