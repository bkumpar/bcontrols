
#include "stdafx.h"
#include "BScrollBar.h"
#include "BEvent.h"

BScrollBar::BScrollBar(void): BVisualControl() 
{
}

BScrollBar::BScrollBar( BVisualControl* parent, int left, int top, int width, int height, ScrollBarOrientation orientation)
	: BVisualControl(parent), _smallStep(1), _largeStep(10)
{
	_hWnd = createControl(parent->hWnd(), left, top, width, height, orientation);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}


BScrollBar::~BScrollBar(void)
{
}

HWND BScrollBar::createControl(HWND hwndParent, int left, int top, int width, int height, ScrollBarOrientation orientation)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		L"SCROLLBAR",	
		(PTSTR) NULL,
		WS_CHILD | WS_VISIBLE | (DWORD)orientation,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}

void BScrollBar::setRange(int minValue, int maxValue)
{
	BOOL ret = SetScrollRange(hWnd(), SB_CTL,  minValue,  maxValue, TRUE);
}

int BScrollBar::minValue()
{
	SCROLLINFO scrollinfo;
	BOOL ret = GetScrollInfo(hWnd(), SB_CTL, &scrollinfo);
	return (int) scrollinfo.nMin;
}

int BScrollBar::maxValue()
{
	SCROLLINFO scrollinfo;
	BOOL ret = GetScrollInfo(hWnd(), SB_CTL, &scrollinfo);
	return (int) scrollinfo.nMax;
}

void BScrollBar::setPage(int pageSize)
{
	SCROLLINFO scrollinfo;
	ZeroMemory( & scrollinfo, sizeof( scrollinfo ) );
	scrollinfo.cbSize = sizeof(SCROLLINFO);
	scrollinfo.fMask = SIF_PAGE;
	scrollinfo.nPage = pageSize;
	//scrollinfo.nMin ;
	//scrollinfo.nMax ;
	//scrollinfo.nPos ;
	int res = SetScrollInfo(hWnd(), SB_CTL, &scrollinfo, TRUE);
}


void BScrollBar::setValue(int value)
{
	int res = SetScrollPos(hWnd(), SB_CTL, value, TRUE);
}

int BScrollBar::value()
{
	return GetScrollPos(hWnd(), SB_CTL );
}

void BScrollBar::setSmallStep(int value)
{
	_smallStep = value;
}

int BScrollBar::smallStep()
{
	return _smallStep;
}

void BScrollBar::setLargeStep(int value)
{
	_largeStep = value;
}

int BScrollBar::largeStep()
{
	return _largeStep;
}
