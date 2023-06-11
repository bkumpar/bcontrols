#include "stdafx.h"
#include "MainForm.h"
#include <ctime>
#include <cwchar>
#include <string>
#include <BFileDialog.h>
#include <BFolderBrowseDialog.h>
#include <BUtils.h>

#pragma region Constructors and destructor
MainForm::MainForm(HINSTANCE hInstance, int nCmdShow, HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName )
		:BForm(hInstance, nCmdShow, icon, iconSmall, cursor, menuName )
{
	initialize();
}

MainForm::~MainForm(void)
{

}
#pragma endregion

void MainForm::initialize()
{
	this->setCloseEventHandler(this, BForm::CloseHandler(&MainForm::onClose));
	this->setCreateEventHandler(this, BForm::CreateHandler(&MainForm::onCreate));
	this->setResizeEventHandler(this, BForm::ResizeHandler(&MainForm::onResize));
}

void MainForm::buttonOkOnMouseDown(void * sender, MouseEventArguments& e)
{
    switch(e.button)
    {
       case MK_LBUTTON:
		    staticText1->setText(L"LOkStatic");
			textEdit1->setText(L"LOkText1");
			groupBox->setText(L"LOkGroup");
			textEdit2->setText(L"LOkText2");
            break;
        case MK_RBUTTON:
			staticText1->setText(L"ROkStatic");
			textEdit1->setText(L"ROkText1");
			textEdit2->setText(L"ROkText2");
			groupBox->setText(L"ROkGroup");
            break;
    }
}

void MainForm::buttonCancelOnMouseDown(void * sender, MouseEventArguments& e)
{
    switch(e.button)
    {
        case MK_LBUTTON:
			close();
            break;
        case MK_RBUTTON:
			popUpMenu->show( e.xPos, e.yPos, (BVisualControl*)sender);
			//popUpMenu->show( e.xPos, e.yPos, this);
			break;
    }
}

void MainForm::buttonOkOnMouseWheel(void * sender, MouseEventArguments& e)
{
	staticText1->setText(L"wheel on buton OK");
}

void MainForm::buttonCancelOnMouseWheel(void * sender, MouseEventArguments& e)
{
	staticText1->setText(L"wheel on buton CANCEL");
}

void MainForm::textEdit1MouseDown(void * sender, MouseEventArguments& e)
{
	//BTextEdit* edit = static_cast<BTextEdit*>(e.sender);
	//edit->setText(L"Clicked!");
}

void MainForm::textEdit2MouseDown(void * sender, MouseEventArguments& e)
{
	//BTextEdit* edit = static_cast<BTextEdit*>(e.sender);
	//edit->setText(L"Clicked!");
}

void MainForm::realTimeTimer_onTimer(void * sender, TimerEventArguments& e)
{
	statusBar->setPanelText(1, now());
}

