#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BRadioButton:public BVisualControl
{
public:
	BRadioButton(void);
	BRadioButton( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BRadioButton(void);
//	void setBackgroundColor(BColor color);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
//	COLORREF _backgroundColor;
};
