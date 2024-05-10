#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void Interactwithclient(SOCKET clientSocket, vector<SOCKET>& clients) {
    cout << "client connected" << endl;
    //send//recieve
    char buffer[4096];
    while (1) {
        int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesrecvd <= 0) {
            cout << "client disconnected" << endl;
            break;
        }
        string message(buffer, bytesrecvd);
        cout << "message from client : " << message << endl;
        for (auto client : clients) {
            if (client != clientSocket) {
                send(client, message.c_str(), message.length(), 0);
            }
        }
    }

    auto it = find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    closesocket(clientSocket);
}

int main() {
    //initialize winsock library
    if (!Initialize()) {
        cout << "winsock initialization failed" << endl;
        return 1;
    }

    //create the socket
    SOCKET listensocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listensocket == INVALID_SOCKET) {
        cout << "socket creation failed" << endl;
        WSACleanup();
        return 1;
    }

    //get ip and port
    //create addr structure
    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    //convert the ip addr to binary format (0.0.0.0)
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
        cout << "setting address structure failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }

    //bind the ip/port with the socket
    if (bind(listensocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "bind failed " << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }

    //listen
    if (listen(listensocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(listensocket);
        WSACleanup();
        return 1;
    }
    cout << "server has started listening " << port << endl;
    vector<SOCKET> clients;
    while (1) {
        //accept
        SOCKET clientSocket = accept(listensocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cout << "INVALID SOCKET" << endl;
        }
        clients.push_back(clientSocket);

        thread t1(Interactwithclient, clientSocket, std::ref(clients)); 
        t1.detach();
    }

    //receive and send
    closesocket(listensocket);

    //clean up the winsock
    WSACleanup();
    return 0;
}
