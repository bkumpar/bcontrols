#pragma once

#include "StdAfx.h"
#include "ExportImport.h"

class BListView;
class BListViewItem;

IMPORT_EXPORT class BListViewSubItem
{
public:
	BListViewSubItem();
	~BListViewSubItem();
	BListViewSubItem(BListViewItem* listViewItem, int index);
	void setText(std::wstring);
	std::wstring text();
	BListViewItem * listViewItem();
private:
	BListViewItem * _listViewItem;
	int _index;
	LVITEMA ItemData;

};
