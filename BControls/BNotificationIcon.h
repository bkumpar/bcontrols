#pragma once

#include "BControl.h"
#include "BIcon.h"
#include <shellapi.h>
#include <string>

static void * _thisNotificationIcon;

class BNotificationIcon : public BControl
{
public:
    BNotificationIcon(BControl* parent, BIcon* icon, std::wstring toolTipText);
    BNotificationIcon(BControl* parent, BIcon* icon, std::wstring toolTipText, BIcon* baloonIcon, std::wstring baloonText);
    ~BNotificationIcon();
    void setIcon(BIcon* icon);
    void setToolTipText(std::wstring toolTipText);
    void setBaloonIcon(BIcon* baloonIcon);
    void setBaloonTitle(std::wstring baloonTitle);
    void setBaloonText(std::wstring baloonText);
    void show();
    void show(BIcon* icon);
	void showBaloon();
	void showBaloon(BIcon* baloonIcon, std::wstring baloonTitle, std::wstring baloonText );
	void showTooltip(std::wstring toolTipText);
    void hide();

private:

    HICON _hIcon;
    NOTIFYICONDATA _notifyIconData ;
    void initNotifyIconData( HWND hWnd, BIcon* notifyIcon, std::wstring toolTipText);
	void initNotifyIconData( HWND hWnd, BIcon* notifyIcon, std::wstring toolTipText, BIcon* baloonIcon, std::wstring baloonText);
    HWND createControl(HWND hwndParent);
	ATOM RegisterClass();
	std::wstring _className;
    ATOM _atom;
	static LRESULT CALLBACK subWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK localSubWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 

};