// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI myThreadFun(LPVOID lpParameter) {
    for (int i = 0; i < 10; i++) {
        cout << i <<" " << endl;
    }
    return 0;
}

int main()
{
    unsigned int counter = 0;
    DWORD threadId;
    HANDLE myHandle = CreateThread(
        NULL,
        0,
        myThreadFun,
        &counter,
        0,
        &threadId
    );

    /*for (int i = 10; i < 20; i++) {
        cout << i << " " << endl;
    }*/

    WaitForSingleObject(myHandle, 1);

    cout << "Thread id is : " << threadId << endl;
    
    CloseHandle(myHandle);
    return 0;
}
