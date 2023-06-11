#include "stdafx.h"
#include "BMenuItem.h"
#include "BMenu.h"
#include "BMainMenu.h"
#include "BPopUpMenu.h"
#include "BForm.h"

BMenuItem::BMenuItem()
{
		
}

BMenuItem::BMenuItem( BMenu* menu,std::wstring text)
	:  _menu(menu), _hMenu (menu->hMenu()), _text(text), BVisualControl(menu->mainMenu()->form())
{
   	AppendMenu( _hMenu, MF_STRING, (UINT_PTR)_id, (LPCWSTR)_text.c_str()); 
	_className = L"BMENUITEM";
	HINSTANCE _hInstance= GetModuleHandle(NULL);
	_menuItemAtom = RegisterMenuItemClass(_hInstance);
	_hWnd = createControl(menu->mainMenu()->form()->hWnd());
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}

//BMenuItem::BMenuItem( BMenuItem* menuItem ,std::wstring text)
//	:  _menu(menuItem->menu()), _hMenu (menuItem->hMenu()), _text(text), BVisualControl(menuItem->menu()->mainMenu()->form())
//{
//   	AppendMenu( _hMenu, MF_STRING, (UINT_PTR)_id, (LPCWSTR)_text.c_str()); 
//	_className = L"BMENUITEM";
//	HINSTANCE _hInstance= GetModuleHandle(NULL);
//	_menuItemAtom = RegisterMenuItemClass(_hInstance);
//	_hWnd = createControl(menuItem->menu()->mainMenu()->form()->hWnd());
//	_idToHandle[_id] = _hWnd;
//	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG)this);
//	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
//}
//

void BMenuItem::setText(std::wstring text)
{
    _flags = _flags | MF_STRING;
}

std::wstring BMenuItem::text()
{
	return _text;
}

void BMenuItem::setIcon(HBITMAP bitmap)
{
    _flags = _flags | MF_BITMAP;
}

HWND BMenuItem::createControl(HWND hwndParent)
{
	std::wstring text = L"BMENUITEM";
	
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		_className.c_str(),	
		text.c_str(),
		0,
		0, 0, 0, 0,
		hwndParent,
		NULL,
		hInst,
		NULL
	);

	if ( !hWnd )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to createControl ." << _className.c_str() << "Error: " <<  dwError << std::endl;
    
	}
	return hWnd;
}

ATOM BMenuItem::RegisterMenuItemClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= dummyWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _className.c_str();
	wcex.hIconSm		= NULL;

	if ( (this-> _menuItemAtom = ::RegisterClassEx( &wcex )) == 0 )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to register window class." << _className.c_str() << "Error: " <<  dwError << std::endl;
    
	}
	return this-> _menuItemAtom;
}

LRESULT CALLBACK BMenuItem::dummyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}


void BMenuItem::setChecked(bool flag)
{
	CheckMenuItem(_hMenu, id(), (flag ? MF_CHECKED : MF_UNCHECKED));
}

bool BMenuItem::checked()
{

	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	BOOL ret = GetMenuItemInfo(
	/*HMENU*/           _hMenu,
	/*UINT*/            id(),
	/*BOOL*/            /*fByPosition*/ FALSE,
	/*LPMENUITEMINFO*/ &mii);


}


HMENU BMenuItem::hMenu()
{
	return _hMenu;
}

BMenu* BMenuItem::menu()
{
	return _menu;
}