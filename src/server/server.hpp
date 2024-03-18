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
    void setupSocket();
    void handleClient(int client_socket);
    std::string exec(const char* cmd);
    std::string getCurrentGitCommit();

    std::string socketPath;
    std::vector<std::thread> threads;
};

#endif // SOCKET_H
