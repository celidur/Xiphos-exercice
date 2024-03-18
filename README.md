# C++ Client-Server Application

This is a simple client-server application written in C++.

## Prerequisites

- A Linux-based operating system 
- `g++` for compiling C++ code. version 12.2 or later.
- `make` for automating the build process. version 4.1 or later.
- no third-party/additional setup is required.
## Application Structure

- Server:
    - `server.cpp`, `server.h`: : Server class definition and implementation.
    - `ServerMain.cpp`: Main function to start the server.
- Client:
    - `client.cpp`, `client.h`: Client class definition and implementation.
    - `ClientMain.cpp`: Main function to start the client.
- `Makefile`: Automates the build process.

## Build and Run

### Build the Application:

```bash
make
```

### Run the Server:

In a terminal, run the server with the following command:

```bash
./server <socket_path>
```

you can stop the server by pressing `Ctrl+C`.

### Run the Client:

In another terminal, run the client with the following command:

```bash
./client <socket_path> <message>
```

where `<socket_path>` is the path to the server socket and `<message>` is the message to send to the server.

if the message is `VERSION`, the server will return the version of the server. Else, the server will return `REJECTED`

