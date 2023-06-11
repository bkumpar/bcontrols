#include "StdAfx.h"
#include <commdlg.h>
#include "BVisualControl.h"




class BFileDialog
{
public:

	enum FileDialogResult 
	{
		ResultOK,
		ResultCancel,
		ResultError,
	};
	BFileDialog(std::wstring title, HWND hwndOwner=NULL);
	BFileDialog(BVisualControl* owner);
	~BFileDialog();
	FileDialogResult show();
	void setFilter(std::wstring);
	std::wstring filename();

private:
	OPENFILENAME ofn;
	TCHAR  _filename[ MAX_PATH ];
	std::wstring _filter;
	std::wstring _title;
};
