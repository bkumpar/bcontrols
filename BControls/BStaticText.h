#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BStaticText:public BVisualControl
{
public:
	BStaticText(void);
	BStaticText( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BStaticText(void);
//	void setBackgroundColor(BColor color);

private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height );
	//BColor _backgroundColor;
};

