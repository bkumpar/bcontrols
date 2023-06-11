#include "StdAfx.h"
#include "BFileDialog.h"
#include <Cderr.h>

BFileDialog::BFileDialog(std::wstring title, HWND hwndOwner)
{
    ZeroMemory( &_filename, sizeof( _filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
	ofn.hwndOwner = hwndOwner;
	_title = title;



}

BFileDialog::~BFileDialog()
{


}

void BFileDialog::setFilter(std::wstring)
{


}
std::wstring BFileDialog::filename()
{
	return std::wstring(_filename);
}

BFileDialog::FileDialogResult BFileDialog::show()
{
	ofn.lpstrFilter  = L"Text Files\0*.txt\0Any File\0*.*\0";
    ofn.lpstrFile    = _filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = _T("Select a File, yo!");
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameW( &ofn ))
	{
		return ResultOK;
	}
	else
	{
		switch (CommDlgExtendedError())
		{
			case CDERR_DIALOGFAILURE   :
			case CDERR_FINDRESFAILURE  :
			case CDERR_INITIALIZATION  :
			case CDERR_LOADRESFAILURE  :
			case CDERR_LOADSTRFAILURE  :
			case CDERR_LOCKRESFAILURE  :
			case CDERR_MEMALLOCFAILURE :
			case CDERR_MEMLOCKFAILURE  :
			case CDERR_NOHINSTANCE     : 
			case CDERR_NOHOOK          :       
			case CDERR_STRUCTSIZE      :    
			case FNERR_BUFFERTOOSMALL  : 
			case FNERR_INVALIDFILENAME :
			case FNERR_SUBCLASSFAILURE : 
				return ResultError;
				break;
			default: 
				return ResultCancel;
		}
	}


}

/*
#include <iostream>
#include <tchar.h>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

int main()
{
  char filename[ MAX_PATH ];

  OPENFILENAME ofn;
    ZeroMemory( &filename, sizeof( filename ) );
    ZeroMemory( &ofn,      sizeof( ofn ) );
    ofn.lStructSize  = sizeof( ofn );
    ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter  = _T("Text Files\0*.txt\0Any File\0*.*\0");
    ofn.lpstrFile    = filename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrTitle   = _T("Select a File, yo!");
    ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

  if (GetOpenFileName( &ofn ))
  {
    std::cout << "You chose the file \"" << filename << "\"\n";
  }
  else
  {
    // All this stuff below is to tell you exactly how you messed up above. 
    // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
    switch (CommDlgExtendedError())
    {
      case CDERR_DIALOGFAILURE   : std::cout << "CDERR_DIALOGFAILURE\n";   break;
      case CDERR_FINDRESFAILURE  : std::cout << "CDERR_FINDRESFAILURE\n";  break;
      case CDERR_INITIALIZATION  : std::cout << "CDERR_INITIALIZATION\n";  break;
      case CDERR_LOADRESFAILURE  : std::cout << "CDERR_LOADRESFAILURE\n";  break;
      case CDERR_LOADSTRFAILURE  : std::cout << "CDERR_LOADSTRFAILURE\n";  break;
      case CDERR_LOCKRESFAILURE  : std::cout << "CDERR_LOCKRESFAILURE\n";  break;
      case CDERR_MEMALLOCFAILURE : std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
      case CDERR_MEMLOCKFAILURE  : std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
      case CDERR_NOHINSTANCE     : std::cout << "CDERR_NOHINSTANCE\n";     break;
      case CDERR_NOHOOK          : std::cout << "CDERR_NOHOOK\n";          break;
      case CDERR_NOTEMPLATE      : std::cout << "CDERR_NOTEMPLATE\n";      break;
      case CDERR_STRUCTSIZE      : std::cout << "CDERR_STRUCTSIZE\n";      break;
      case FNERR_BUFFERTOOSMALL  : std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
      case FNERR_INVALIDFILENAME : std::cout << "FNERR_INVALIDFILENAME\n"; break;
      case FNERR_SUBCLASSFAILURE : std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
      default                    : std::cout << "You cancelled.\n";
    }
  }
}
*/