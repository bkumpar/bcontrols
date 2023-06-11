#include "stdafx.h"
#include "BForm.h"
#include "BException.h"


BForm::BForm()
{
	_text = L"BForm";
	_className = L"BForm";
}

BForm::BForm(HINSTANCE hInstance,  int nCmdShow, 
	HICON icon, HICON iconSmall, HCURSOR cursor, LPCWSTR menuName )
	: BVisualControl(), _hInstance(hInstance), _icon(icon), _iconSmall(iconSmall), _cursor(cursor), _menuName(menuName)
{
	_text = L"BForm";
	_className = L"BForm";
}


BForm::BForm(BVisualControl* parent, HINSTANCE hInstance,  int nCmdShow, 
	HICON icon, HICON iconSmall, HCURSOR cursor, LPCWSTR menuName )
	: BVisualControl(parent), _hInstance(hInstance), _icon(icon), _iconSmall(iconSmall), _cursor(cursor), _menuName(menuName)
{
	_text = L"BForm";
	_className = L"BForm";
}

BForm::~BForm(void)
{

}

void BForm::show()
{
	if(!_hWnd)
	{
		RegisterClass(_hInstance);
		createControl( NULL, _hInstance, 1);
	}
}

BOOL BForm::createControl(BVisualControl* parent, HINSTANCE hInstance, int nCmdShow)
{
	INITCOMMONCONTROLSEX icex;           
	icex.dwICC = ICC_STANDARD_CLASSES | ICC_LISTVIEW_CLASSES ;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	if(!InitCommonControlsEx(&icex))
	{
		std::cerr << L"Error initializing common controls!" << std::endl;
		return false;
	}
	_thisForm = this;
	_hWnd = CreateWindowEx(WS_EX_CONTEXTHELP
		, _className.c_str()
		, _text.c_str()
		, WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, parent ? parent->hWnd() : NULL
		, NULL
		, hInstance
		, NULL);

	if (!_hWnd)
	{
		throw new BException(L"Error creating window:" + _className);
	}
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(_hWnd, nCmdShow);
	UpdateWindow(_hWnd);

	return TRUE;
}


ATOM BForm::RegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	memset( &wcex, 0, sizeof( WNDCLASSEX ) ) ;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= _icon; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BCONTROLS));
	wcex.hCursor		= _cursor;//LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= _menuName;//MAKEINTRESOURCE(IDC_BCONTROLS);
	wcex.lpszClassName	= _className.c_str() /*szWindowClass*/;
	wcex.hIconSm		= _iconSmall;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK BForm::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{		
	BForm* me = (BForm*)(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	if (me)
		return me->realWndProc(hWnd, message, wParam, lParam);
	else if (_thisForm)
	{	
		BForm* me = (BForm*)_thisForm;
		return me->realWndProc(hWnd, message, wParam, lParam);
	}
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK BForm::realWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_COMMAND:
		{
			(this);
			HWND myHWnd = _idToHandle[(int)wParam];
			return SendMessage(myHWnd, BWM_CLICKED, (WPARAM) BN_CLICKED, (LPARAM)NULL );
			break;
		}

	case WM_DESTROY:
		{	
			int exitCode = 0;
			destroy();
			PostQuitMessage(exitCode);
			break;
		}
	case WM_CREATE:
		{
			_hWnd = hWnd;
			CreateEventArguments e(hWnd);
			create(e);
			break;
		}
	case WM_SIZE:
		{
			CreateEventArguments e(hWnd);
			resize(e);
			break;
		}
	case WM_CLOSE:
		{	
			bool cancel = false;
			CancelEventArguments e(false);
			close( e);
			if(!e.cancel)
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
	case WM_CTLCOLORSTATIC:
		{
			HWND h = (HWND)lParam;
			DWORD CtrlID = GetDlgCtrlID(h); //Window Control ID

			if (CtrlID == _id) //If desired control
			{
				HDC hdcStatic = (HDC) wParam;
				SetTextColor(hdcStatic, RGB(0,255,0));
				SetBkColor(hdcStatic, _backgroundColor);
				if (_hbrBkgnd == NULL)
				{
					_hbrBkgnd = CreateSolidBrush(_backgroundColor);
				}

				return (INT_PTR)_hbrBkgnd;
			}
			else
			{
				return SendMessage((HWND)lParam, WM_CTLCOLORSTATIC, (WPARAM) wParam, (LPARAM)lParam );
			}
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR * param = (LPNMHDR)lParam;
			switch (param->code)
			{
			case TCN_SELCHANGING:
				{
					// Return FALSE to allow the selection to change.
					return FALSE;
				}

			case TCN_SELCHANGE:
				{ 

					//int iPage = TabCtrl_GetCurSel(hWnd); 
					break;
				} 
			default:
				//long p = param->code;
				break;
			}
			return DefWindowProc(hWnd, message, wParam, lParam);	
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void BForm::destroy()
{

}

void BForm::close(CancelEventArguments& e)
{
	if(_closeHandler && _closeTarget)
	{
		BForm* target = (BForm*) _closeTarget;
		(target->*_closeHandler)(this, e);
	}
}

void BForm::close()
{
	PostMessage(this->hWnd(), WM_CLOSE, NULL, NULL);
}

LONG BForm::clientWidth()
{
	RECT rc;
	GetClientRect(_hWnd,&rc);
	return rc.right;
}

LONG BForm::clientHeight()
{
	RECT rc;
	GetClientRect(_hWnd,&rc);
	return rc.bottom;
}

BMainMenu* BForm::createMainMenu()
{
	return new BMainMenu(this);
}

BStatusBar* BForm::createStatusBar(int panels)
{
	int sbWidth = this->width();
	int sbHeight = 32;
	int sbX = 0;
	int sbY = this->height()-sbHeight-20;
	_statusBar = new BStatusBar(this, L"", sbX, sbY, sbWidth, sbHeight, panels);
	return _statusBar;
}

void BForm::setCloseEventHandler(void* target, CloseHandler handler)
{
	_closeTarget = target;
	_closeHandler = handler;
}
