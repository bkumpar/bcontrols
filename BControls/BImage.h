#pragma once
#include "stdafx.h"
#include <GdiPlus.h>

class BImage
{
public:
    BImage();
    ~BImage();
    
    bool load(std::wstring fileName);
    bool save(std::wstring fileName);
	bool create(int width, int height);
	bool drawLine(int x1,int y1,int x2,int y2);
	bool drawCircle(int x,int y,int r);
	bool drawPoint(int x,int y);
	int width();
	int height();
private:
    Gdiplus::Bitmap * _bitmap;
	Gdiplus::Graphics * _graphics;
   	Gdiplus::GdiplusStartupInput _gdiplusStartupInput;
	ULONG_PTR           _gdiplusToken;
    int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};