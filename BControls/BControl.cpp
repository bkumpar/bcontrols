#include "StdAfx.h"
#include "BVisualControl.h"
#include "BScrollBar.h"

BControl::BControl(void)
{
	_id = nextID();
	_customPaint = false;
	_hbrBkgnd = NULL;
	_hWnd = NULL;
	_clickTarget = NULL;		_clickHandler = NULL;
	_mouseDownTarget = NULL;	_mouseDownHandler = NULL;
	_mouseWheelHandler = NULL; _mouseWheelTarget = NULL;
	_createTarget = NULL;		_createHandler = NULL;
	_resizeTarget = NULL;		_resizeHandler = NULL;
	_paintTarget = NULL;		_paintHandler = NULL;
	_changeTarget = NULL;		_changeHandler = NULL;

}

BControl::BControl(HWND parent)
{
	_hWndParent = parent;
	_id = nextID();
	_customPaint = false;
	_hbrBkgnd = NULL;
	_hWnd = NULL;
	_clickTarget = NULL;		_clickHandler = NULL;
	_mouseDownTarget = NULL;	_mouseDownHandler = NULL;
	_mouseWheelHandler = NULL; _mouseWheelTarget = NULL;
	_createTarget = NULL;		_createHandler = NULL;
	_resizeTarget = NULL;		_resizeHandler = NULL;
	_paintTarget = NULL;		_paintHandler = NULL;
	_changeTarget = NULL;		_changeHandler = NULL;
}

BControl::~BControl(void)
{
	if (_hbrBkgnd != NULL)
	{
		DeleteObject(_hbrBkgnd);
	}

}

HWND BControl::hWnd(void)
{
	return _hWnd;
}

HWND BControl::hWndParent(void)
{
	return _hWndParent;
}

int BControl::id(void)
{
	return this->_id;
}

int BControl::nextID()
{
	return firstID++;
}

/*
Event triggers
*/

void BControl::click()
{
	EventArguments e;
	if (_clickHandler && _clickTarget)
	{
		BControl* target = (BControl*)_clickTarget;
		(target->*_clickHandler)(this, e);
	}

}

void BControl::mouseUp(UINT button, int xPos, int yPos)
{
	MouseEventArguments e(button, xPos, yPos);
}

void BControl::mouseDown(UINT button, int xPos, int yPos)
{
	if (_mouseDownHandler && _mouseDownTarget)
	{
		POINT screenPos;
		screenPos.x = xPos;
		screenPos.y = yPos;
		ClientToScreen(hWnd(), &screenPos);
		MouseEventArguments e(button, (int)screenPos.x, (int)screenPos.y);
		BControl* target = (BControl*)_mouseDownTarget;
		(target->*_mouseDownHandler)(this, e);
	}
}

void BControl::mouseWheel(UINT button, int xPos, int yPos, int delta)
{
	if (_mouseWheelHandler && _mouseWheelTarget)
	{
		POINT screenPos;
		screenPos.x = xPos;
		screenPos.y = yPos;
		ClientToScreen(hWnd(), &screenPos);
		MouseEventArguments e(button, (int)screenPos.x, (int)screenPos.y, delta);
		BControl* target = (BControl*)_mouseWheelTarget;
		(target->*_mouseWheelHandler)(this, e);
	}
}

void BControl::resize(EventArguments& e)
{
	if (_resizeHandler && _resizeTarget)
	{
		BControl* target = (BControl*)_resizeTarget;
		(target->*_resizeHandler)(this, e);
	}
}

void BControl::create(CreateEventArguments& e)
{
	if (_createHandler && _createTarget)
	{
		BControl* target = (BControl*)_createTarget;
		(target->*_createHandler)(this, e);
	}
}

void BControl::paint(PaintEventArguments& e)
{
	if (_paintHandler && _paintTarget)
	{
		BControl* target = (BControl*)_paintTarget;
		(target->*_paintHandler)(this, e);
	}
}

void BControl::change(ChangeEventArguments& e)
{
	if (_changeHandler && _changeTarget)
	{
		BControl* target = (BControl*)_changeTarget;
		(target->*_changeHandler)(this, e);
	}
}

