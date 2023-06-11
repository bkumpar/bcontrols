#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

class BTabPage;

IMPORT_EXPORT class BTabControl:public BVisualControl
{
public:
	BTabControl(void);
	BTabControl( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BTabControl(void);
	BTabPage * addPage(std::wstring text, int index);
	BTabPage * page(int index);
	void removePage(int index);
	void removePage(BTabPage* tabPage);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
};

