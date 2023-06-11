#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BPanel.h"


class BTabControl;

IMPORT_EXPORT class BTabPage : public BVisualControl
{
	friend class BTabControl;
public:
	BTabPage();
	~BTabPage();
	BTabPage(BTabControl* tabControl, std::wstring text, int index);
	void setText(std::wstring text);
	std::wstring text();
	int index();
	HWND hWnd();

private:
	BTabControl * _tabControl;
	BPanel * panel;
	int _index;
	LVITEMA ItemData;
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
};

