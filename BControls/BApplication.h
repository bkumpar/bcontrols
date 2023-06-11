#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BForm.h"

class BForm;

IMPORT_EXPORT class BApplication
{
public:
	BApplication(void);
	virtual ~BApplication(void);
	void setHelpFile(std::wstring helpFile);
	std::wstring helpFile(void);
	//HWND showHelp(HWND hwndCaller);
	int run();
private:
	std::wstring  _helpFile;
};

