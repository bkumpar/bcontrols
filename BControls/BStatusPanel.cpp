
#include "stdafx.h"
#include "BStatusPanel.h"


BStatusPanel::BStatusPanel(void): BVisualControl() 
{
}

BStatusPanel::BStatusPanel( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}

BStatusPanel::~BStatusPanel(void)
{
}

HWND BStatusPanel::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx( NULL,	
		STATUSCLASSNAME,	// ComCtrl.h
		text.c_str() ,
		WS_VISIBLE|WS_CHILD|SBARS_SIZEGRIP,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}