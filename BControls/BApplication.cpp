#include "stdafx.h"
#include "BApplication.h"
#include "BForm.h"

BApplication::BApplication(void)
{
}


BApplication::~BApplication(void)
{
}

int BApplication::run()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}

//HWND  BApplication::showHelp(HWND hwndCaller)
//{
//	std::wstring _helpFile = L"C:\\Users\\Boris\\Documents\\Visual Studio 2010\\Projects\\simple_win_32\\help\\simple_html_help.chm::/Page1.htm";
//	UINT    uCommand = HH_DISPLAY_TOC;
//	DWORD   dwData = NULL;
//	HWND rc =  HtmlHelp(hwndCaller, _helpFile.c_str(), uCommand, dwData);
//	return rc;
//}

void BApplication::setHelpFile(std::wstring helpFile)
{
	_helpFile = helpFile;
}
std::wstring BApplication::helpFile(void)
{
	return _helpFile;
}

