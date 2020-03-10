// threadExit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
using namespace std;


DWORD WINAPI exitThread(LPVOID lpParam) {
    cout << "Hey there, you have reached here to terminate the thread." << endl;
    exitThread(lpParam);
    return 0;
}


int main()
{
    unsigned int counter = 0;
    DWORD threadId;

    HANDLE myHandle = CreateThread(
        NULL,
        0,
        exitThread,
        &counter,
        0,
        &threadId
    );
}
