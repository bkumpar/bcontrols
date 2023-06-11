
#include "stdafx.h"
#include "BCheckBox.h"
#include "BEvent.h"
#include <windowsx.h>

BCheckBox::BCheckBox(void): BVisualControl() 
{
}

BCheckBox::BCheckBox( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BCheckBox::~BCheckBox(void)
{

}

void BCheckBox::setState(CheckBoxState state)
{

}

BCheckBox::CheckBoxState BCheckBox::state()
{

}


void BCheckBox::setChecked(bool value)
{
	Button_SetCheck(hWnd(), value ? BST_CHECKED : BST_UNCHECKED);
}


bool BCheckBox::checked()
{
	return (Button_GetCheck(hWnd()) == BST_CHECKED);
}

HWND BCheckBox::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		L"BUTTON",	
		text.c_str() ,
		WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}
