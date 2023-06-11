#include "stdafx.h"
#include "BMainMenu.h"
#include "BMenu.h"
#include "BPopUpMenu.h"
#include "BForm.h"

BMainMenu::BMainMenu()
{
    _hMenu =  CreateMenu();
}

BMainMenu::BMainMenu(BForm* form)
	: _form(form)
{
	_hMenu =  CreateMenu();
	SetMenu(_form->hWnd(), _hMenu);
}

HMENU BMainMenu::hMenu()
{
	return _hMenu;
}

 BMenu* BMainMenu::addMenu( std::wstring text)
 {
	 return new BMenu(this, text);
 }

 BPopUpMenu* BMainMenu::addPopUpMenu( std::wstring text)
 {
	 return new BPopUpMenu(this, text);
 }

 HWND BMainMenu::hForm()
 {
	return _hForm;
 }

 BForm* BMainMenu::form()
 {
	 return _form;
 }