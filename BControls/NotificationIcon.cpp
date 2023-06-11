#include "stdafx.h"
#include "NotificationIcon.h"


    NotificationIcon::NotificationIcon(HWND hParentWnd, HICON hIcon)
    {
        InitNotifyIconData(hParentWnd, hIcon);
    }

    NotificationIcon::NotificationIcon(HWND hParentWnd, BIcon* icon)
    {
        InitNotifyIconData(hParentWnd, icon->hIcon());
    }

    NotificationIcon::~NotificationIcon()
    {

    }
    void NotificationIcon::show()
    {
        Shell_NotifyIcon(NIM_ADD, &notifyIconData);
    }

    //void NotificationIcon::show(HICON hIcon)
    //{
    //    notifyIconData.hIcon = hIcon;
    //    Shell_NotifyIcon(NIM_ADD, &notifyIconData);
    //}

    void NotificationIcon::hide()
    {
        Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
    }
    
    void NotificationIcon::setText(std::wstring text)
    {
        stringcopy(notifyIconData.szTip, text.c_str()); 
    }

void NotificationIcon::InitNotifyIconData( HWND hWnd, HICON notifyIcon)
{
  memset( &notifyIconData, 0, sizeof( NOTIFYICONDATA ) ) ;
  
  notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
  
  /////
  // Tie the NOTIFYICONDATA struct to our
  // global HWND (that will have been initialized
  // before calling this function)
  notifyIconData.hWnd = hWnd;
  // Now GIVE the NOTIFYICON.. the thing that
  // will sit in the system tray, an ID.
  notifyIconData.uID = IDI_TRAY_APP_ICON;
  // The COMBINATION of HWND and uID form
  // a UNIQUE identifier for EACH ITEM in the
  // system tray.  Windows knows which application
  // each icon in the system tray belongs to
  // by the HWND parameter.
  /////
  
  /////
  // Set up flags.
  notifyIconData.uFlags = NIF_ICON | // promise that the hIcon member WILL BE A VALID ICON!!
    NIF_MESSAGE | // when someone clicks on the system tray icon,
    // we want a WM_ type message to be sent to our WNDPROC
    NIF_TIP;      // we're gonna provide a tooltip as well, son.

  notifyIconData.uCallbackMessage = WM_TRAYICON; //this message must be handled in hwnd's window procedure. more info below.
  
  // Load da icon.  Be sure to include an icon "green_man.ico" .. get one
  // from the internet if you don't have an icon
  //g_notifyIconData.hIcon = (HICON)LoadImage( hInst,TEXT("sun_small.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE  ) ;
  notifyIconData.hIcon = notifyIcon; //(HICON)LoadIcon( hInst, MAKEINTRESOURCE(IDI_NOTIFICATIONICON) ) ;

  // set the tooltip text.  must be LESS THAN 64 chars
  stringcopy(notifyIconData.szTip, TEXT("Look this tooltip!!!"));
}
