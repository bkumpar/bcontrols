#include "stdafx.h"
#include "BStaticText.h"


BStaticText::BStaticText(void)
{
}

BStaticText::BStaticText( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	:BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}


BStaticText::~BStaticText(void)
{
}

HWND BStaticText::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height )
{
    HWND hWnd = CreateWindowEx( NULL
	        , L"STATIC"
			, text.c_str()
			, WS_CHILD | SS_NOTIFY|  WS_VISIBLE  
			, left, top, width, height
			, hwndParent
			, (HMENU) id()
			, GetModuleHandle(NULL) 
			, NULL
		);
	return hWnd;
}  


//void BStaticText::setBackgroundColor(COLORREF color)
//{
//	_backgroundColor = color;
//}