void MainForm::onClose(void * sender, CancelEventArguments& e)
{
	e.cancel =  IDNO == MessageBox(hWnd(), L"Are you sure to exit?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION );
}
	
void MainForm::close()
{
	BForm::close();
}

void MainForm::onResize(int width, int heihgt)
{
	PostMessage(statusBar->hWnd(), WM_SIZE, NULL, NULL);
}

void MainForm::groupBox_onPaint(void * sender, PaintEventArguments& e)
{
	RECT rect;
	GetClientRect(e.hWnd, &rect);
	RedrawWindow(e.hWnd,NULL,NULL, RDW_NOERASE);
	RECT rect2 = rect;
	rect2.top = rect.top+60;
	DrawText(e.hdc, L"Custom draw text - centered", -1, &rect2, DT_CENTER );
	rect2.left = rect.left + 10;
	rect2.top = rect.bottom - 40;
	DrawText(e.hdc, L"Custom draw text - left aligned", -1, &rect2, DT_SINGLELINE);  

}

std::wstring MainForm::now()
{
    wchar_t wstr[100];
	tm timeStruct ;
	std::time_t t = std::time(NULL);
	int err = localtime_s(&timeStruct, &t);
	if(err ==0)
	{
		std::wstring fmt = L"%d.%m.%Y %H:%M:%S";
		if(std::wcsftime(wstr, 100, fmt.c_str(), &timeStruct)) 
		{
			return std::wstring(wstr);
		}
	}
	return std::wstring(L"");

}

void  MainForm::fileExitMenu_onClick(void * sender, EventArguments& e)
{
	this->close();
}

void MainForm::onCreate(void * sender, CreateEventArguments& e)
{
#pragma region groupBox
	groupBox = new BGroupBox(this, L"Group Box", 50, 50, 500, 280);
	groupBox->setPaintEventHandler(this,BForm::PaintHandler(&MainForm::groupBox_onPaint));
	groupBox->setBackgroundColor(RGB(0, 255,0));
	groupBox->setCustomPaint(false);
#pragma endregion

#pragma region staticText1
	staticText1 = new BStaticText(groupBox,  L"staticText1", 50, 34, 250, 22);
	staticText1->setText(L"New static text");
	staticText1->setBackgroundMode(transparent);
	staticText1->setBackgroundColor(RGB(0, 0, 255));
#pragma endregion	

#pragma region textEdit1
	textEdit1 = new BTextEdit(groupBox, L"",  50, 94, 250, 22);
#pragma endregion	

#pragma region textEdit2
	textEdit2 = new BTextEdit(groupBox,  L"",  50, 124, 250, 22);
#pragma endregion	

#pragma region buttonCancel
	buttonCancel = new BButton(groupBox,  L"Cancel", 350, 30, 130, 30);
	buttonCancel->setClickEventHandler(this, BForm::ClickHandler(&MainForm::buttonCancel_onClick));
	buttonCancel->setMouseDownEventHandler(this, BForm::MouseDownHandler(&MainForm::buttonCancelOnMouseDown));
#pragma endregion	

#pragma region buttonOk
	buttonOk = new BButton(groupBox,  L"OK", 350, 90, 130, 30);
	buttonOk->setClickEventHandler(this, BForm::ClickHandler(&MainForm::buttonOK_onClick));
	buttonOk->setMouseWheelEventHandler(this, BForm::MouseWheelHandler(&MainForm::buttonOK_onClick));
#pragma endregion	

#pragma region comboBox
	comboBox = new BComboBox(groupBox,  L"Combo", 50, 154, 250, 22);
	comboBox->addItem(L"jpg");
	comboBox->addItem(L"mp4");
	comboBox->addItem(L"png");
	comboBox->addItem(L"pdf");
#pragma endregion	

#pragma region checkBox
	checkBox = new BCheckBox(groupBox,  L"CheckBox", 50, 186, 250, 22);
	checkBox->setBackgroundMode(transparent);
	checkBox->setBackgroundColor(RGB(250, 0, 0));
	checkBox->setTextColor(RGB(0, 250, 0));
	checkBox->setClickEventHandler(this, BForm::ClickHandler(&MainForm::checkBox_onClick));
#pragma endregion	

#pragma region statusBar
	statusBar = this->createStatusBar(2);
#pragma endregion	

#pragma region groupBoxProgress
	groupBoxProgress = new BGroupBox(this, L"Test progress bar"
							, groupBox->xPos() + groupBox->width() + 50
							, groupBox->yPos() 
							, 300
							, 150); 
	groupBoxProgress->setBackgroundColor(RGB(0, 255,255));
#pragma endregion	

#pragma region progressBar
	progressBar = new BProgressBar(groupBoxProgress
									, 20
									, 30
									, 250
									, 32 );
	progressBar->setRange(0, 100);
	progressBar->setValue(0);
#pragma endregion	

#pragma region buttonTestProgress
	buttonTestProgress = new BButton(groupBoxProgress, L"Start test"
										, 100
										, progressBar->yPos() + progressBar->height() + 20
										, 100
										, 30);
	buttonTestProgress->setClickEventHandler(this, BForm::ClickHandler(&MainForm::buttonTestProgress_OnClick));
#pragma endregion	
	
#pragma region progressTimer
	progressTimer = new BTimer( this->hWnd(), 100);
	progressTimer->setEventHandler(this, BTimer::OnTimerHandlerType(&MainForm::progressTimer_OnTimer));
#pragma endregion	

#pragma region realTimeTimer
	realTimeTimer = new BTimer( this->hWnd(), 1000);
	realTimeTimer->setEventHandler(this, BTimer::OnTimerHandlerType(&MainForm::realTimeTimer_onTimer));
	realTimeTimer->start(1000);
#pragma endregion	

#pragma region groupBoxTree
	groupBoxTree = new BGroupBox(this, L"TreeView"
								, groupBoxProgress->xPos()
								, groupBoxProgress->yPos() + groupBoxProgress->height() + 20
								, 300
								, 320);
	groupBoxTree->setBackgroundColor(RGB(0, 255,127));
#pragma region 

#pragma endregion treeView	
	treeView = new BTreeView(groupBoxTree,  L"tree view"
							, 20
							, 30
							, groupBoxTree->width() - 50
							, groupBoxTree->height() - 50);

	BTreeViewItem* root = treeView->addRoot(L"root");
	BTreeViewItem* item = root->addItem( L"item 1");
	BTreeViewItem* item2 = root->addItem( L"item 1");

	item = item2->addItem( L"item 2.1");
	item2 = root->addItem( L"item 2.1.1");
	item = item2->addItem( L"item 2.1");
	item = item2->addItem( L"item 2.1.1");
#pragma endregion	

#pragma region groupBoxList
	groupBoxList = new BGroupBox (this, L"ListView"
									, groupBox->xPos()
									, groupBox->yPos() +  groupBox->height() + 20
									, groupBox->width()
									, 200);
	groupBoxList->setBackgroundColor(RGB(255, 0, 127));
#pragma endregion	

#pragma region listView
	listView = new BListView(groupBoxList,  L"LIST_VIEW"
								, 20
								, 30
								, groupBoxList->width() - 50
								, groupBoxList->height() - 50);
	BListView* lv = listView;
	lv->addColumn(L"Column1", 1, 80);
	lv->addColumn(L"Column2", 2, 100);
	lv->addColumn(L"Column3", 3, 80);
	// 1st row
	BListViewItem* lvi = listView->addItem(L"Item11", 0);
	lvi->addSubItem(L"Item12", 1);
	lvi->addSubItem(L"Item13", 2);
	//2nd row
	lvi = listView->addItem(L"Item21", 1);
	lvi->addSubItem(L"Item22", 1);
	lvi->addSubItem(L"Item23", 2);
	// 3rd row
	lvi = listView->addItem(L"Item31", 2);
	BListViewSubItem* lvsi = lvi->addSubItem(L"Subitem32", 1);
	lvi->setText(L"Item31a");
	lvsi->setText(L"Subitem32a");
	std::wstring s1 = lvi->text();
	std::wstring s2 = lvsi->text();
	//textEdit1->setText(s1);
	//textEdit2->setText(s2);
#pragma endregion	

#pragma region groupBoxScrollBars
	groupBoxScrollBars = new BGroupBox(this, L"ScrollBars"
								, groupBoxProgress->xPos() + groupBoxProgress->width() + 20
								, groupBoxProgress->yPos()
								, 200
								, 300);
	//groupBoxScrollBars->setPaintEventHandler(this,BForm::PaintHandler(&MainForm::groupBoxScrollBars_onPaint));
	groupBoxScrollBars->setBackgroundMode(opaque);
	groupBoxScrollBars->setBackgroundColor(RGB(250, 250, 0));
	groupBoxScrollBars->setTextColor(RGB(255, 0, 0));
	groupBoxScrollBars->setCustomPaint(false);
#pragma endregion	

#pragma region redVerticalScrollBar
	redVerticalScrollBar = new BScrollBar(groupBoxScrollBars
								, groupBoxScrollBars->width() - 120
								, 30
								, 20
								, groupBoxScrollBars->height() - 70
								, BScrollBar::vertical);
	redVerticalScrollBar->setRange(0, 255);
	redVerticalScrollBar->setPage(0);
	redVerticalScrollBar->setSmallStep(1);
	redVerticalScrollBar->setLargeStep(16);
	redVerticalScrollBar->setValue( 127 );
	redVerticalScrollBar->setChangeEventHandler(this, BControl::ChangeHandler(&MainForm::redVerticalScrollBar_onChange));
#pragma endregion

#pragma region greenVerticalScrollBar
	greenVerticalScrollBar = new BScrollBar(groupBoxScrollBars
								, groupBoxScrollBars->width() - 80
								, 30
								, 20
								, groupBoxScrollBars->height() - 70
								, BScrollBar::vertical);
	greenVerticalScrollBar->setRange(0, 255);
	greenVerticalScrollBar->setPage(0);
	greenVerticalScrollBar->setSmallStep(1);
	greenVerticalScrollBar->setLargeStep(16);
	greenVerticalScrollBar->setValue( 127 );
	greenVerticalScrollBar->setChangeEventHandler(this, BControl::ChangeHandler(&MainForm::greenVerticalScrollBar_onChange));
#pragma endregion

#pragma region blueVerticalScrollBar
	blueVerticalScrollBar = new BScrollBar(groupBoxScrollBars
								, groupBoxScrollBars->width() - 40
								, 30
								, 20
								, groupBoxScrollBars->height() - 70
								, BScrollBar::vertical);
	blueVerticalScrollBar->setRange(0, 255);
	blueVerticalScrollBar->setPage(0);
	blueVerticalScrollBar->setSmallStep(1);
	blueVerticalScrollBar->setLargeStep(16);
	blueVerticalScrollBar->setValue( 127);
	blueVerticalScrollBar->setChangeEventHandler(this, BControl::ChangeHandler(&MainForm::blueVerticalScrollBar_onChange));
#pragma endregion

#pragma region horizontalScrollBar
	horizontalScrollBar = new BScrollBar(groupBoxScrollBars
								, 20
								, groupBoxScrollBars->height() - 30
								, groupBoxScrollBars->width() - 40
								, 20
								, BScrollBar::horzontal) ;
	horizontalScrollBar->setRange(0, 255);
	horizontalScrollBar->setValue( 127);
#pragma endregion

#pragma region groupBoxRadioButtons
	groupBoxRadioButtons = new BGroupBox(this, L"RadioButtons"
								, groupBoxScrollBars->xPos() 
								, groupBoxScrollBars->yPos() + groupBoxScrollBars->height() + 20
								, groupBoxScrollBars->width() 
								, 120);
	groupBoxRadioButtons->setPaintEventHandler(this,BForm::PaintHandler(&MainForm::groupBoxRadioButtons_onPaint));
	groupBoxRadioButtons->setBackgroundColor(RGB(50, 50, 255));
	groupBoxRadioButtons->setCustomPaint(false);
#pragma endregion

#pragma region radioButton1
	radioButton1 = new BRadioButton(groupBoxRadioButtons
									, L"Radio button 1"
									, 20
									, 30
									, groupBoxRadioButtons->width() - 30
									, 20 );
	radioButton1->setBackgroundColor(RGB(220,220,220));
#pragma endregion

#pragma region radioButton2 
	radioButton2 = new BRadioButton(groupBoxRadioButtons
									, L"Radio button 2"
									, 20
									, radioButton1->yPos() + radioButton1->height() + 10
									, groupBoxRadioButtons->width() - 30
									, 20 );
	radioButton2->setBackgroundColor(RGB(220,220,220));
#pragma endregion

#pragma region radioButton3
	radioButton3 = new BRadioButton(groupBoxRadioButtons
									, L"Radio button 3"
									, 20
									, radioButton2->yPos() + radioButton2->height() + 10
									, groupBoxRadioButtons->width() - 30
									, 20 );
	radioButton3->setBackgroundColor(RGB(220,220,220));
	radioButton3->setTextColor(RGB(220,10,10));
#pragma endregion

#pragma region mainMenu
	mainMenu = this->createMainMenu();

#pragma region fileMenu
	fileMenu = mainMenu->addMenu( L"File");
	fileNewMenu = fileMenu->addMenuItem( L"New");
	fileOpenMenu = fileMenu->addMenuItem( L"Open");
	fileOpenMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::fileOpenMenu_onClick));
	fileOpenRecentSubMenu = fileMenu->addSubMenu( L"Open recent...");
	fileOpenRecentSubMenu1 = fileOpenRecentSubMenu->addMenuItem( L"Recently opened file1");
	fileOpenRecentSubMenu2 = fileOpenRecentSubMenu->addMenuItem( L"Recently opened file2");
	fileBrowseFolderMenu = fileMenu->addMenuItem(L"Browse Folder");
	fileBrowseFolderMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::fileBrowseFolderMenu_onClick));
	fileSaveMenu = fileMenu->addMenuItem( L"Save");
	fileCloseMenu = fileMenu->addMenuItem( L"Close");
	fileMenu->addSeparator();
	fileExitMenu = fileMenu->addMenuItem( L"Exit");
	fileExitMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::fileExitMenu_onClick));
