#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BStatusPanel:public BVisualControl
{
public:
	BStatusPanel(void);
	BStatusPanel(BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BStatusPanel(void);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
	HWND createControl(HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
};
