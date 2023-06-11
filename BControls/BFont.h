#pragma once
//#pragma warning(disable : 4251 4995) 

#include "StdAfx.h"
#include "ExportImport.h"

IMPORT_EXPORT class BFont
{
public:
	BFont();
	void setName(LPCTSTR fontName);
	void setBold(bool bold);
	void setItalic(bool italic);
	void setUnderline(bool underline);
	void setSize(int fontSize);
	HFONT getHandle();

private:
	void setDefaults();
	int     _nHeight;
	int     _nWidth;
	int     _nEscapement;
	int     _nOrientation;
	int     _fnWeight;
	DWORD   _fdwItalic;
	DWORD   _fdwUnderline;
	DWORD   _fdwStrikeOut;
	DWORD   _fdwCharSet;
	DWORD   _fdwOutputPrecision;
	DWORD   _fdwClipPrecision;
	DWORD   _fdwQuality;
	DWORD   _fdwPitchAndFamily;
	LPCTSTR _lpszFace;
	std::string _fontName;

};
