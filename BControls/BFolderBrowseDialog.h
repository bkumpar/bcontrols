#include "StdAfx.h"



class BFolderBrowseDialog
{
public:

	BFolderBrowseDialog();
	BOOL show();
	std::wstring folder();
private:
	std::wstring _folder;

};