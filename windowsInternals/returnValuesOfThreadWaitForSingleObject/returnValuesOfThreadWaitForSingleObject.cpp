// returnValuesOfThreadWaitForSingleObject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;


DWORD WINAPI tCallBack1(LPVOID lpParam) {
    cout << "You have created thread 1 successfully" << endl;
    return 0;
}


DWORD WINAPI tCallBack2(LPVOID lpParam) {
    cout << "You have created thread 2 successfully" << endl;
    return 0;
}


DWORD WINAPI tCallBack3(LPVOID lpParam) {
    cout << "You have created thread 3 successfully" << endl;
    Sleep(2000);
    return 0;
}


void returnStatus(unsigned long val) {

    switch (val) {
    case WAIT_ABANDONED: 
        cout << "Thread has been abondoned" << endl;
        break;

    case WAIT_OBJECT_0:
        cout << "The thread has been executed successfully" << endl;
        break;

    case WAIT_TIMEOUT:
        cout << "The thread has exceeded time limit" << endl;
        break;

    case WAIT_FAILED:
        cout << "The execution has failed" << endl;
        break;
    }
}


int main()
{
    HANDLE th1, th2, th3;
    DWORD tid1, tid2, tid3;
    int counter1 = 0, counter2 = 0, counter3 = 0;
    unsigned long t1Return, t2Return, t3Return;

    //creating thread 1
    th1 = CreateThread(
        NULL,
        0,
        tCallBack1,
        &counter1,
        0,
        &tid1
    );
    t1Return = WaitForSingleObject(th1, INFINITE);      // storing the return value
    cout << "Return value of Thread 1 (ID: "<< tid1 <<") with INFINITE time to execute: ";
    returnStatus(t1Return);
    cout << "\n";

    //creating thread 2
    th2 = CreateThread(
        NULL,
        0,
        tCallBack2,
        &counter2,
        0,
        &tid2
    );
    t2Return = WaitForSingleObject(th2, 1000);          // stroing the return value
    cout << "Return value of Thread 2 (ID: " << tid2 << ") with 1sec to execute: ";
    returnStatus(t2Return);
    cout << "\n";

    //creating thread 3
    th3 = CreateThread(
        NULL,
        0,
        tCallBack3,
        &counter3,
        0,
        &tid3
    );
    t3Return = WaitForSingleObject(th3, 1000);          //stroing the return value
    cout << "Return value of Thread 3 (ID: " << tid3 << ") with 1sec to execute along with sleep in call back: ";
    returnStatus(t3Return);
    cout << "\n";

    CloseHandle(th1);
    CloseHandle(th2);
    CloseHandle(th3);
    return 0;
}
