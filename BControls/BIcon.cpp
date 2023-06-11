#include "stdafx.h"
#include "BIcon.h"

BIcon::BIcon()
{

}

BIcon::BIcon(HICON hIcon)
{
    _hIcon = hIcon;
}


BIcon::~BIcon()
{
    DeleteObject(this->_hIcon);
}
BIcon::BIcon(std::wstring fileName)
{
    HINSTANCE hInst = GetModuleHandle(NULL) ;
    _hIcon = (HICON)LoadImage( hInst, (LPCWSTR)fileName.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE  ) ;
}

BIcon::BIcon(int resourceId)
{
    HINSTANCE hInst = GetModuleHandle(NULL) ;
    _hIcon =  (HICON)LoadIcon( hInst, MAKEINTRESOURCE(resourceId) ) ;
}

HICON BIcon::hIcon()
{
    return _hIcon;
}

