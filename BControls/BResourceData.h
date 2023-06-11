#pragma once
#if defined( BUILD_DLL )
    #define IMPORT_EXPORT __declspec(dllexport)
#else
    #define IMPORT_EXPORT __declspec(dllimport)
#endif

#include "StdAfx.h"


class IMPORT_EXPORT BResourceData
{
public:
	BResourceData(void);
	virtual ~BResourceData(void);

};
