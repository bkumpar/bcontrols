#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include <string>

class BMainMenu;
class BMenuItem;

IMPORT_EXPORT class BMenu 
{
public:    
	BMenu();
	BMenu(BMainMenu* mainMenu,  std::wstring text);
	BMenu(BMenu* menu,  std::wstring text);
	HMENU hMenu();
	BMenu* addSubMenu(std::wstring text);
	BMenuItem* addMenuItem(std::wstring text);
	void addSeparator();
	BMainMenu* mainMenu();
protected:
	HMENU  _hMenu;
	BMainMenu* _mainMenu;
	std::wstring _text;
};

typedef BMenu * BMenuPtr;