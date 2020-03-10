// inheritHandleByChildProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	BOOL processStatus;
	PROCESS_INFORMATION processInfo;
	STARTUPINFO startInfo;
	SECURITY_ATTRIBUTES secAtt;

	secAtt.bInheritHandle = TRUE;		//allow inheritance
	secAtt.lpSecurityDescriptor = NULL;
	secAtt.nLength = sizeof(secAtt);

	ZeroMemory(&startInfo, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));
	
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
		cout << "Child Process Details:\nProcess ID: " << GetProcessId(processInfo.hProcess) << "  |  Thread ID: " << GetThreadId(processInfo.hThread) << endl;
	}

	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);

	return 0;
}
