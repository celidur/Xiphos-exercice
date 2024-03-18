#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class SocketClient {
public:
    SocketClient(const std::string& socketPath);
    void sendMessage(const std::string& message);

private:
    void connectToServer();
    
    std::string socketPath;
    int sock;
};

#endif // SOCKET_H
