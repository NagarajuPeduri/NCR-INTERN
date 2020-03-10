// threadExit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
using namespace std;

DWORD exitCode;

DWORD WINAPI exitThread(LPVOID lpParam) {
    cout << "Hey there, you have reached here to terminate the thread using ExitThread api." << endl;
    ExitThread(exitCode);       //terminate the thread using exitCode.
}


int main()
{
    unsigned int counter = 0;
    DWORD threadId;
    //DWORD exitCode = 0;

    HANDLE myHandle = CreateThread(
        NULL,       //allow returned handle inherit by child process.
        0,          //stack size
        exitThread, //callback funtion(start function).
        &counter,   //lpparameter, which is used as parameter in callback function.
        0,
        &threadId
    );

    if (myHandle == 0) {
        cout << "Thread creation failed due to error: " << GetLastError() << endl;
    }
    else {
       // WaitForSingleObject(myHandle, INFINITE);
        if (!GetExitCodeThread(myHandle, &exitCode)) {    //First get the exit code of the thread. Using this, terminate the thread in its callback function. 
            cout << "Cannot get the thread exit code due to the error: " << GetLastError() << endl;
        }
        else{
            WaitForSingleObject(myHandle, 100);
            cout << exitCode;
        }      
    }

    CloseHandle(myHandle);
    return 0;
}
