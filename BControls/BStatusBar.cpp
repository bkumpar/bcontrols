
#include "stdafx.h"
#include "BStatusBar.h"


BStatusBar::BStatusBar(void): BVisualControl() 
{
}

BStatusBar::BStatusBar( BVisualControl* parent, std::wstring text, int left, int top, int width, int height, int panelsCount)
	: BVisualControl(parent)
{

	_hWnd = createControl(parent->hWnd(), _id, panelsCount);
	_idToHandle[_id] = _hWnd;
	SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	BOOL rc = SetWindowSubclass(_hWnd, &subWndProc, _id, NULL);
}

BStatusBar::~BStatusBar(void)
{
}


// Description: 
//   Creates a status bar and divides it into the specified number of parts.
// Parameters:
//   hwndParent - parent window for the status bar.
//   idStatus - child window identifier of the status bar.
//   hinst - handle to the application instance.
//   cParts - number of parts into which to divide the status bar.
// Returns:
//   The handle to the status bar.
//
HWND BStatusBar::createControl(HWND hwndParent, int idStatus, int cParts)
{
    HWND hwndStatus;
    RECT rcClient;
    HLOCAL hloc;
    PINT paParts;
    int i, nWidth;
    HINSTANCE hInst= GetModuleHandle(NULL);

    // Create the status bar.
    hwndStatus = CreateWindowEx(
        0,                       // no extended styles
        STATUSCLASSNAME,         // name of status bar class
        (PCTSTR) NULL,           // no text when first created
        SBARS_SIZEGRIP |         // includes a sizing grip
		SBARS_TOOLTIPS |		// enables tooltips
        WS_CHILD | WS_VISIBLE,   // creates a visible child window
        0, 0, 0, 0,              // ignores size and position
        hwndParent,              // handle to parent window
        (HMENU) idStatus,       // child window identifier
        hInst,                   // handle to application instance
        NULL);                   // no window creation data

    // Get the coordinates of the parent window's client area.
    GetClientRect(hwndParent, &rcClient);

    // Allocate an array for holding the right edge coordinates.
    hloc = LocalAlloc(LHND, sizeof(int) * cParts);
    paParts = (PINT) LocalLock(hloc);

    // Calculate the right edge coordinate for each part, and
    // copy the coordinates to the array.
    nWidth = rcClient.right / cParts;
    int rightEdge = nWidth;
    for (i = 0; i < cParts; i++) { 
       paParts[i] = rightEdge;
       rightEdge += nWidth;
    }

    // Tell the status bar to create the window parts.
    SendMessage(hwndStatus, SB_SETPARTS, (WPARAM) cParts, (LPARAM)paParts);

    // Free the array, and return.
    LocalUnlock(hloc);
    LocalFree(hloc);
    return hwndStatus;
}  

void BStatusBar::setPanelText(int index, std::wstring text)
{
	SendMessage(_hWnd, SB_SETTEXT, (WPARAM) index, (LPARAM)text.c_str() );
}

void BStatusBar::setTooltipText(int index, std::wstring text)
{
	SendMessage(_hWnd, SB_SETTIPTEXT, (WPARAM) index, (LPARAM)text.c_str() );
}

void BStatusBar::addPanel(int width)
{
	return;
}

void BStatusBar::insertPanel(int width)
{
	return;
}
