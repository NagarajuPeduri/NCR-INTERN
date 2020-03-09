#include<Windows.h>
#include<iostream>
#include<tchar.h>

using namespace std;

int _tmain(int argc, WCHAR* argv[], WCHAR* env[])
{
	STARTUPINFO startUpInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startUpInfo, sizeof(startUpInfo));
	ZeroMemory(&processInfo, sizeof(processInfo));
	startUpInfo.cb = sizeof(startUpInfo);

	BOOL status = 0;

	status = CreateProcess(
		L"C:\\Program Files (x86)\\Notepad++\\notepad++.exe",		//Actual applciation name
		NULL,		//application name using command line arguments
		NULL,		//security attribute for inheriting process by child process
		NULL,		//security attribute for inheriting thread by child process
		FALSE,
		0,
		NULL,		//inherit parent process environemnt
		NULL,		//inherit parent process directory
		&startUpInfo,
		&processInfo
	);

	if (status == 0) {
		cout << "The process creation has failed due to: " << GetLastError() << endl;
	}
	else {
		WaitForSingleObject(processInfo.hProcess, INFINITE);

		cout << "Process details:\n";
		cout << "Current process ID: " << GetCurrentProcessId()<<"  |  Current thread ID: " << GetCurrentThreadId() <<"\n\n";
		cout << "Child Process ID: " << GetProcessId(processInfo.hProcess) << endl << "Child Thread ID: " << GetThreadId(processInfo.hThread) << endl;
		//cout << processInfo.dwProcessId << " " << processInfo.dwThreadId;
		cout << "Process ID of child process thread: " << GetProcessIdOfThread(processInfo.hThread) << endl;		//should be same as child process id
	}

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

	return 0;
}

