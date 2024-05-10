### Simple C++ Chat Application

This repository contains a simple chat application implemented in C++ using Microsoft Visual Studio Code. The application consists of two main components: a server and a client.

### Features

- **Real-time Communication**: Users can connect to the server and send/receive messages in real-time.
- **Multiple Client Support**: The server supports multiple client connections concurrently, enabling group communication.
- **User-Friendly Interface**: The client provides a user-friendly interface for sending and receiving messages.
- **Error Handling**: The application includes error handling mechanisms to gracefully deal with connection failures and other issues.

### Dependencies

- **WinSock Library**: The application relies on the WinSock library for socket programming on Windows platforms.
- **C++ Standard Library**: Standard C++ libraries are used for threading, input/output, and other functionalities.

### Usage

1. **Server Setup**: Compile and run the server application. It listens for incoming connections from clients.
2. **Client Setup**: Compile and run the client application. Enter the server's IP address and port number to connect.
3. **Chatting**: Once connected, users can send messages to the server, which broadcasts them to all other connected clients.


### Server Setup

The server terminal when it's running and waiting for client connections:

![Server Terminal](https://drive.google.com/file/d/1x0dHWPOQOnuLfZlKHEkhqGUgIaovmSIQ/view?usp=sharing)

### Client Setup

### Chatting

Screenshots of both client terminals engaged in a chat conversation:

- Client1 Terminal:

  ![Client 1 Terminal](https://drive.google.com/file/d/1UIkT8omgdEAz9WGOFsDg-i4OYmuCRNr3/view?usp=sharing)

- Client2 Terminal:

  ![Client 2 Terminal](https://drive.google.com/file/d/1BtEubqDuQxq5tTVkFhFHzY4kTvCH3Bjd/view?usp=sharing)


### Code Structure

- **Server**: The server code (`server.cpp`) handles socket initialization, client connections, and message broadcasting.
- **Client**: The client code (`client.cpp`) manages socket connection to the server, sending and receiving messages.

### How to Compile and Run

```bash
# Server Compilation
g++ server.cpp -o server -lws2_32

# Server Execution
./server

# Client Compilation
g++ client.cpp -o client -lws2_32

# Client Execution
./client


