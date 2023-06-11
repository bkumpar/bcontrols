#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"
#include "BMenu.h"

IMPORT_EXPORT class BPopUpMenu : public BMenu
{
public:
	BPopUpMenu();
    BPopUpMenu(BMainMenu* mainMenu,  std::wstring text);
    void show(int x, int y, BVisualControl* owner, UINT flags = 0x0);

private:
};