// inheritHandleByChildProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	BOOL processStatus;
	PROCESS_INFORMATION processInfo, processInfo1;
	STARTUPINFO startInfo, startInfo1;
	SECURITY_ATTRIBUTES secAtt;

	secAtt.bInheritHandle = TRUE;		//allow inheritance
	secAtt.lpSecurityDescriptor = NULL;
	secAtt.nLength = sizeof(secAtt);

	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));

	ZeroMemory(&startInfo1, sizeof(startInfo1));
	startInfo1.cb = sizeof(startInfo1);
	ZeroMemory(&processInfo1, sizeof(processInfo1));
	
	//process creation
	processStatus = CreateProcess(
		L"C:\\Windows\\System32\\notepad.exe",
		NULL,
		&secAtt,
		NULL,
		TRUE,		//Allow inheritance
		0,
		NULL,
		NULL,
		&startInfo,
		&processInfo
	);

	if (processStatus == 0) {
		cout << "Process creation failed due to: " << GetLastError() << endl;
	}
	else {
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		cout << "Notepad process Details:\nProcess ID: " << GetProcessId(processInfo.hProcess) << "  |  Thread ID: " << GetThreadId(processInfo.hThread) << endl;
	}

	WCHAR handle[] = { (WCHAR)processInfo.hProcess };


	processStatus = CreateProcess(
		L"C:\\Windows\\System32\\calc.exe",
		handle,			//inherits the parent handle
		&secAtt,
		NULL,
		FALSE,		//doesn't allow inheritance
		0,
		NULL,
		NULL,
		&startInfo1,
		&processInfo1
	);

	if (processStatus == 0) {
		cout << "Process creation failed due to: " << GetLastError() << endl;
	}
	else {
		WaitForSingleObject(processInfo1.hProcess, INFINITE);
		cout << "\nalc process Details:\nProcess ID: " << GetProcessId(processInfo1.hProcess) << "  |  Thread ID: " << GetThreadId(processInfo1.hThread) << endl;
	}

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo1.hThread);
	CloseHandle(processInfo1.hProcess);

	return 0;
}
