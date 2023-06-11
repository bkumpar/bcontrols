#pragma once
#include "stdafx.h"
#include "BFont.h"

BFont::BFont()
{
	setDefaults();
}

void BFont::setDefaults()
{
	HDC  hdc = GetDC(NULL);
	int lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	_nHeight = lfHeight;
	_nWidth = 0;
	_nEscapement = 0;
	_nOrientation =	0; 
	_fnWeight =	FW_DONTCARE;
	_fdwItalic = FALSE;
	_fdwUnderline =	FALSE; 
	_fdwStrikeOut = FALSE; 
	_fdwCharSet = ANSI_CHARSET;
	_fdwOutputPrecision = OUT_TT_PRECIS;
	_fdwClipPrecision = CLIP_DEFAULT_PRECIS;
	_fdwQuality = DEFAULT_QUALITY;
	_fdwPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE ;
	_lpszFace = L"Times New Roman";

}

HFONT  BFont::getHandle()
{

	return CreateFont (_nHeight 
		, _nWidth
		, _nEscapement
		, _nOrientation
		, _fnWeight
		, _fdwItalic
		, _fdwUnderline
		, _fdwStrikeOut
		, _fdwCharSet
		, _fdwOutputPrecision
		, _fdwClipPrecision
		, _fdwQuality
		, _fdwPitchAndFamily
		, _lpszFace);
}

void  BFont::setName(LPCTSTR fontName)
{

	_lpszFace = fontName;
}

void BFont::setBold(bool bold)
{
	_fnWeight =  (bold ? FW_BOLD : FW_NORMAL);
}

void BFont::setItalic(bool italic)
{
	_fdwItalic =  (italic ? TRUE : FALSE);
}

void BFont::setUnderline(bool underline)
{
	_fdwUnderline = (underline ? TRUE : FALSE);
}

void BFont::setSize(int fontSize)
{
	HDC  hdc = GetDC(NULL);
	_nHeight = -MulDiv(fontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
}