#pragma endregion

#pragma region editMenu
	editMenu = mainMenu->addMenu(L"Edit");
	editCutMenu = editMenu->addMenuItem( L"Cut");
	editCopyMenu = editMenu->addMenuItem( L"Copy");;
	editPasteMenu = editMenu->addMenuItem( L"Paste");;
#pragma endregion
	
#pragma region toolsMenu
	toolsMenu = mainMenu->addMenu(L"Tools");
	toolsOptionsMenu = toolsMenu->addMenuItem( L"Options");
	toolsOptionsMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::toolsOptionsMenu_onClick));
#pragma endregion

#pragma region viewMenu
	viewMenu = mainMenu->addMenu(L"View");
#pragma endregion

#pragma region notificationIconViewMenu
	notificationIconViewSubMenu = viewMenu->addSubMenu( L"NotificationIcon");
	notificationIconShowViewMenu = notificationIconViewSubMenu->addMenuItem( L"Show icon");
	notificationIconShowViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::notificationIconShowViewMenu_onClick));

	notificationIconHideViewMenu = notificationIconViewSubMenu->addMenuItem( L"Hide icon");
	notificationIconHideViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::notificationIconHideViewMenu_onClick));

	notificationIconBaloonViewMenu = notificationIconViewSubMenu->addMenuItem( L"Show baloon");
	notificationIconBaloonViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::notificationIconBaloonViewMenu_onClick));

