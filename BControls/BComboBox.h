#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BComboBox : public BVisualControl
{
public:
	BComboBox(void);
	BComboBox( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BComboBox(void);
	void addItem(std::wstring text);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
};

