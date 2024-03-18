#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <vector>
#include <thread>
#include <atomic>

class SocketServer {
public:
    SocketServer(const std::string& socketPath);
    ~SocketServer();

    void run();
    static int server_fd;

private:
    std::string socketPath;
    std::vector<std::thread> threads;

    void setupSocket();
    void handleClient(int client_socket);
};

#endif // SOCKET_H
