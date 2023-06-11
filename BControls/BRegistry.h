#pragma once
#include "stdafx.h"
#include "ExportImport.h"


IMPORT_EXPORT class BRegistry 
{

public:
	BRegistry();
	BRegistry(HKEY hkey, std::wstring  subKey);
	~BRegistry();

	bool readString(std::wstring  valueName, std::wstring  &value);
	bool readInt(std::wstring  valueName, int  &value);
	bool readBool(std::wstring  valueName, bool  &value);

	bool writeString(std::wstring  valueName, std::wstring  &value);
	bool writeInt(std::wstring  valueName, int  value);
	bool writeBool(std::wstring  valueName, bool  value);

private:
	HKEY _hkey;
	std::wstring  _subKey;

};