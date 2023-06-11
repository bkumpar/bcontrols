#pragma once
#include <BForm.h>
#include <BButton.h>
#include <BStaticText.h>
#include <BTextEdit.h>
#include <BGroupBox.h>
#include <BTimer.h>
#include <BStatusBar.h>
#include <BTreeView.h>
#include <BTreeViewItem.h>
#include <BFont.h>
#include <BListView.h>
#include <BListViewItem.h>
#include <BListViewSubItem.h>
#include <BMainMenu.h>
#include <BMenu.h>
#include <BMenuItem.h>
#include <BPopUpMenu.h>
#include <BComboBox.h>
#include <BCheckBox.h>
#include <BProgressBar.h>
#include <BScrollBar.h>
#include <BRadioButton.h>
#include <BIconList.h>
#include <BNotificationIcon.h>
#include "SettingsForm.h"
#include "BVisualControl.h"

class MainForm : public BForm
{
public:
	MainForm( HINSTANCE hInstance, int nCmdShow, HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName );
	virtual ~MainForm(void);
	void close();
private:
	bool nicVisible;
	std::wstring now(); 

#pragma region groupBox
	BGroupBox* groupBox;
	void groupBox_onPaint(void * sender, PaintEventArguments& e);
#pragma endregion
#pragma region buttonCancel
	BButton* buttonCancel;
	void buttonCancelOnMouseDown(void * sender, MouseEventArguments& e);
	void buttonCancelOnMouseWheel(void * sender, MouseEventArguments& e);
	void buttonCancel_onClick(void * sender, EventArguments& e);
#pragma endregion	
#pragma region buttonOk
	BButton* buttonOk;
	void buttonOK_onClick(void * sender, EventArguments& e);
	void buttonOkOnMouseDown(void * sender, MouseEventArguments& e);
	void buttonOkOnMouseWheel(void * sender, MouseEventArguments& e);
#pragma endregion	
#pragma region staticText1
	BStaticText* staticText1;
#pragma endregion	
#pragma region textEdit	
	BTextEdit* textEdit1;
	void textEdit1MouseDown(void * sender, MouseEventArguments& e);
#pragma endregion	
#pragma region textEdit2
	BTextEdit* textEdit2;
	void textEdit2MouseDown(void * sender, MouseEventArguments& e);
#pragma endregion	
#pragma region realTimeTimer
	BTimer* realTimeTimer;
	void realTimeTimer_onTimer(void * sender, TimerEventArguments& e);
#pragma endregion	
	BStatusBar* statusBar; 
	BTreeView* treeView;
#pragma region listView
	BListView* listView;
	void listView_onCreate(void * sender, EventArguments& e);
#pragma endregion	
	BComboBox* comboBox;
#pragma region checkBox
	BCheckBox* checkBox;
	void checkBox_onClick(void * sender, EventArguments& e);
#pragma endregion
	BGroupBox* groupBoxProgress;
#pragma region buttonTestProgress
	BButton* buttonTestProgress;
	void buttonTestProgress_OnClick(void* sender, EventArguments& e);
#pragma endregion	
	BProgressBar* progressBar;
#pragma region progressTimer
	BTimer* progressTimer;
	void progressTimer_OnTimer(void* sender, EventArguments& e);
#pragma endregion
	BGroupBox* groupBoxTree;
	BGroupBox* groupBoxList;
#pragma region groupBoxRadioButtons
	BGroupBox* groupBoxRadioButtons;
	void groupBoxRadioButtons_onPaint(void* sender, PaintEventArguments& e);
#pragma endregion
#pragma region groupBoxScrollBars
	BGroupBox* groupBoxScrollBars;
	void groupBoxScrollBars_onPaint(void* sender, PaintEventArguments& e);
#pragma endregion
#pragma region redVerticalScrollBar
	BScrollBar* redVerticalScrollBar;
	void redVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e);
#pragma endregion
#pragma region greenVerticalScrollBar
	BScrollBar* greenVerticalScrollBar;
	void greenVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e);
#pragma endregion
#pragma region blueVerticalScrollBar
	BScrollBar* blueVerticalScrollBar;
	void blueVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e);
#pragma endregion
#pragma region horizontalScrollBar
	BScrollBar* horizontalScrollBar;
#pragma endregion
	BRadioButton* radioButton1;
	BRadioButton* radioButton2;
	BRadioButton* radioButton3;
#pragma region Menu declarations
	BMainMenu* mainMenu;
	BMenu* fileMenu;
	BMenuItem* fileNewMenu;
#pragma region fileOpenMenu
	BMenuItem* fileOpenMenu;
	void fileOpenMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BMenu* fileOpenRecentSubMenu;
	BMenuItem* fileOpenRecentSubMenu1;
	BMenuItem* fileOpenRecentSubMenu2;
	BMenuItem* fileOpenRecent3Menu;
	BMenuItem* fileSaveMenu;
#pragma region fileBrowseFolderMenu
	BMenuItem* fileBrowseFolderMenu;
	void fileBrowseFolderMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BMenuItem* fileCloseMenu;
#pragma region fileExitMenu
	BMenuItem* fileExitMenu;
	void fileExitMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BMenu* editMenu;
	BMenuItem* editCutMenu;
	BMenuItem* editCopyMenu;
	BMenuItem* editPasteMenu;
	BMenu* toolsMenu;
#pragma region toolsOptionsMenu
	BMenuItem* toolsOptionsMenu;
	void toolsOptionsMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BMenu* viewMenu;

#pragma region notificationIconViewSubMenu
	BMenu* notificationIconViewSubMenu;
	BMenuItem* notificationIconShowViewMenu;
	BMenuItem* notificationIconHideViewMenu;
	BMenuItem* notificationIconBaloonViewMenu;
	void notificationIconShowViewMenu_onClick(void * sender, EventArguments& e);
	void notificationIconHideViewMenu_onClick(void * sender, EventArguments& e);
	void notificationIconBaloonViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region groupBoxViewMenu
	BMenuItem* groupBoxViewMenu;
	void groupBoxViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region treeViewViewMenu
	BMenuItem* treeViewViewMenu;
	void treeViewViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region listViewViewMenu
	BMenuItem* listViewViewMenu;
	void listViewViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region progressViewMenu
	BMenuItem* progressViewMenu;
	void progressViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion	
#pragma region scrollBarsViewMenu
	BMenuItem* scrollBarsViewMenu;
	void scrollBarsViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region radioButtonsViewMenu
	BMenuItem* radioButtonsViewMenu;
	void radioButtonsViewMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BMenu* helpMenu;

	BMenuItem* helpContentMenu;
#pragma region helpAboutMenu
	BMenuItem* helpAboutMenu;
	void helpAboutMenu_onClick(void * sender, EventArguments& e);
#pragma endregion
	BPopUpMenu* popUpMenu;
#pragma region startMenuItem
	BMenuItem* startMenuItem;
	void popupMenuStart_onClick(void * sender, EventArguments& e);
#pragma endregion
#pragma region startMenuItem
	BMenuItem* stopMenuItem;
	void popupMenuStop_onClick(void * sender, EventArguments& e);
#pragma endregion

	SettingsForm* settingsForm;
	BNotificationIcon* notificationIcon;
	BIconList* iconList;

#pragma region MainForm
	void initialize();
	void onClose(void * sender, CancelEventArguments& e);
	void onCreate(void * sender, CreateEventArguments& e);
	void onResize(int width, int heihgt);
#pragma endregion
};

