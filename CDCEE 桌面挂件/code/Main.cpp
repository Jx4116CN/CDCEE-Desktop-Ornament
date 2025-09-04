#include "Init.h"

#undef main

int main()
{
	HANDLE mutex = CreateMutex(NULL, FALSE, (const WCHAR*)TITLE);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, L"程序已经在运行中！", L"提示", MB_OK | MB_ICONWARNING);
		CloseHandle(mutex);
		return ERROR_ALREADY_EXISTS;
	}

	//Save_cfg();
	Init_main();
	show_main();

	Quit();

	return 0;
}