#pragma endregion

#pragma region groupBoxViewMenu
	groupBoxViewMenu = viewMenu->addMenuItem( L"GroupBox");
	groupBoxViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::groupBoxViewMenu_onClick));
	groupBoxViewMenu->setChecked(true);
#pragma endregion

#pragma region treeViewViewMenu
	treeViewViewMenu = viewMenu->addMenuItem( L"TreeView");
	treeViewViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::treeViewViewMenu_onClick));
	treeViewViewMenu->setChecked(true);
#pragma endregion

#pragma region listViewViewMenu
	listViewViewMenu = viewMenu->addMenuItem( L"ListView");
	listViewViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::listViewViewMenu_onClick));
	listViewViewMenu->setChecked(true);
#pragma endregion

#pragma region progressViewMenu
	progressViewMenu = viewMenu->addMenuItem( L"ProgressBar");
	progressViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::progressViewMenu_onClick));
	progressViewMenu->setChecked(true);
	scrollBarsViewMenu = viewMenu->addMenuItem( L"ScrollBars");
	scrollBarsViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::scrollBarsViewMenu_onClick));
	scrollBarsViewMenu->setChecked(true);
#pragma endregion
	
#pragma region radioButtonsViewMenu
	radioButtonsViewMenu = viewMenu->addMenuItem( L"RadioButtons");
	radioButtonsViewMenu->setClickEventHandler(this, BForm::ClickHandler(&MainForm::radioButtonsViewMenu_onClick));
	radioButtonsViewMenu->setChecked(true);
