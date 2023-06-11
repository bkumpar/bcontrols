#pragma once
#include "stdafx.h"
#include <exception>
#include <string>

class BException : public std::exception
{
public:
	explicit BException(const std::wstring& message):
      _msg(message) {}

	  explicit BException(const std::wstring& message, int errorCode):
      _msg(message), _errorCode(errorCode) {}

	  std::wstring what()
	  {
		  return _msg;
	  }

	  int errorCode()
	  {
		  return _errorCode;
	  }

protected:
	std::wstring _msg;
	int _errorCode;
};

class BRegistryException : public BException
{
public:
	BRegistryException(const std::wstring& message)
		: BException(message){}
};

