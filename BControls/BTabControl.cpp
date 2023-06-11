
#include "stdafx.h"
#include "BTabControl.h"
#include "BTabPage.h"
#include "BEvent.h"


BTabControl::BTabControl(void)
{


}

BTabControl::BTabControl( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;

}

HWND BTabControl::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icex);

    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
			WC_TABCONTROL,	
			text.c_str() ,
			WS_TABSTOP|WS_VISIBLE|WS_CHILD,
			left, top, width, height,
			hwndParent,
			(HMENU) _id,
			hInst,
			NULL
	);
	return hWnd;

}

BTabControl::~BTabControl(void)
{


}

BTabPage * BTabControl::addPage(std::wstring text, int index)
{

	return new BTabPage(this, text, index);
}

BTabPage * BTabControl::page(int index)
{


}

void BTabControl::removePage(int index)
{
	TabCtrl_DeleteItem(this->hWnd(), index);
}


void BTabControl::removePage(BTabPage* tabPage)
{
	TabCtrl_DeleteItem(tabPage->_tabControl->hWnd(), tabPage->_index);
	
}