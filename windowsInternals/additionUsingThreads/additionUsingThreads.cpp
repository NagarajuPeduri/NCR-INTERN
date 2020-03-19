// additionUsingThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int a, b;


DWORD WINAPI reading(LPVOID lpParam) {
    cout << "In thread 1\nEnter two values" << endl;
    cin >> a >> b;
    return 0;
}


DWORD WINAPI adding(LPVOID lpParam) {
    cout << "\nAfter addition:\n" << a + b << endl;
    return 0;
}


int main()
{
    HANDLE tHandle[2];
    DWORD tID1, tID2;

   //creating thread for reading
    tHandle[0] = CreateThread(
        NULL,
        0,
        reading,
        NULL,
        0,
        &tID1
    );
    WaitForSingleObject(tHandle[0], INFINITE);

    //creating tread for adding
    tHandle[1] = CreateThread(
        NULL,
        0,
        adding,
        NULL,
        0,
        &tID2
    );
    WaitForSingleObject(tHandle[1], INFINITE);

    CloseHandle(tHandle[0]);
    CloseHandle(tHandle[1]);

    return 0;
}
