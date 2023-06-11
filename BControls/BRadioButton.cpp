#include "StdAfx.h"
#include "BRadioButton.h"
#include "ExportImport.h"
#include "BVisualControl.h"

BRadioButton::BRadioButton(void)
{


}

BRadioButton::BRadioButton( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}


HWND BRadioButton::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		L"BUTTON",	
		text.c_str() ,
		WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_RADIOBUTTON,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}
BRadioButton::~BRadioButton(void)
{


}

//void BRadioButton::setBackgroundColor(COLORREF color)
//{
//	_backgroundColor = color;
//}