LRESULT CALLBACK BControl::subWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	BControl* me = (BControl*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (me)
		return me->realSubWndProc(hWnd, msg, wParam, lParam, uIdSubclass, dwRefData);
	else
		return DefSubclassProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK BControl::realSubWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//return DefSubclassProc(hWnd, msg, wParam, lParam);
	switch (msg)
	{
	case WM_RBUTTONDOWN:
		//mouseDown((UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_RBUTTONUP:
		//mouseUp((UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
		//mouseDown((UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONUP:
		//mouseUp((UINT)wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_MOUSEWHEEL:
		//mouseWheel(NULL, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GET_WHEEL_DELTA_WPARAM(wParam));
		break;
	case WM_PAINT:
		//if (_customPaint)
		//{
		//	hdc = BeginPaint(hWnd, &ps);
		//	//hdc = GetDC(hWnd);
		//	PaintEventArguments e(hWnd, ps, hdc);
		//	paint(e);
		//	EndPaint(hWnd, &ps);
		//	ReleaseDC(hWnd, hdc);
		//	return 0;
		//}
		break;
		/*
		If the control runs on a Win32 system, there are several types of WM_CTLCOLOR* messages it may receive. For more information, see WM_CTLCOLORBTN, WM_CTLCOLORDLG, WM_CTLCOLOREDIT, WM_CTLCOLORLISTBOX, WM_CTLCOLORMSGBOX, WM_CTLCOLORSCROLLBAR, WM_CTLCOLORSTATIC.
		*/
	case WM_CTLCOLORSTATIC:

	case WM_CTLCOLORBTN:
	{
		//HWND h = (HWND)lParam;
		//DWORD CtrlID = GetDlgCtrlID(h); //Window Control ID

		//if (CtrlID == _id) //If desired control
		//{
		//	HDC hdcStatic = (HDC)wParam;
		//	SetTextColor(hdcStatic, _textColor);
		//	SetBkMode(hdcStatic, _backgroundMode);
		//	if (_backgroundMode == transparent)
		//	{
		//		return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
		//	}
		//	return (INT_PTR)CreateSolidBrush(_backgroundColor);

		//}
		//else
		//{
		//	return SendMessage((HWND)lParam, msg, (WPARAM)wParam, (LPARAM)lParam);
		//}
		break;
	}
	
	case WM_CREATE:
	{
		//CreateEventArguments e(hWnd);
		//create(e);
		break;
	}
	case WM_VSCROLL:
	case WM_HSCROLL:
	{
		//BScrollBar* sb = (BScrollBar*) this;
		//HWND h = (HWND)lParam;
		//DWORD CtrlID = GetDlgCtrlID(h); //Window Control ID
		//if (CtrlID == _id) //If desired control
		//{
		//	switch (LOWORD(wParam))
		//	{
		//	case SB_THUMBPOSITION:
		//	case SB_THUMBTRACK:
		//	{
		//		int newValue = HIWORD(wParam);
		//		HWND hWnd = (HWND)lParam;
		//		int res = SetScrollPos(hWnd, SB_CTL, newValue, TRUE);
		//		ChangeEventArguments e(hWnd);
		//		change(e);
		//	}
		//	case SB_TOP:
		//	{
		//		int i = 2;
		//		break;
		//	}
		//	case SB_BOTTOM:
		//	{
		//		int i = 2;
		//		break;
		//	}
		//	case SB_PAGEUP:
		//	{
		//		int res = SetScrollPos(hWnd, SB_CTL, sb->value() - sb->largeStep(), TRUE);
		//		ChangeEventArguments e(hWnd);
		//		change(e);
		//		break;
		//	}
		//	case SB_PAGEDOWN:
		//	{
		//		int res = SetScrollPos(hWnd, SB_CTL, sb->value() + sb->largeStep(), TRUE);
		//		ChangeEventArguments e(hWnd);
		//		change(e);
		//		break;
		//	}
		//	case SB_LINEUP:
		//	{
		//		int res = SetScrollPos(hWnd, SB_CTL, sb->value() - sb->smallStep(), TRUE);
		//		ChangeEventArguments e(hWnd);
		//		change(e);
		//		break;
		//	}
		//	case SB_LINEDOWN:
		//	{
		//		int res = SetScrollPos(hWnd, SB_CTL, sb->value() + sb->smallStep(), TRUE);
		//		ChangeEventArguments e(hWnd);
		//		change(e);
		//		break;
		//	}

		//	}
		//}
		//else
		//{
		//	return SendMessage((HWND)lParam, msg, (WPARAM)wParam, (LPARAM)lParam);
		//}
		break;
	}
	
	case WM_SIZING:
		break;
	case BWM_CLICKED:
		//click();
		break;
	case WM_COMMAND:
	{
		//switch (HIWORD(wParam))
		//{
		//case BN_CLICKED:
		//{
		//	HWND myHWnd = _idToHandle[(int)wParam];
		//	return SendMessage(myHWnd, BWM_CLICKED, (WPARAM)NULL, (LPARAM)NULL);
		//}
		////default:
		////	return DefSubclassProc(hWnd, msg, wParam, lParam);
		//}
		break;
	}
	case WM_NOTIFY:
	{
		//NMHDR * param = (LPNMHDR)lParam;
		//switch (param->code)
		//{
		//case TCN_SELCHANGING:
		//{
		//	// Return FALSE to allow the selection to change.
		//	return FALSE;
		//}

		//case TCN_SELCHANGE:
		//{

		//	int iPage = TabCtrl_GetCurSel(hWnd);

		//	break;
		//}
		//default:
		//	long p = param->code;
		//	break;
		//}
		return TRUE;
	}
	case WM_TRAYICON:
	{
		//LPARAM eventId = LOWORD(lParam);
		//LPARAM iconId = HIWORD(lParam);
		//int i = 0;
		//switch (eventId)
		//{
		//case WM_MOUSEMOVE:
		//	i = WM_MOUSEMOVE;
		//	break;
		//case WM_LBUTTONDOWN:
		//	i = WM_LBUTTONDOWN;
		//	break;
		//case WM_RBUTTONDOWN:
		//	std::wstring text = this->text();
		//	int id = this->_id;
		//	HWND hWnd = this->hWnd();
		//	i = WM_RBUTTONDOWN;
		//	break;
		//}
		break;
	}
	default:
		return DefSubclassProc(hWnd, msg, wParam, lParam);

	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);
}

