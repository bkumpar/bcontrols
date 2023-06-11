#pragma once

#include "BIcon.h"
#include <map>

typedef std::map<std::wstring, BIcon*> BIconMap;

class BIconList
{
public:
    BIconList();
    BIconList(HINSTANCE hInstance);
    ~BIconList();
    BIcon* add(std::wstring name, std::wstring fileName);
    BIcon* add(std::wstring name, BIcon* icon);
    BIcon* add(std::wstring name, int resourceId);
    void remove(std::wstring name);
    BIcon* icon(std::wstring name);
private:
    HINSTANCE hInst;
    BIconMap icons;
    void clean();
};