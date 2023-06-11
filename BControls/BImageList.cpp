
#include "stdafx.h"
#include "BImageList.h"

BImageList::BImageList(    )
{
    this->hInst = NULL;
}

BImageList::BImageList(HINSTANCE hInstance)
{
    this->hInst = hInstance;
}

BImageList::~BImageList()
{
    clean();
}

HBITMAP BImageList::add(std::wstring name, std::wstring fileName)
{
    HBITMAP handle = (HBITMAP)LoadImage( hInst, (LPCWSTR)fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE  ) ;
    images[name] = handle;
    return handle;

}


void BImageList::clean()
{
    for(BImageMap::iterator iter = images.begin(); iter != images.end(); ++iter)
    {
        std::wstring k =  iter->first;
        remove(k);
    }
}


void BImageList::remove(std::wstring name)
{
    HBITMAP handle = images[name];
    DeleteObject(handle);
    images.erase(name);

}
