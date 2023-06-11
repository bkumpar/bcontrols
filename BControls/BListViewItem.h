#pragma once

#include "StdAfx.h"
#include "ExportImport.h"

class BListView;
class BListViewSubItem;

IMPORT_EXPORT class BListViewItem
{
public:
	BListViewItem();
	~BListViewItem();
	BListViewItem(BListView* listView, int index);
	void setText(std::wstring text);
	std::wstring text();
	int index();
	BListViewSubItem* addSubItem(std::wstring text, int index);
	BListView* listView();
private:
	BListView * _listView;
	int _index;
	LVITEMA ItemData;
};

