#include "stdafx.h"
#include "BNotificationIcon.h"
#include <cstring>

BNotificationIcon::BNotificationIcon(BControl* parent, BIcon* icon, std::wstring toolTipText)
	:BControl(parent->hWnd())
{
	_className = L"BNOTIFICATIONICON";
	_atom = RegisterClass();
	_hWnd = createControl(_hWndParent);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	initNotifyIconData(_hWnd, icon, toolTipText);
}

BNotificationIcon::BNotificationIcon(BControl* parent, BIcon* icon, std::wstring toolTipText, BIcon* baloonIcon, std::wstring baloonText)
	:BControl(parent->hWnd())
{
	_className = L"BNOTIFICATIONICON";
	_atom = RegisterClass();
	_hWnd = createControl(_hWndParent);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	initNotifyIconData(_hWnd, icon, toolTipText, baloonIcon, baloonText);
}

BNotificationIcon::~BNotificationIcon()
{

}

void BNotificationIcon::setIcon(BIcon* icon)
{
	_notifyIconData.hIcon = icon->hIcon();
}

void BNotificationIcon::setToolTipText(std::wstring toolTipText)
{
	wcscpy_s(_notifyIconData.szTip, toolTipText.c_str());
}

void BNotificationIcon::setBaloonIcon(BIcon* baloonIcon)
{
	_notifyIconData.hBalloonIcon = baloonIcon->hIcon(); 
}

void BNotificationIcon::setBaloonTitle(std::wstring baloonTitle)
{
	wcscpy_s(_notifyIconData.szInfoTitle, baloonTitle.c_str());
}

void BNotificationIcon::setBaloonText(std::wstring baloonText)
{
	wcscpy_s(_notifyIconData.szInfo, baloonText.c_str());
}

void BNotificationIcon::show()
{
	Shell_NotifyIcon(NIM_ADD, &_notifyIconData);
	Shell_NotifyIcon(NIM_SETVERSION, &_notifyIconData);
}

void BNotificationIcon::show(BIcon* icon)
{
	_notifyIconData.hIcon = icon->_hIcon;
	Shell_NotifyIcon(NIM_ADD, &_notifyIconData);
	Shell_NotifyIcon(NIM_SETVERSION, &_notifyIconData);
}

void BNotificationIcon::hide()
{
	Shell_NotifyIcon(NIM_DELETE, &_notifyIconData);
}

void BNotificationIcon::showBaloon()
{
	_notifyIconData.uFlags |= NIF_INFO;
	Shell_NotifyIcon(NIM_MODIFY, &_notifyIconData);
	_notifyIconData.uFlags &= !NIF_INFO;
}

void BNotificationIcon::showTooltip(std::wstring toolTipText)
{
	_notifyIconData.uFlags = NIF_TIP;
	wcscpy_s(_notifyIconData.szTip, toolTipText.c_str());  
	Shell_NotifyIcon(NIM_MODIFY, &_notifyIconData);
}

void BNotificationIcon::showBaloon(BIcon* baloonIcon, std::wstring baloonTitle, std::wstring baloonText )
{
	_notifyIconData.dwInfoFlags = NIIF_INFO ;
	_notifyIconData.hBalloonIcon = baloonIcon->hIcon(); 
	wcscpy_s(_notifyIconData.szInfoTitle, baloonTitle.c_str());
	wcscpy_s(_notifyIconData.szInfo, baloonText.c_str());
	_notifyIconData.uFlags |= NIF_INFO;
	Shell_NotifyIcon(NIM_MODIFY, &_notifyIconData);
	_notifyIconData.uFlags &= !NIF_INFO;
}

