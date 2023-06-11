#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

static void * _thisPanel;
static bool _registered = false;

IMPORT_EXPORT class BPanel :public BVisualControl
{

public:
	BPanel();
	BPanel(BVisualControl* parent);
	BPanel(BVisualControl* parent, int left, int top, int width, int height);
	~BPanel();

private:

	BVisualControl* _parent;
	const std::wstring _className;
	const std::wstring _windowName;
	ATOM RegisterClass();
	ATOM _atom;

	HWND createControl(HWND hwndParent,  int left, int top, int width, int height);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK realWndProc(HWND, UINT, WPARAM, LPARAM);


};
