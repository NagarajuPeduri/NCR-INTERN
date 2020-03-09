// createTwoProcesses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

int main()
{
    STARTUPINFO startInfo, startInfo1;
    PROCESS_INFORMATION processInfo1, processInfo2;

    ZeroMemory(&startInfo, sizeof(startInfo));          //flusing memory
    ZeroMemory(&processInfo1, sizeof(processInfo1));
    startInfo.cb = sizeof(startInfo);

    ZeroMemory(&startInfo1, sizeof(startInfo1));        //flusing memory
    ZeroMemory(&processInfo2, sizeof(processInfo2));
    startInfo1.cb = sizeof(startInfo1);

    BOOL status = 0;

    //creating a child process for notepad
    status = CreateProcess(
        L"C:\\Windows\\System32\\notepad.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startInfo,
        &processInfo1
    );

    if (status == 0) {
        cout << "Cannot open notepad due to error: " << GetLastError() << endl;
    }
    status = 0;

    WaitForSingleObject(processInfo1.hProcess, INFINITE);       // waiting till the child process of notepad is executed. 

    //creating a child process for calculator
    status = CreateProcess(
        L"C:\\Windows\\System32\\calc.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &startInfo1,
        &processInfo2
    );

    if (status == 0) {
        cout << "Cannot open calculator due to error: " << GetLastError() << endl;
    }

    WaitForSingleObject(processInfo2.hProcess, INFINITE);       //waiting till the child process of calculator is executed. 

    cout << "\nProcess details of notepad:\n" << "Process ID: " << processInfo1.dwProcessId << "  |  Thread ID: " << processInfo1.dwThreadId << "\n\n";
    cout << "Process details of calculator:\n" << "Process ID: " << processInfo2.dwProcessId << "  |  Thread ID: " << processInfo2.dwThreadId << endl;
 
    CloseHandle(processInfo1.hProcess);
    CloseHandle(processInfo1.hThread);

    CloseHandle(processInfo2.hProcess);
    CloseHandle(processInfo2.hThread);
}


