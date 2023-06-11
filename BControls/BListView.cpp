#include "stdafx.h"
#include "BListView.h"
#include "BListViewItem.h"

BListView::BListView(void) : BVisualControl()
{

}

BListView::BListView(BVisualControl* parent, std::wstring text, int left, int top, int width, int height)
	: BVisualControl(parent)
{
	_hWnd = createControl(parent->hWnd(), text, left, top, width, height);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}


HWND BListView::createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height )
{
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

	HWND hWnd = CreateWindowEx( NULL
	        , WC_LISTVIEW 
			, text.c_str()
			, WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_VISIBLE | WS_BORDER
			, left, top, width, height
			, hwndParent
			, (HMENU) id()
			, (HINSTANCE) GetWindowLongPtr(hwndParent, GWLP_HINSTANCE)
			, NULL
		);
	return hWnd;
}

void BListView::addColumn(std::wstring text,int column,  int width)
{
	LVCOLUMNA columnData;
	columnData.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	columnData.fmt = LVCFMT_LEFT;
	columnData.cx = width;
	LPTSTR str = (LPTSTR)text.c_str();
	ListView_InsertColumn( hWnd(), column, &columnData);
}

BListViewItem *  BListView::addItem(std::wstring text, int index)
{
	LVITEM item;
    item.mask = LVIF_TEXT;
    item.iSubItem = 0;
    item.pszText = (LPTSTR)text.c_str();
    item.iItem = index;
    ListView_InsertItem(hWnd(), &item);
	return new BListViewItem(this, item.iItem);
}

BListViewItem* BListView::item(int index)
{
	return new BListViewItem((BListView*)this, index);
}