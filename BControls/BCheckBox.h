#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BCheckBox : public BVisualControl
{
public:
	enum CheckBoxState
	{
		cbsChecked,
		cbsUnchecked,
		cbsMixed
	};

	BCheckBox(void);
	BCheckBox( BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BCheckBox(void);
	void setState(CheckBoxState state);
	CheckBoxState state();
	bool checked();
	void setChecked(bool value);
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height);
};

