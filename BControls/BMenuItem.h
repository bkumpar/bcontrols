#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

class BMenu;
class BPopUpMenu;

IMPORT_EXPORT class BMenuItem : public BVisualControl
{
public:
    BMenuItem();
    BMenuItem(BMenu* menu, std::wstring text);
    BMenuItem(BMenuItem* menuItem, std::wstring text);
    void setText(std::wstring text);
	std::wstring text();
    void setIcon(HBITMAP bitmap);
   	void click();
	void setChecked(bool flag);
	bool checked();
	HMENU hMenu();
	BMenu* menu();
private:
	HMENU _hMenu;
	BMenu* _menu;
    std::wstring _text;
    UINT _flags;
	ATOM _menuItemAtom;
	std::wstring _className;
	HINSTANCE _hInstance;
	HWND createControl(HWND hwndParent);
 	ATOM RegisterMenuItemClass(HINSTANCE hInstance);
	ATOM RegisterTimerClass(HINSTANCE hInstance);
	static LRESULT CALLBACK dummyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

typedef BMenuItem * BMenuItemPtr;