#pragma endregion

#pragma region helpMenu
	helpMenu = mainMenu->addMenu( L"Help");
	helpContentMenu = helpMenu->addMenuItem( L"Content");
	helpAboutMenu = helpMenu->addMenuItem( L"About");
	helpAboutMenu->setClickEventHandler(this,  BForm::ClickHandler(&MainForm::helpAboutMenu_onClick));
#pragma endregion

#pragma region popUpMenu
	popUpMenu = mainMenu->addPopUpMenu(L"");
	//popUpMenu = new BPopUpMenu();
	startMenuItem = popUpMenu->addMenuItem( L"Start");
	startMenuItem->setClickEventHandler(this, BForm::ClickHandler(&MainForm::popupMenuStart_onClick));
	popUpMenu->addSeparator();
	stopMenuItem = popUpMenu->addMenuItem( L"Stop");
	stopMenuItem->setClickEventHandler(this, BForm::ClickHandler(&MainForm::popupMenuStop_onClick));
#pragma endregion

	SetMenu(this->hWnd(), mainMenu->hMenu());
	DrawMenuBar(this->hWnd());
#pragma endregion
	
#pragma region notificationIcon
	iconList = new BIconList(GetModuleHandle(NULL));
	iconList->add(L"off", L"E:\\Resources\\off.ico");
	iconList->add(L"on", L"E:\\Resources\\on.ico");
	notificationIcon = new BNotificationIcon(this, iconList->icon(L"off"), L"Icon off");
	//notificationIcon->show();
	nicVisible=false;

