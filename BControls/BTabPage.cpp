
#include "StdAfx.h"
#include "BTabPage.h"
#include "BTabControl.h"
#include <vector>

BTabPage::BTabPage()
	: BVisualControl()
{


}
BTabPage::~BTabPage()
{


}


BTabPage::BTabPage(BTabControl* tabControl, std::wstring text, int index)
	: BVisualControl(tabControl)
{
	int width = tabControl->width()-20;
	int height = tabControl->height()-60;
	int left = 10;
	int top = 40;
	_hWnd = createControl(tabControl->hWnd(), text, left, top, width, height);
	TCITEM tabItem;
	ZeroMemory( &tabItem, sizeof(tabItem) );
	tabItem.mask = TCIF_TEXT;
	tabItem.dwState = 0;
	tabItem.dwStateMask = 0;
	tabItem.pszText = (LPWSTR)text.c_str();
	tabItem.cchTextMax = (int)text.length();
	tabItem.iImage = -1;
	tabItem.lParam = NULL;
	_index = index;
	_tabControl = tabControl;
	TabCtrl_InsertItem( _tabControl->hWnd(), _index, &tabItem);
}


void BTabPage::setText(std::wstring text)
{
	TCITEM tabItem;
	ZeroMemory( &tabItem, sizeof(tabItem) );
	tabItem.mask = TCIF_TEXT;
	tabItem.dwState = 0;
	tabItem.dwStateMask = 0;
	tabItem.pszText = (LPWSTR)text.c_str();
	tabItem.cchTextMax = (int)text.length();
	tabItem.iImage = -1;
	tabItem.lParam = NULL;
	TabCtrl_SetItem(  _tabControl->hWnd(),  _index,   &tabItem);
}

std::wstring BTabPage::text()
{
	std::vector<wchar_t> bufText( MAX_PATH );
	size_t cchTextMax = 255; 
	TC_ITEM tabItem;
	ZeroMemory( &tabItem, sizeof(tabItem) );
	tabItem.mask = TCIF_TEXT;
	tabItem.dwState = 0;
	tabItem.dwStateMask = 0;
	tabItem.pszText =  &bufText[0];
	tabItem.cchTextMax = (int)cchTextMax;
	tabItem.iImage = -1;
	tabItem.lParam = NULL;
	TabCtrl_GetItem(   _tabControl->hWnd(),   _index,   &tabItem);
	return std::wstring(&bufText[0]);
}

int BTabPage::index()
{
	return 0;
}

HWND BTabPage::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
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
	return hWnd;}
