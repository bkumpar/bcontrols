#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BTextEdit:public BVisualControl
{
public:

	//typedef void (BTextEdit::*OnClickHandlerType)(void*, EventArguments &e);

	BTextEdit(void);
	BTextEdit(BVisualControl* parent, std::wstring text, int left, int top, int width, int height);
	virtual ~BTextEdit(void);
	//void setEventHandler(OnClickHandlerType e);
	void click();
	void setMultiline(bool flag);
	bool multiline();
private:
	HWND createControl(HWND hwndParent, std::wstring text, int left, int top, int width, int height );
	 //_onClickHandler;
};

