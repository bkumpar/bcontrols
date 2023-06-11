#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BButton:public BVisualControl
{
public:
	BButton(void);
	BButton( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BButton(void);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
};

