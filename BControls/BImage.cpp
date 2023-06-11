#include "stdafx.h"
#include "Bimage.h"
#pragma comment(lib, "Gdiplus.lib")


using namespace Gdiplus;

BImage::BImage()
{
    GdiplusStartup(&_gdiplusToken, &_gdiplusStartupInput, NULL);
	_bitmap = NULL;
	_graphics = NULL;
}

BImage::~BImage()
{
	if ( _graphics != NULL)
	{
		delete _graphics;
	}

	if ( _bitmap != NULL)
	{
		delete _bitmap;
	}
    GdiplusShutdown(_gdiplusToken);
}

bool BImage::load(std::wstring fileName)
{
	if ( _bitmap != NULL)
	{
		delete _bitmap;
	}
	
    _bitmap = Gdiplus::Bitmap::FromFile(fileName.c_str());

	if (_bitmap == NULL)
	{
		return false;
	}
	if (Gdiplus::Ok != _bitmap->GetLastStatus())
	{
		return false;
	}
	_graphics = new Gdiplus::Graphics(_bitmap);

	if ( _graphics == NULL)
	{
		return false;
	}

	if (Gdiplus::Ok != _graphics->GetLastStatus())
	{
		return false;
	}


    return true;
}

bool BImage::save(std::wstring fileName)
{
    if(_bitmap == NULL)
    {
        return false;
    }
    CLSID pngClsid;
	GetEncoderClsid(L"image/jpeg", &pngClsid);
    _bitmap->Save(fileName.c_str(), &pngClsid);
    return true;
}

bool BImage::create(int width, int height)
{
	if ( _bitmap != NULL)
	{
		delete _bitmap;
	}



}

int BImage::width()
{
	return _bitmap != NULL ? _bitmap->GetWidth() : 0;
}

int BImage::height()
{
	return _bitmap != NULL ? _bitmap->GetHeight() : 0;
}


bool BImage::drawLine(int x1,int y1,int x2,int y2)
{
	Gdiplus::Pen blackpen( Gdiplus::Color( 255, 0, 0, 0 ), 10 );
    _graphics->DrawLine( &blackpen, x1, y1, x2, y2 );
	return (Gdiplus::Ok == _graphics->GetLastStatus());
}

bool BImage::drawCircle(int x,int y,int r)
{

}

bool BImage::drawPoint(int x,int y)
{

}

int BImage::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}