
#include "stdafx.h"
#include "BButton.h"
#include "BEvent.h"

BButton::BButton(void): BVisualControl() 
{
}

BButton::BButton( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BButton::~BButton(void)
{
}

HWND BButton::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		L"BUTTON",	
		text.c_str() ,
		WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}

