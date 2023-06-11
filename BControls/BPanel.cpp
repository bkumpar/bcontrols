#include "StdAfx.h"
#include "BPanel.h"

BPanel::BPanel()
{


}

BPanel::BPanel(BVisualControl* parent)
	: BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(),20, 20, 100, 100);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BPanel::BPanel(BVisualControl* parent, int left, int top, int width, int height)
	: BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(),left, top, width, height);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BPanel::~BPanel()
{

}

HWND BPanel::createControl(HWND hwndParent,  int left, int top, int width, int height)
{
	HINSTANCE hInst= GetModuleHandle(NULL);
	HWND  hWnd = CreateWindow(
		WC_STATIC, 
		L"PANEL", 
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		left, 
		top, 
		width, 
		height,
		hwndParent, 
		NULL, 
		hInst,    
		NULL); 

	if ( hWnd == 0 )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to create window class. Error: " <<  dwError << std::endl;
	}
	Static_Enable( hWnd, TRUE);
	Static_SetText(hWnd, L"STATIC CONTROL");
	return hWnd;
}

