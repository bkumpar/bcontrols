#pragma once

#include "resource.h"
#include "BIcon.h"
#include <shellapi.h>
#include <string>

#define WM_TRAYICON ( WM_USER + 1 )

#ifdef UNICODE
#define stringcopy wcscpy
#else
#define stringcopy strcpy
#endif
void InitNotifyIconData( HWND hWnd);

class NotificationIcon
{
public:
    NotificationIcon(HWND hParentWnd, HICON hIcon);
    NotificationIcon(HWND hParentWnd, BIcon* icon);
    ~NotificationIcon();
    void setText(std::wstring text);
    void show();
    //void show(HICON hIcon);
    void hide();
private:
    HICON hIcon;
    NOTIFYICONDATA notifyIconData ;
    void InitNotifyIconData( HWND hWnd, HICON notifyIcon);

};