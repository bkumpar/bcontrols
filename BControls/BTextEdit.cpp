#include "stdafx.h"
#include "BTextEdit.h"


BTextEdit::BTextEdit(void)
{
}

BTextEdit::BTextEdit(BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	:BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);

}
BTextEdit::~BTextEdit()
{
}

HWND BTextEdit::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height )
{
	HWND hWnd = CreateWindowEx(WS_EX_CLIENTEDGE
			, L"EDIT"   
            , text.c_str()  
            , WS_CHILD | WS_VISIBLE | ES_LEFT |/* WS_BORDER |*/ WS_TABSTOP | ES_AUTOHSCROLL
			 /*| WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL*/ 
            , left, top, width, height   
            , hwndParent         
            , (HMENU) id()   
            , GetModuleHandle(NULL) 
            , NULL  
		);       
	return hWnd;
}

void BTextEdit::click()
{
	if(_clickHandler)
	{
		EventArguments e;
		(this->*_clickHandler)(this, e);
	}
}

//void BTextEdit::setEventHandler(OnClickHandlerType e)
//{
//	_onClickHandler = e;
//}


void BTextEdit::setMultiline(bool flag)
{
	return;
}

bool BTextEdit::multiline()
{
	return false;
}
