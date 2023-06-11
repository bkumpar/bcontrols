#include "stdafx.h"
#include "BListView.h"
#include "BListViewItem.h"
#include "BListViewSubItem.h"
#include <vector>

BListViewItem::BListViewItem(void)
{

}

BListViewItem::BListViewItem(BListView* listView, int index)
{
	_listView = listView;
	_index = index;
}

BListView* BListViewItem::listView()
{
	return _listView;
}

void BListViewItem::setText(std::wstring text)
{
	ListView_SetItemText(_listView->hWnd(),  _index,    0,   (LPTSTR)text.c_str());
}

std::wstring BListViewItem::text()
{
	std::vector<wchar_t> bufText( MAX_PATH );
	size_t cchTextMax = 255; 
	ListView_GetItemText(_listView->hWnd(),_index, 0,  &bufText[0], (int)bufText.size());
	return std::wstring(&bufText[0]);
}

int BListViewItem::index()
{
	return _index;
}

BListViewSubItem* BListViewItem::addSubItem(std::wstring text, int index)
{
	ListView_SetItemText(_listView->hWnd(),  _index,    index,   (LPTSTR)text.c_str());
	return new BListViewSubItem((BListViewItem*)this, index);
}