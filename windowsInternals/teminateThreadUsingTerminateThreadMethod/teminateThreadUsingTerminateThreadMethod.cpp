// teminateThreadUsingTerminateThreadMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

DWORD exitCode;
HANDLE myHandle;

DWORD WINAPI terminateThreadHere(LPVOID lpParam) {
	cout << "You have reached here to terminate the thread using terminateThread API" << endl;
	TerminateThread(myHandle, exitCode);
	return 0;
}


int main()
{
	unsigned int counter = 0;
	DWORD threadId;

	 myHandle = CreateThread(
		NULL,
		0,
		terminateThreadHere,
		&counter,
		0,
		&threadId
	);

	if (!myHandle) {
		cout << "Thread cannot be created due to an error: " << GetLastError() << endl;
	}
	else {
		if (!GetExitCodeThread(myHandle, &exitCode)) {
			cout << "Cannot get the exit code of the thread: " << GetLastError() << endl;
		}
		else {
			WaitForSingleObject(myHandle, INFINITE);
			cout << "Exit code of the terminated thread is : " << exitCode << endl;
		}
	}

	CloseHandle(myHandle);
	return 0;
}
