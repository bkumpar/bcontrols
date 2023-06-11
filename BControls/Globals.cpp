#include "stdafx.h"

#include <map>

std::map<int, HWND> _idToHandle;  
int firstID = 5000;


//HWND GetDlgItem( HWND hDlg,  int  nIDDlgItem);
//int GetDlgCtrlID(  HWND hWnd);