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
		NULL,		//Actual applciation name
		argv[1],	//application name using command line arguments
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
		cout << "\n ------------------------ Called command prompt application ----------------------------\n\n\n";
		WaitForSingleObject(processInfo.hProcess, INFINITE);

		cout << "\nProcess details:\n";
		cout << "Process ID: " << processInfo.dwProcessId << endl << "Thread ID: " << processInfo.dwThreadId << endl;
	}

	

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);

	return 0;
}

