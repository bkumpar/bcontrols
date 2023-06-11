#include "StdAfx.h"

#include "BFolderBrowseDialog.h"
#include <Shlobj.h> 


BFolderBrowseDialog::BFolderBrowseDialog()
{



}

std::wstring BFolderBrowseDialog::folder()
{
	return _folder;
}


BOOL BFolderBrowseDialog::show()
{
	BOOL ret= FALSE;
	BROWSEINFO bi = {0};
	bi.lpszTitle = _T("Browse for Folder");
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if ( pidl != NULL )
	{
		TCHAR tszPath[MAX_PATH] = _T("\0");
		if ( SHGetPathFromIDList(pidl, tszPath) == TRUE )
		{
			_folder = std::wstring(tszPath);
			ret = TRUE;
		}
	// — Free pidl
	CoTaskMemFree(pidl);
	}
	return ret;
}