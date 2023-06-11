
#include "stdafx.h"
#include "BRegistry.h"



BRegistry::BRegistry()
{

}

BRegistry::BRegistry(HKEY hkey, std::wstring  subKey):
_hkey(hkey), _subKey(subKey)
{

}

BRegistry::~BRegistry()
{

}

bool BRegistry::readString(std::wstring  valueName, std::wstring  &value)
{
	DWORD keyType = 0;
	DWORD dataSize = 0;
	const DWORD flags = RRF_RT_REG_SZ; // Only read strings (REG_SZ)
	LONG result = ::RegGetValue(
		_hkey, 
		_subKey.c_str(),
		valueName.c_str(), 
		flags, 
		&keyType, 
		nullptr, // pvData == nullptr ? Request buffer size
		&dataSize);

	DWORD bufferSize = dataSize / sizeof(wchar_t);
	wchar_t *stringBuffer = new wchar_t[bufferSize];

	result = ::RegGetValue(
		_hkey, 
		_subKey.c_str(),
		valueName.c_str(), 
		flags, 
		nullptr, 
		stringBuffer, // Write string in this destination buffer
		&dataSize);
	value = std::wstring(stringBuffer);
	return true;
}

bool BRegistry::readInt(std::wstring  valueName, int  &value)
{
	DWORD keyType = 0;
	DWORD dataSize = sizeof(DWORD);
	DWORD data = 0;
	const DWORD flags = RRF_RT_REG_DWORD; 
	LONG result = ::RegGetValue(
		_hkey, 
		_subKey.c_str(),
		valueName.c_str(), 
		flags, 
		&keyType, 
		&data, 
		&dataSize);
	value = data;
	return true;
}

bool BRegistry::readBool(std::wstring  valueName, bool  &value)
{
	int intValue = 0;
	bool retval = readInt( valueName, intValue);
	value = intValue != 0 ? true : false;
	return true;
}



bool BRegistry::writeString(std::wstring  valueName, std::wstring  &value)
{
	DWORD keyType = 0;
	DWORD dataSize = (DWORD)value.size() * sizeof(wchar_t);
	LONG result = ::RegSetKeyValue(
		_hkey, 
		_subKey.c_str(),
		valueName.c_str(), 
		REG_SZ,
		value.c_str(),
		dataSize);

	return true;
}

bool BRegistry::writeInt(std::wstring  valueName, int  value)
{
	DWORD keyType = 0;
	DWORD dataSize = 0;
	DWORD data = value;
	LONG result = ::RegSetKeyValue(
		_hkey, 
		_subKey.c_str(),
		valueName.c_str(), 
		REG_DWORD, 
		&data,
		sizeof(DWORD));
	return true;
}

bool BRegistry::writeBool(std::wstring  valueName, bool  value)
{
	int intValue = value ? 1 : 0;
	bool retval = writeInt(valueName, intValue);
	return true;
}