#pragma endregion


}

void MainForm::buttonCancel_onClick(void * sender, EventArguments& e)
{
	this->close();
}

void MainForm::fileOpenMenu_onClick(void * sender, EventArguments& e)
{
	BFileDialog bfd(std::wstring(L"Open file"),hWnd());
	if(bfd.show()==BFileDialog::ResultOK) 
	{
		staticText1->setText(bfd.filename());
	}
}

void MainForm::fileBrowseFolderMenu_onClick(void * sender, EventArguments& e)
{
	BFolderBrowseDialog fbd;
	if(fbd.show())
	{
		staticText1->setText(fbd.folder());
	}
}

void MainForm::helpAboutMenu_onClick(void * sender, EventArguments& e)
{
	int ret = MessageBoxW( this->hWnd(), L"BControls test \nby bkumpar", L"About", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_APPLMODAL);
}

void MainForm::buttonOK_onClick(void * sender, EventArguments& e)
{
	int ret = MessageBoxW( this->hWnd(), L"BControls test \nby bkumpar", L"Button clicked", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_APPLMODAL);
}

void MainForm::popupMenuStart_onClick(void * sender, EventArguments& e)
{
	int ret = MessageBoxW( this->hWnd(), L"START", L"PopUpMenu", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_APPLMODAL);
}

void MainForm::popupMenuStop_onClick(void * sender, EventArguments& e)
{
	int ret = MessageBoxW( this->hWnd(), L"STOP", L"PopUpMenu", MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1 | MB_APPLMODAL);
}


void MainForm::notificationIconShowViewMenu_onClick(void * sender, EventArguments& e)
{
	notificationIcon->show();
	notificationIconShowViewMenu->setChecked(true);
}

void MainForm::notificationIconHideViewMenu_onClick(void * sender, EventArguments& e)
{
	notificationIcon->hide();
	notificationIconHideViewMenu->setChecked(false);
}


void MainForm::notificationIconBaloonViewMenu_onClick(void * sender, EventArguments& e)
{
	notificationIcon->showBaloon(iconList->icon(L"on"),L"Baloon title",L"Baloon text");
}


void MainForm::groupBoxViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBox->setVisible(!groupBox->visible());
	groupBoxViewMenu->setChecked(groupBox->visible());
}

void MainForm::treeViewViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBoxTree->setVisible(!groupBoxTree->visible());
	treeViewViewMenu->setChecked(groupBoxTree->visible());
}

void MainForm::listViewViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBoxList->setVisible(!groupBoxList->visible());
	listViewViewMenu->setChecked(groupBoxList->visible());
}

