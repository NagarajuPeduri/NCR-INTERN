// socketClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
    string ipAddress = "153.58.141.193";     //ip address of server
    int port = 54000;                   //listening port on the server

    //initialize winsock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0) {
        cerr << "Can't start winsock, Err #" << wsResult << endl;
        return 0;
    }

    //create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr<< "Can't create socket, Err #" << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }

    //fill in the hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //connect to the server
    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 0;

    }

    //do while loop to send and receive data
    char buf[4096];
    string userInput;

    do {
        //promt the user for some text
        cout << "> ";
        getline(cin, userInput);

        if (userInput.size() > 0) {
            //send the text
            int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            if (sendResult != SOCKET_ERROR) {

                //wait for response
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(sock, buf, 4096, 0);

                if (bytesReceived > 0) {
                    //echo response to the console
                    cout << "server> " << string(buf, 0, bytesReceived) << endl;
                }
            }
        }

    } while (userInput.size() > 0);

    //close down everything
    closesocket(sock);
    WSACleanup();
}

