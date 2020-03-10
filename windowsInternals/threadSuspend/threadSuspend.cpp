// threadSuspend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI myFun(LPVOID lpParam) {
    Sleep(5000);        //suspend the thread for 5 sec
    for (int i = 0; i < 1000; i++) {
        cout << i << " ";
    }
    return 0;
}

int main()
{
    DWORD threadId;
    unsigned int counter = 0;

    char ch;
    ch = getchar();

    //creating thread
    HANDLE myHandle = CreateThread(
        NULL,
        0,
        myFun,
        &counter,
        0,
        &threadId
    );

    if (myHandle == 0) {
        cout << "Thrad creation failed due to : " << GetLastError() << endl;
    }
    else {
        WaitForSingleObject(myHandle, 5500);
        CloseHandle(myHandle);
    }

    return 0;
}
