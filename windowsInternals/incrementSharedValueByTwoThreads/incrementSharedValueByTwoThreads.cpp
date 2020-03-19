// incrementSharedValueByTwoThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;
int sharedVal = 0;


DWORD WINAPI t1CallBack(LPVOID lpParam) {
    //cout << "Incremented shared value in thread 1" << endl;
    sharedVal++;
    return 0;
}


DWORD WINAPI t2CallBack(LPVOID lpParam) {
    //cout << "Incremented shared value in thread 2" << endl;
    sharedVal++;
    return 0;
}


int main()
{
    HANDLE th1, th2;
    DWORD t1ID, t2ID;
    int c1, c2;

    //creating thread 1
    th1 = CreateThread(
        NULL,
        0,
        t1CallBack,
        &c1,
        0,
        &t1ID
    );

    WaitForSingleObject(th1, 10);

    //creating thread 2
    th2 = CreateThread(
        NULL,
        0,
        t2CallBack,
        &c2,
        0,
        &t2ID
    );
    
    for (int i = 0; i < 10; i++)cout << "";

    cout << "In main thread, shared value is: " << sharedVal << endl;

    CloseHandle(th1);
    CloseHandle(th2);
    return 0;
}
