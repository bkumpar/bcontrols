#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

class BListViewItem ;

IMPORT_EXPORT class BListView:public BVisualControl
{
public:
	BListView(void);
	BListView(BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	void addColumn(std::wstring text,int column, int width);
	BListViewItem * addItem(std::wstring text, int index);
	BListViewItem * item(int index);

private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height );

};

