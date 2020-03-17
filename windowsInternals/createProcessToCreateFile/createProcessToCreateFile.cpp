// createProcessToCreateFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//this process creates a file and passes the handle of created file to other file to write something.

#include <iostream>
#include <Windows.h>
#include <tchar.h>
using namespace std;

int main()
{
    //creating a file.
    HANDLE fileHandle = CreateFile(
        L"C:\\Users\\np185137\\fuel.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        cout << "file creation has failed due to an error: " << GetLastError() << endl;
        CloseHandle(fileHandle);
        return 0;
    }

    //creating a process which writes something into the file created. 
    STARTUPINFO startInfo;
    PROCESS_INFORMATION processInfo;
    SECURITY_ATTRIBUTES secAtt;

    secAtt.bInheritHandle = TRUE;
    secAtt.lpSecurityDescriptor = NULL;
    secAtt.nLength = sizeof(secAtt);

    ZeroMemory(&startInfo, sizeof(startInfo));
    ZeroMemory(&processInfo, sizeof(processInfo));
    startInfo.cb = sizeof(startInfo);
    BOOL status = 0;

    //status = CreateProcess()
    status = CreateProcess(
        L"C:\\Users\\np185137\\Documents\\NCR work\\NCR-INTERN\\windowsInternals\\Debug\\createProcessToWriteFile.exe",

    );
}
