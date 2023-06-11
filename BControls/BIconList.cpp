
#include "stdafx.h"
#include "BIconList.h"

BIconList::BIconList(    )
{
    this->hInst = NULL;
}

BIconList::BIconList(HINSTANCE hInstance)
{
    this->hInst = hInstance;
}

BIconList::~BIconList()
{
    clean();
}

BIcon* BIconList::add(std::wstring name, std::wstring fileName)
{
    BIcon * newIcon = new BIcon(fileName);
    this->icons[name] = newIcon;
    return newIcon;
}

BIcon* BIconList::add(std::wstring name, BIcon* icon)
{
    this->icons[name] = icon;
    return icon;
}

BIcon* BIconList::add(std::wstring name, int resourceId)
{
    BIcon * newIcon = new BIcon(resourceId);
    this->icons[name] = newIcon;
    return newIcon;
}

void BIconList::clean()
{
    for(BIconMap::iterator iter = icons.begin(); iter != icons.end(); ++iter)
    {
        std::wstring k =  iter->first;
        remove(k);
    }
}


void BIconList::remove(std::wstring name)
{
    BIcon* icon = icons[name];
    delete icon;
    icons.erase(name);

}

BIcon* BIconList::icon(std::wstring name)
{
    BIcon* icon = icons[name];
    return icon;
}

    
