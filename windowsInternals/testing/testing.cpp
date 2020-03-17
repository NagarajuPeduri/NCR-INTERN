// threadCreation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include<string>
using namespace std;

struct node {
    int age;
    string name;
};

DWORD WINAPI myFun(LPVOID lpParam) {
    node c = *(node*)lpParam;
    cout << c.age<< " " << c.name << endl;
    cout << "Hey there!, a new thread has been created.\n";
    return 0;
}

int main()
{
    unsigned int counter = 10;
    node var;

    var.age = 22;
    var.name = "akhil";

    DWORD threadId;

    HANDLE myHandle = CreateThread(
        NULL,       //whether the returned can be inherited by child process
        0,          //stack size, 0 indicates that the thread uses the default size for the executable
        myFun,      //starting address of the thread (callback function)
        &var,   //lpParameter ( which is to be passed to the thread)
        0,          //flags that control the creation of thread.    
        &threadId   //A pointer to the variable that receives thread identifier. 
    );

    if (myHandle == 0) {        //if myHandle is 0, then the thread creation is failed. 
        cout << "Thread creation has failed due to error: " << GetLastError() << endl;
    }
    else {
        WaitForSingleObject(myHandle, 10);
    }

    CloseHandle(myHandle);
    return 0;
}