void MainForm::progressViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBoxProgress ->setVisible(!groupBoxProgress->visible());
	progressViewMenu->setChecked(groupBoxProgress->visible());
}

void MainForm::scrollBarsViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBoxScrollBars->setVisible(!groupBoxScrollBars->visible());
	scrollBarsViewMenu->setChecked(groupBoxScrollBars->visible());
}

void MainForm::radioButtonsViewMenu_onClick(void * sender, EventArguments& e)
{
	groupBoxRadioButtons->setVisible(!groupBoxRadioButtons->visible());
	radioButtonsViewMenu->setChecked(groupBoxRadioButtons->visible());
}

void MainForm::checkBox_onClick(void * sender, EventArguments& e)
{
	if( checkBox->checked())
	{
		staticText1->setText(L"Checked");
	}
	else
	{
		staticText1->setText(L"Unchecked");
	}
}

void MainForm::buttonTestProgress_OnClick(void* sender, EventArguments& e)
{
	progressBar->setRange(0, 1000);
	progressBar->setValue(0);
	progressBar->resetTimer();
	progressTimer->start(1000);
	((BButton*) sender)->setEnabled(false);
}

void MainForm::progressTimer_OnTimer(void* sender, EventArguments& e)
{
	int max = progressBar->maxValue();
	int min = progressBar->minValue();
	int value = progressBar->value();
	if( value < progressBar->maxValue())
	{
		value += 1;
		progressBar->setValue(value);
		int newValue = progressBar->value();
		// show elapsed time, estimated time and percentage
		std::wstring estimatedTime;
		//std::time_t t = std::time(NULL); 
		const std::time_t t = progressBar->estimatedTime();
		//const tm* lt = std::gmtime(&t);
		//wchar_t wstr[100];
		//if(std::wcsftime(wstr, 100, L"%H:%M:%S", lt)) 
		//{
		//	estimatedTime = std::wstring(wstr);
		//}
		//else
		//{
		//	estimatedTime = L"Unknown...";
		//}
		datetime_utils::format(t, estimatedTime );
		textEdit1->setText(estimatedTime);
	}
	else 
	{
		progressTimer->stop();
		progressBar->setValue(0);
		buttonTestProgress->setEnabled(true);
	}

}

void MainForm::groupBoxScrollBars_onPaint(void* sender, PaintEventArguments& e)
{


}

void MainForm::groupBoxRadioButtons_onPaint(void* sender, PaintEventArguments& e)
{

}

void MainForm::redVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e)
{
	groupBoxScrollBars->setBackgroundColor(RGB(redVerticalScrollBar->value()
												,greenVerticalScrollBar->value()
												,blueVerticalScrollBar->value()));
	RedrawWindow(groupBoxScrollBars->hWnd(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void MainForm::greenVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e)
{
	groupBoxScrollBars->setBackgroundColor(RGB(redVerticalScrollBar->value()
											,greenVerticalScrollBar->value()
											,blueVerticalScrollBar->value()));
}

void MainForm::blueVerticalScrollBar_onChange(void* sender, ChangeEventArguments& e)
{
	groupBoxScrollBars->setBackgroundColor(RGB(redVerticalScrollBar->value()
												,greenVerticalScrollBar->value()
												,blueVerticalScrollBar->value()));
	RedrawWindow(groupBoxScrollBars->hWnd(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);}

void MainForm::toolsOptionsMenu_onClick(void * sender, EventArguments& e)
{
	HINSTANCE hInstance= GetModuleHandle(NULL);
	HICON icon  = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BCONTROLS_TEST));
	HICON iconSmall = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	HCURSOR cursor = LoadCursor(NULL, IDC_ARROW);
	LPCWSTR menuName =  NULL ; //MAKEINTRESOURCE(IDM_MAIN_MENU);

	settingsForm = new SettingsForm(this,GetModuleHandle(NULL), 1, icon, iconSmall, cursor, menuName);
	settingsForm->show();
}

void MainForm::listView_onCreate(void * sender, EventArguments& e)
{
}