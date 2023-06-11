#include "stdafx.h"
#include "BPopUpMenu.h"
#include "BMainMenu.h"

BPopUpMenu::BPopUpMenu(BMainMenu* mainMenu,  std::wstring text)
	: BMenu(mainMenu, text)
{
    _hMenu = CreatePopupMenu();
	AppendMenu( mainMenu->hMenu(), MF_POPUP|MF_DISABLED, (UINT_PTR)_hMenu, (LPCWSTR)_text.c_str()); 
}

BPopUpMenu::BPopUpMenu()
	: BMenu()
{
    _hMenu = CreatePopupMenu();
}

void BPopUpMenu::show(int x, int y, BVisualControl* owner, UINT flags)
{
    BOOL ret = TrackPopupMenuEx( _hMenu             // HMENU       hmenu,
                                , flags             // UINT        fuFlags,
                                , x                 // int         x,
                                , y                 // int         y,
                                , owner->hWnd()  // HWND        hwnd,
                                ,NULL  );           // LPTPMPARAMS lptpm
}
