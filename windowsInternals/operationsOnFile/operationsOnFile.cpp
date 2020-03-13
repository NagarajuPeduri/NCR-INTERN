// operationsOnFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
using namespace std;
#define BUFFERSIZE 4096

int main()
{
    HANDLE fileHandle;
    fileHandle = CreateFile(L"C:\\Users\\np185137\\Desktop\\NCR documents\\fuel.txt",
        GENERIC_ALL,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    if (fileHandle == INVALID_HANDLE_VALUE) {
        cout << "File handler initialization failed due to an error : " << GetLastError() << endl;
    }
    else {
        cout << "File has be created successfully!" << endl;
        string toWrite;
        cout << "Enter data to write into the file: " << endl;
        getline(cin, toWrite);
        BOOL status;
        DWORD len = 0;

        status = WriteFile(
            fileHandle,
            toWrite.c_str(),
            toWrite.size()+1,
            &len,
            NULL
        );

        if (!status) {
            cout<<"Could not write the content into the file due to an error: " << GetLastError() << endl;
        }
        else {
            WCHAR read[100];
            LPVOID st;
            DWORD noOfBytesRead = 0;
            BOOL status;

            status = ReadFile(
                fileHandle,
                read,
                toWrite.size() + 1,
                &noOfBytesRead,
                NULL
            );

            if (!status) {
                cout << "Could not read the content of the file due to an error: " << GetLastError() << endl;
            }
            else {
                _tprintf(_T("The content in the file are: %s"), read);
            }
        }

    }
    CloseHandle(fileHandle);
    return 0;
}
