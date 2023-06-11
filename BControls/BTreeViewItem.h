#pragma once

#include "ExportImport.h"
#include "StdAfx.h"
#include "BVisualControl.h"

class BTreeView;

IMPORT_EXPORT class BTreeViewItem
{
public:
	BTreeViewItem(void);
	BTreeViewItem(BTreeView* treeView, HTREEITEM treeItem);
	HTREEITEM treeItem();
	BTreeViewItem*  addItem( std::wstring text);

private:
	HTREEITEM _treeItem;
	BTreeView* _treeView;
};
