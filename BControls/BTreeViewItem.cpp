
#include "stdafx.h"
#include "BTreeViewItem.h"
#include "BTreeView.h"


BTreeViewItem::BTreeViewItem(void)
{

}

BTreeViewItem::BTreeViewItem(BTreeView* treeView, HTREEITEM treeItem)
{
	_treeItem = treeItem;
	_treeView = treeView;
}

HTREEITEM BTreeViewItem::treeItem()
{
	return _treeItem;
}

BTreeViewItem*  BTreeViewItem::addItem( std::wstring text)
{
	TVINSERTSTRUCTW lpis;
	ZeroMemory( &lpis, sizeof(TVINSERTSTRUCTW));
	lpis.hParent =_treeItem;
	lpis.hInsertAfter =  TVI_LAST;
	lpis.item.pszText = (LPWSTR) text.c_str();
	lpis.item.mask = TVIF_TEXT;
	lpis.item.cchTextMax = 0 ;
	lpis.item.hItem = NULL;
	HTREEITEM treeItem = TreeView_InsertItem(_treeView->hWnd() ,&lpis);
	return new BTreeViewItem(_treeView, treeItem);
}

