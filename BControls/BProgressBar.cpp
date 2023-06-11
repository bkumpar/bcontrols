
#include "stdafx.h"
#include "BProgressBar.h"
#include "BEvent.h"

BProgressBar::BProgressBar(void): BVisualControl() 
{
}

BProgressBar::BProgressBar( BVisualControl* parent, int left, int top, int width, int height)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), left, top, width, height);
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
	_idToHandle[_id] = _hWnd;
}

BProgressBar::~BProgressBar(void)
{
}

HWND BProgressBar::createControl(HWND hwndParent, int left, int top, int width, int height)
{
    HINSTANCE hInst= GetModuleHandle(NULL);
	HWND hWnd = CreateWindowEx(NULL,	
		PROGRESS_CLASS,	
		(PTSTR) NULL ,
		WS_TABSTOP|WS_VISIBLE|WS_CHILD,
		left, top, width, height,
		hwndParent,
		(HMENU) _id,
		hInst,
		NULL
	);
	return hWnd;
}

void BProgressBar::setRange(int minValue, int maxValue)
{
	LRESULT res = SendMessage(hWnd(), PBM_SETRANGE32, (WPARAM)minValue, (LPARAM)maxValue);
}

int BProgressBar::minValue()
{
	LRESULT res = SendMessage(hWnd(), PBM_GETRANGE, (WPARAM)true, (LPARAM)NULL);
	return (int) res;
}

int BProgressBar::maxValue()
{
	LRESULT res = SendMessage(hWnd(), PBM_GETRANGE, (WPARAM)false, (LPARAM)NULL);
	return (int) res;
}

void BProgressBar::setStepValue(int value)
{
	LRESULT res = SendMessage(hWnd(), PBM_SETSTEP , (WPARAM)value, (LPARAM)NULL);
}

int BProgressBar::stepValue()
{
	LRESULT res = SendMessage(hWnd(), PBM_GETSTEP, (WPARAM)NULL, (LPARAM)NULL);
	return (int) res;
}
void BProgressBar::setValue(int value)
{
	LRESULT res = SendMessage(hWnd(), PBM_SETPOS, (WPARAM)value, (LPARAM)NULL);
}

int BProgressBar::value()
{
	LRESULT res = SendMessage(hWnd(), PBM_GETPOS, (WPARAM)NULL, (LPARAM)NULL);
	return (int) res;
}

std::time_t BProgressBar::elapsedTime()
{
	return (std::time_t)difftime(std::time(NULL), _startTime);
}

std::time_t BProgressBar::estimatedTime()
{
	double v = value();
	double max = maxValue();
	double min = minValue();
	time_t e = elapsedTime();
	if(v > min)
	{
		time_t tt = (time_t) (e * (max-v) / (v-min)) ;
		return tt;
	}
	
	return UNKNOWN_TIME;
}

void BProgressBar::resetTimer()
{
	_startTime = std::time(NULL);
}
