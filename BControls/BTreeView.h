#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

class BTreeViewItem;

IMPORT_EXPORT class BTreeView:public BVisualControl
{
public:
	BTreeView(void);
	BTreeView(BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BTreeView(void);
	HTREEITEM  addItem(std::wstring text);
	HTREEITEM  addItem(HTREEITEM parent, std::wstring text);
	BTreeViewItem*  addRoot(std::wstring text);
	void clear();

private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
	HWND createControl(HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
};
