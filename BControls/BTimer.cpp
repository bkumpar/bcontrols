#include "stdafx.h"
#include "BTimer.h"

BTimer::BTimer(void)
	:BControl()
{
}

BTimer::BTimer(  HWND hwndParent, UINT interval, UINT maxRepeats )
	:BControl()
{
	_idTimer = NULL;
	_paused = false;
	_className = L"BTIMER";
	_timerAtom = registerClass();
	_hWnd = createControl(hwndParent);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
}

BTimer::~BTimer(void)
{
}

void BTimer::start(UINT interval)
{
	if(! _idTimer )
	{
		_idTimer = SetTimer( _hWnd, id(), interval,  (TIMERPROC) timerProc);
	}
}

void BTimer::stop()
{
	if( _idTimer )
	{
		BOOL ret = KillTimer( _hWnd, _idTimer);
		_idTimer = NULL;
	}
}

void BTimer::pause(UINT maxRepeats)
{
}

void BTimer::pause()
{
	_paused = true;
}

void BTimer::resume()
{
	_paused = false;
}



void BTimer::reset(UINT interval)
{
}

VOID CALLBACK BTimer::timerProc( HWND hWnd, UINT message, UINT idTimer,  DWORD dwTime)
{
         BTimer* me = (BTimer*) (GetWindowLongPtr(hWnd, GWLP_USERDATA));
         if (me) 
		 {
			 me->realTimerProc( hWnd, message, idTimer,  dwTime);
		 }
}

VOID CALLBACK BTimer::realTimerProc( HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)

{
		timer(dwTime);
}


void BTimer::timer(DWORD dwTime)
{
	if(_onTimerHandler && !_paused)
	{
		TimerEventArguments e( dwTime);
		BTimer* target = (BTimer*) _onTimerEventTarget;
		(target->*_onTimerHandler)(this, e);
	}
}

HWND BTimer::createControl(HWND hwndParent)
{
	std::wstring text = L"TIMER";
	
	HWND hWnd = CreateWindowEx(NULL,	
		_className.c_str(),	
		text.c_str(),
		0,
		0, 0, 0, 0,
		hwndParent,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	if ( !hWnd )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to createControl ." << _className.c_str() << "Error: " <<  dwError << std::endl;
    
	}
	return hWnd;
}

ATOM BTimer::registerClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= dummyWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _className.c_str() /*szWindowClass*/;
	wcex.hIconSm		= NULL;

	if ( (this-> _timerAtom = ::RegisterClassEx( &wcex )) == 0 )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to register window class." << _className.c_str() << "Error: " <<  dwError << std::endl;
    
	}
	return this-> _timerAtom;
}

void BTimer::setEventHandler(void* target, OnTimerHandlerType e)
{
	_onTimerEventTarget = target;
	_onTimerHandler = e;
}

LRESULT CALLBACK BTimer::dummyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}