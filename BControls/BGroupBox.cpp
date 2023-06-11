#include "stdafx.h"
#include "BGroupBox.h"

BGroupBox::BGroupBox(void) : BVisualControl()
{
}

BGroupBox::BGroupBox( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	:BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);	
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}


BGroupBox::~BGroupBox(void)
{
}

HWND BGroupBox::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height )
{
    HWND hWnd = CreateWindowEx( NULL
	        , L"BUTTON"
			, text.c_str()
			, BS_GROUPBOX | WS_VISIBLE | WS_CHILD | WS_GROUP 
			, left, top, width, height
			, hwndParent
			, (HMENU) _id
			, /*hInstance = GetModuleHandle(NULL)  */
			(HINSTANCE) GetWindowLongPtr(hwndParent, GWLP_HINSTANCE)
			, NULL
		);
	return hWnd;
}  
