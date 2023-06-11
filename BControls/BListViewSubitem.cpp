#include "StdAfx.h"
#include "BListViewSubitem.h"
#include "BListViewItem.h"
#include "BListView.h"
#include <vector>

BListViewSubItem::BListViewSubItem()
{


}

BListViewSubItem::~BListViewSubItem()
{


}

BListViewSubItem::BListViewSubItem(BListViewItem* listViewItem, int index)
{
	_listViewItem = listViewItem;
	_index = index;
}

void BListViewSubItem::setText(std::wstring text)
{
	ListView_SetItemText(listViewItem()->listView()->hWnd(),  
						listViewItem()->index(),   
						_index,   
						(LPTSTR)text.c_str());
}

std::wstring BListViewSubItem::text()
{
	std::vector<wchar_t> bufText( 256 );
	ListView_GetItemText(listViewItem()->listView()->hWnd(), 
						listViewItem()->index(), 
						_index,  
						&bufText[0], 
						(int)bufText.size());
	return std::wstring(&bufText[0]);
}


BListViewItem * BListViewSubItem::listViewItem()
{
	return _listViewItem;
}