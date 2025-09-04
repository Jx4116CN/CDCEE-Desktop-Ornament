#include "Init.h"

#undef main

int main()
{
	HANDLE mutex = CreateMutex(NULL, FALSE, (const WCHAR*)TITLE);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, L"�����Ѿ��������У�", L"��ʾ", MB_OK | MB_ICONWARNING);
		CloseHandle(mutex);
		return ERROR_ALREADY_EXISTS;
	}

	//Save_cfg();
	Init_main();
	show_main();

	Quit();

	return 0;
}