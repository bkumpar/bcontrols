#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BStatusBar:public BVisualControl
{
public:
	BStatusBar(void);
	BStatusBar(BVisualControl* parent, std::wstring text, int left, int top, int width, int height, int panelsCount );
	virtual ~BStatusBar(void);
	void addPanel(int width);
	void insertPanel(int width);
	void setPanelText(int index, std::wstring text);
	void setTooltipText(int index, std::wstring text);
private:
	//HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
	HWND createControl(HWND hwndParent, int idStatus, int cParts);

};
