// socketServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main(){
    
    //initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    INT WSOK = WSAStartup(ver, &wsData);
    if (WSOK != 0) {
        cerr << "Can't initialize winsock! quitting" << endl;
        return 0;
    }


    //create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "Cant't create a socket! Quitting" << endl;
        return 0;
    }


    //bind the socket to an ip address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;     //could also use inet_pton ..

    bind(listening, (sockaddr*)&hint, sizeof(hint));


    //tell winsock the socket is for listening
    listen(listening, SOMAXCONN);  


    //wait for connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);       //if(clientSocket == INVALID_SOCKET)
    
    char host[NI_MAXHOST];      //client's remote name
    char service[NI_MAXSERV];   // service (i.e. port) the client is connt on

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        cout << host << " connected on port " << service << endl;
    }
    else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }


    //close listening socket
    closesocket(listening);


    //while loop: accept and echo message back to client
    char buf[4096];
    string userInput;

    while (true) {
        
        ZeroMemory(buf, 4096);

        //wait for the client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << " Error in recv(). Quitting" << endl;
            break;
        }

        if (bytesReceived == 0) {
            cout << "Client disconnected " << endl;
            break;
        }

        cout << "Client> "<<string(buf, 0, bytesReceived) << endl;

        cout << ">";

        getline(cin, userInput);

        //echo msg back to client
        send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
    }


    //close the socket
    closesocket(clientSocket);

    //cleanup winsock
    WSACleanup();

}
