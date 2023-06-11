
#include "stdafx.h"
#include "BMenu.h"
#include "BMainMenu.h"
#include "BMenuItem.h"


BMenu::BMenu()
{

}

BMenu::BMenu(BMainMenu* mainMenu,  std::wstring text)
	:_mainMenu(mainMenu), _text(text)
{
	_hMenu =  CreateMenu();
	AppendMenu( _mainMenu->hMenu(), MF_POPUP, (UINT_PTR)_hMenu, (LPCWSTR)_text.c_str()); 
}

BMenu::BMenu(BMenu* menu,  std::wstring text)
	:_mainMenu(menu->mainMenu()), _text(text)
{
	HMENU parentMenu = menu->hMenu();
	_hMenu = CreateMenu();
	BOOL ret = AppendMenu( parentMenu, MF_POPUP, (UINT_PTR)_hMenu, (LPCWSTR)_text.c_str()); 
	 (ret);
}

HMENU BMenu::hMenu()
{
	return _hMenu;
}

BMenu* BMenu::addSubMenu(std::wstring text)
{
	return new BMenu( this, text);
}

BMenuItem* BMenu::addMenuItem(std::wstring text)
{
	return new BMenuItem( this, text);
}

void BMenu::addSeparator()
{
	AppendMenu( _hMenu, MF_SEPARATOR, (UINT_PTR)NULL, (LPCWSTR)L""); 
}

BMainMenu* BMenu::mainMenu()
{
		return _mainMenu;
}