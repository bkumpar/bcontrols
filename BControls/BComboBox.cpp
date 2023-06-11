
#include "stdafx.h"
#include "BComboBox.h"
#include "BEvent.h"
#include <windowsx.h>

BComboBox::BComboBox(void): BVisualControl() 
{
}

BComboBox::BComboBox( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BComboBox::~BComboBox(void)
{
}

HWND BComboBox::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		L"COMBOBOX",	
		text.c_str() ,
		WS_TABSTOP|WS_VISIBLE|WS_CHILD|CBS_DROPDOWN,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}

void BComboBox::addItem(std::wstring text)
{
	HWND hWnd = this->hWnd();
	ComboBox_AddString( hWnd, text.c_str());
}