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
    fileHandle = CreateFile(L"C:\\Users\\np185137\\fuel.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
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

        //writing into the file
        status = WriteFile(
            fileHandle,
            toWrite.c_str(),
            toWrite.length(),
            &len,
            NULL
        );

        if (!true) {
            cout<<"Could not write the content into the file due to an error: " << GetLastError() << endl;
        }
        else {
            //READING   
            WCHAR read1[BUFFERSIZE];
            ZeroMemory(read1, BUFFERSIZE);
            LPVOID st;
            DWORD noOfBytesRead = 0;
            BOOL status;

            //move the file pointer to beginning. 
            SetFilePointer(
                fileHandle,
                NULL,
                NULL,
                0
            );

            //reading from the file
            status = ReadFile(
                fileHandle,
                read1,
                BUFFERSIZE,
                &noOfBytesRead,
                NULL
            );

            if (!status) {
                cout << "Could not read the content of the file due to an error: " << GetLastError() << endl;
            }
            else {
                _tprintf(_T("The content in the file are: %S"), read1);
            }
        }

    }
    CloseHandle(fileHandle);
    return 0;
}
