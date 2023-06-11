#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"
#include "BMainMenu.h"
#include "BStatusBar.h"

static void * _thisForm;

IMPORT_EXPORT class BForm : public BVisualControl
{
public:
	typedef void (BForm::*CloseHandler)(void*, CancelEventArguments &e);

	BForm();

	BForm(HINSTANCE hInstance, int nCmdShow, 
			HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName );
	BForm(BVisualControl* parent, HINSTANCE hInstance, int nCmdShow, 
			HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName );
	virtual ~BForm(void);

	void show();

	void setClassName(std::wstring className);
	std::wstring className(void);

	LONG clientWidth();
	LONG clientHeight();

	BMainMenu* createMainMenu();
	BStatusBar* createStatusBar(int panels);
	virtual void close();

	void setCloseEventHandler(void* target, CloseHandler handler);

protected:

	 void destroy();
	 void close( CancelEventArguments& e);
private:
	
	HINSTANCE _hInstance;
	std::wstring _className;	
	ATOM RegisterClass(HINSTANCE hInstance);
	static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK realWndProc(HWND, UINT, WPARAM, LPARAM);
	BOOL createControl(BVisualControl* parent, HINSTANCE hInstance, int nCmdShow);
	HICON _icon;
	HICON _iconSmall;
	HCURSOR _cursor;
	LPCWSTR _menuName;
	BMainMenu * _mainMenu;
	BStatusBar* _statusBar;
	HBRUSH _hbrBkgnd;
	CloseHandler _closeHandler;
	void * _closeTarget;


};