//
// event handler setters
//
void BControl::setClickEventHandler(void* target, ClickHandler handler)
{
	_clickTarget = target;
	_clickHandler = handler;
}

void BControl::setMouseDownEventHandler(void* target, MouseDownHandler handler)
{
	_mouseDownTarget = target;
	_mouseDownHandler = handler;
}

void BControl::setMouseWheelEventHandler(void* target, MouseWheelHandler handler)
{
	_mouseWheelTarget = target;
	_mouseWheelHandler = handler;

}

void BControl::setCreateEventHandler(void* target, CreateHandler handler)
{
	_createTarget = target;
	_createHandler = handler;
}

void BControl::setResizeEventHandler(void* target, ResizeHandler handler)
{
	_resizeTarget = target;
	_resizeHandler = handler;
}

void BControl::setPaintEventHandler(void* target, PaintHandler handler)
{
	_paintTarget = target;
	_paintHandler = handler;
}

void BControl::setChangeEventHandler(void* target, ChangeHandler handler)
{
	_changeHandler = handler;
	_changeTarget = target;
}



//
// property setters and getters
//

void  BControl::setVisible(bool visible)
{
	BOOL ret = ShowWindow(hWnd(), visible ? SW_SHOW : SW_HIDE);
}

bool BControl::visible()
{
	return IsWindowVisible(hWnd()) != 0 ? true : false;
}

void BControl::setEnabled(bool enable)
{
	BOOL ret = EnableWindow(hWnd(), enable);
}

bool BControl::enabled()
{

}

void BControl::setCustomPaint(bool enable)
{
	_customPaint = enable;
}

bool BControl::customPaint()
{
	return _customPaint;
}

void BControl::setData(DataPtr data)
{
	_data = data;
}

DataPtr BControl::getData()
{
	return _data;
}

void BControl::setXPos(LONG xPos)
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	rc.left = xPos;
	setWindowPos(rc);
}

LONG BControl::xPos()
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	return rc.left;
}

void BControl::setYPos(LONG yPos)
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	rc.top = yPos;
	setWindowPos(rc);
}

LONG BControl::yPos()
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	return rc.top;
}

void BControl::setWidth(LONG width)
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, SWP_NOMOVE);
	rc.right = width;
	rc.bottom = rc.bottom - rc.top;
	setWindowPos(rc);
}

LONG BControl::width(void)
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	return rc.right - rc.left;
}

void BControl::setHeight(LONG height)
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	rc.bottom = height;
	rc.right = rc.right - rc.left;
	setWindowPos(rc);
}

LONG BControl::height()
{
	RECT rc;
	GetWindowRect(_hWnd, &rc);
	MapWindowPoints(HWND_DESKTOP, GetParent(_hWnd), (LPPOINT)&rc, 2);
	return rc.bottom - rc.top;
}

void BControl::setWindowPos(RECT rect)
{
	int flags = 0 /*SWP_NOMOVE | SWP_HIDEWINDOW */;
	BOOL rc = SetWindowPos(_hWnd, HWND_TOP, rect.left, rect.right, rect.right, rect.bottom, flags);
	if (rc == 0)
	{
		DWORD dwError = ::GetLastError();
		std::wcout << L"Failed to register window class." << _text.c_str() << "Error: " << dwError << std::endl;
	}
}

void BControl::setText(std::wstring text)
{
	SendMessage(this->_hWnd, WM_SETTEXT, 0, (LPARAM)text.c_str());
}

std::wstring BControl::text(void)
{
	int length = (int)SendMessage(this->_hWnd, WM_GETTEXTLENGTH, 0, 0);
	if (length == -1)
		return L"";
	wchar_t * buffer = new wchar_t[length + 1];
	SendMessage(this->_hWnd, WM_GETTEXT, length + 1, (LPARAM)buffer);
	std::wstring str(buffer);
	delete[] buffer;

	return str;
}

void  BControl::setFont(BFont& font)
{
	HFONT hFont = font.getHandle();
	SendMessage(_hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
}
