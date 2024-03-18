#include "client.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <socket_path> <message>" << std::endl;
        return EXIT_FAILURE;
    }

    SocketClient client(argv[1]);
    client.sendMessage(argv[2]);

    return 0;
}
