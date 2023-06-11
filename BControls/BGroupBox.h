#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BGroupBox : public BVisualControl
{
public:
	BGroupBox(void);
	BGroupBox(BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BGroupBox(void);

private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height );

};

