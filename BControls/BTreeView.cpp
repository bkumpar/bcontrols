
#include "stdafx.h"
#include "BTreeView.h"
#include "BTreeViewItem.h"

BTreeView::BTreeView(void): BVisualControl() 
{
}

BTreeView::BTreeView( BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}

BTreeView::~BTreeView(void)
{
}

HWND BTreeView::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height)
{
	HWND hWnd = CreateWindowEx( 
		WS_EX_CLIENTEDGE
		, WC_TREEVIEW
		, text.c_str() 
		, WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_CHECKBOXES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_EX_DOUBLEBUFFER | TVS_EX_FADEINOUTEXPANDOS | TVS_TRACKSELECT
		, left, top, width, height
		, hwndParent
		, (HMENU) id()
		, GetModuleHandle(NULL)
		, NULL
	);
	return hWnd;
}

BTreeViewItem* BTreeView::addRoot(std::wstring text)
{
	TVINSERTSTRUCTW lpis;
	ZeroMemory( &lpis, sizeof(TVINSERTSTRUCTW));
	lpis.hParent = NULL;
	lpis.hInsertAfter = TVI_ROOT;
	lpis.item.cchTextMax = (int)text.length(); 
	lpis.item.pszText = (LPWSTR) text.c_str();
	lpis.item.mask = TVIF_TEXT;
	HTREEITEM treeItem = TreeView_InsertItem(hWnd(),&lpis);
	return new BTreeViewItem((BTreeView*)this, treeItem);
} 

void BTreeView::clear()
{
	TreeView_DeleteAllItems(hWnd());
}