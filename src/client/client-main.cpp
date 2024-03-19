#include "client.hpp"
#include <iostream>
#include <thread>

int main(int argc, char const* argv[]) {
    // argument : <socket_path> <message>
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <socket_path> <message>" << std::endl;
        return EXIT_FAILURE;
    }

    SocketClient client(argv[1]);
    client.sendMessage(argv[2]);

    return 0;
}
