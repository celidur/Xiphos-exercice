#include <iostream>
#include <atomic>
#include <csignal>
#include <sys/socket.h>

#include "server.hpp"

extern std::atomic<bool> running;

void signalHandler([[maybe_unused]] int _signal) {
    running = false;
    // Use shutdown to unblock accept call
    shutdown(SocketServer::server_fd, SHUT_RDWR);
}

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <socket_path>" << std::endl;
        return EXIT_FAILURE;
    }

    // Register signal SIGINT and signal handler
    signal(SIGINT, signalHandler);

    SocketServer server(argv[1]);
    server.run();

    return 0;
}
