#pragma once

#include <string>
#include <map>

typedef std::map<std::wstring, HBITMAP> BImageMap;

class BImageList
{
public:
    BImageList();
    BImageList(HINSTANCE hInstance);
    enum Type {IT_BITMAP, IT_ICON};
    ~BImageList();
    HBITMAP add(std::wstring name, std::wstring fileName);
    void remove(std::wstring name);
private:
    HINSTANCE hInst;
    BImageMap images;
    void clean();
};