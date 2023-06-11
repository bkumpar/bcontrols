#pragma once

//#include "BVisualControl.h"
#include "StdAfx.h"
#include "ExportImport.h"
#include "BMenu.h"

class BMenu;
class BPopUpMenu;
class BForm;

IMPORT_EXPORT class BMainMenu //: public BVisualControl
{
	
public:   
    BMainMenu();
	BMainMenu(BForm* form);
	void remove();
	HMENU hMenu();
	HWND hForm();
	BForm* form();
	BMenu* addMenu( std::wstring text);
	BPopUpMenu* addPopUpMenu( std::wstring text);
private:
   HMENU  _hMenu;
   UINT _flags;
   HWND _hForm;
   BForm* _form;

};

typedef BMainMenu * BMainMenuPtr;