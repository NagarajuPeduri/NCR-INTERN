// treadExitAll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;


DWORD WINAPI th1CallBack(LPVOID lpParam) {
    int time = *(DWORD*)lpParam;
    Sleep(time);
    cout << "Thread 1 with waiting time: " << time << " milli seconds.\n";
    return 0;
}


DWORD WINAPI th2CallBack(LPVOID lpParam) {
    int time = *(DWORD*)lpParam;
    Sleep(time);
    cout << "Thread 2 with waiting time: " << time << " milli seconds.\n";
    return 0;
}


void returnStatus(unsigned long val) {      // checking the return status of waitForMultipleObjects()

    switch (val) {
    case WAIT_ABANDONED_0:
        cout << "Threads has been abondoned with return value: "<<WAIT_ABANDONED_0 << endl;
        break;

    case WAIT_OBJECT_0:
        cout << "The threads has been executed successfully with return value: "<<WAIT_OBJECT_0 << endl;
        break;

    case WAIT_TIMEOUT:
        cout << "The threads has exceeded time limit with return value: "<<WAIT_TIMEOUT << endl;
        break;

    case WAIT_FAILED:
        cout << "The execution has failed with return value: "<<WAIT_FAILED << endl;
        break;
    }
}


void createTheads(BOOL b, int t1WaitTime, int t2WaitTime, int argForWaitCAll) {
    HANDLE th[2];
    DWORD t1ID, t2ID;

    //creating thread 1
    th[0] = CreateThread(
        NULL,
        0,
        th1CallBack,
        &t1WaitTime,    //this parameter to used to suspend the thread. 
        0,
        &t1ID
    );

    //creating thread 2
    th[1] = CreateThread(
        NULL,
        0,
        th2CallBack,
        &t2WaitTime,    //this parameter to used to suspend the thread.
        0,
        &t2ID
    );

    unsigned long val;
    val = WaitForMultipleObjects(2, th, b, argForWaitCAll);
    returnStatus(val);

    CloseHandle(th[0]);
    CloseHandle(th[1]);
}


int main()
{   
    int arr[4][4];      //first coloumn is for bWaitForAll, second coloumn: thread 1 wait time and third coloumn: thread 2 wait time. (time in ms)
    arr[0][0] = 1; arr[0][1] = 0; arr[0][2] = 0; arr[0][3] = INFINITE;
    arr[1][0] = 1; arr[1][1] = 4000; arr[1][2] = 3000; arr[1][3] = INFINITE;
    arr[2][0] = 0; arr[2][1] = 2000; arr[2][2] = 3000; arr[2][3] = INFINITE;
    arr[3][0] = 0; arr[3][1] = 4000; arr[3][2] = 2000; arr[3][3] = 2000;

    for (int ind = 0; ind < 4; ind++) {
        BOOL b = (arr[ind][0] == 1) ? TRUE : FALSE;
        cout << "Call "<<ind+1<<":\nbWaitAll set to : " << b << endl;

        createTheads(b, arr[ind][1], arr[ind][2], arr[ind][3]);      //calling to create two threads. 

        cout << endl;
    }
}
