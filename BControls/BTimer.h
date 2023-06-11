#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BTimer: public BControl
{
	enum State{
		paused,
		stopped,
		working
	};

public:
	typedef void (BTimer::*OnTimerHandlerType)(void*, TimerEventArguments &e);

	BTimer(void);
	BTimer( HWND hwndParent, UINT interval=1000, UINT maxRepeats=0 );
	virtual ~BTimer(void);
	void start(UINT interval=0);
	void stop();
	void pause(UINT maxRepeats=0);
	void BTimer::pause();
	void BTimer::resume();
	void reset(UINT interval=0);
	void timer(DWORD dwTime);
	void setEventHandler(void* target, OnTimerHandlerType e);
private:
	HWND createControl(HWND hwndParent);
	ATOM registerClass();
	std::wstring _className;
	UINT _interval;
	UINT _maxRepeats;
	UINT_PTR _idTimer; 
	bool _paused ;
	HINSTANCE _hInstance;
	static VOID CALLBACK timerProc( 
				HWND hwnd,        // handle to window for timer messages 
				UINT message,     // WM_TIMER message 
				UINT idTimer,     // timer identifier 
				DWORD dwTime);     // current system time 

	VOID CALLBACK realTimerProc( 
				HWND hwnd,        // handle to window for timer messages 
				UINT message,     // WM_TIMER message 
				UINT idTimer,     // timer identifier 
				DWORD dwTime) ;    // current system time 

	OnTimerHandlerType _onTimerHandler;
	void * _onTimerEventTarget;

	ATOM _timerAtom;
	static LRESULT CALLBACK dummyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