void BNotificationIcon::initNotifyIconData( HWND hWnd, BIcon* notifyIcon, std::wstring toolTipText)
{
	memset( &_notifyIconData, 0, sizeof( NOTIFYICONDATA ) ) ;
	_notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	_notifyIconData.hWnd = hWnd;
	_notifyIconData.uID = _id;
	static const GUID niGUID = {0x307d71de, 0x7e0f, 0x415d, {0xba, 0xcc, 0x88, 0x24, 0xe4, 0x03, 0xb0, 0xcd}};
	_notifyIconData.guidItem = niGUID;
	_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;  
	_notifyIconData.uVersion = NOTIFYICON_VERSION_4 ;
	_notifyIconData.uCallbackMessage = WM_TRAYICON; //this message must be handled in hwnd's window procedure. more info below.
	_notifyIconData.hIcon = notifyIcon->hIcon(); 
	wcscpy_s(_notifyIconData.szTip, toolTipText.c_str());
}

void BNotificationIcon::initNotifyIconData( HWND hWnd, BIcon* notifyIcon, std::wstring toolTipText, BIcon* baloonIcon, std::wstring baloonText)
{
	memset( &_notifyIconData, 0, sizeof( NOTIFYICONDATA ) ) ;
	_notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	_notifyIconData.hWnd = hWnd;
	_notifyIconData.uID = _id;
	static const GUID niGUID = {0x307d71de, 0x7e0f, 0x415d, {0xba, 0xcc, 0x88, 0x24, 0xe4, 0x03, 0xb0, 0xcd}};
	_notifyIconData.guidItem = niGUID;
	_notifyIconData.uFlags = NIF_ICON |	NIF_MESSAGE | NIF_TIP;  
	_notifyIconData.uVersion = NOTIFYICON_VERSION_4 ;
	_notifyIconData.uCallbackMessage = WM_TRAYICON; //this message must be handled in hwnd's window procedure. more info below.
	_notifyIconData.hIcon = notifyIcon->hIcon(); 
	wcscpy_s(_notifyIconData.szTip, toolTipText.c_str());
	_notifyIconData.hBalloonIcon = baloonIcon->hIcon(); 
	wcscpy_s(_notifyIconData.szInfoTitle, baloonText.c_str());
	wcscpy_s(_notifyIconData.szInfo, baloonText.c_str());
}

HWND BNotificationIcon::createControl(HWND hwndParent)
{
	std::wstring text = L"NOTIFICATIONICON";
	_thisNotificationIcon = this;
	HWND hWnd = CreateWindowEx(NULL,	
		_className.c_str(),	
		text.c_str(),
		0,
		0, 0, 0, 0,
		NULL, //hwndParent,
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

ATOM BNotificationIcon::RegisterClass()
{
	WNDCLASSEX wcex;
	memset( &wcex, 0, sizeof( WNDCLASSEX ) ) ;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= subWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _className.c_str();
	wcex.hIconSm		= NULL;
	ATOM atom;
	if ( (atom = ::RegisterClassEx( &wcex )) == 0 )
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to register window class." << _className.c_str() << "Error: " <<  dwError << std::endl;
	}
	return atom;
}

LRESULT CALLBACK BNotificationIcon::subWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BNotificationIcon* me = (BNotificationIcon*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (me) 
		return me->localSubWndProc(hWnd, msg, wParam, lParam);
	else if (_thisNotificationIcon )
	{
		me = (BNotificationIcon*) _thisNotificationIcon;
		return me->localSubWndProc(hWnd, msg, wParam, lParam);
	}
	else
		return DefSubclassProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK BNotificationIcon::localSubWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_NCCREATE:
		{
			return TRUE;
		}
	case WM_TRAYICON:
		{
			LPARAM eventId = LOWORD(lParam);
			LPARAM iconId = HIWORD(lParam);
			int i = 0;
			switch (eventId)
			{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:
				mouseDown((UINT)MK_LBUTTON, 1000, 700);
				break;
			case WM_RBUTTONDOWN:
				mouseDown((UINT)MK_RBUTTON, GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam));
				break;
			}
			break;
		}
	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);
}

