//
// BControlsDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <BApplication.h>
#include "MainForm.h"
HINSTANCE hInst;								// current instance



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	BApplication app;
    HICON icon  = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BCONTROLS_TEST));
	HICON iconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	LPCWSTR menuName =  NULL ; 
	MainForm* mainForm = new MainForm(hInstance, nCmdShow, icon, iconSmall, cursor, menuName);
	mainForm->show();
	return app.run();
}



