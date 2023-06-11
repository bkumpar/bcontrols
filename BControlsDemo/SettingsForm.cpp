#include "stdafx.h"
#include "SettingsForm.h"

SettingsForm::SettingsForm(BVisualControl* parent, HINSTANCE hInstance, int nCmdShow, HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName )
	:BForm(parent, hInstance, nCmdShow, icon, iconSmall, cursor, menuName )
{
		initialize();
}
	
SettingsForm::~SettingsForm(void)
{


}

void SettingsForm::initialize()
{
	this->setCloseEventHandler(this, BForm::CloseHandler(&SettingsForm::onClose));
	this->setCreateEventHandler(this, BForm::CreateHandler(&SettingsForm::onCreate));
	this->setResizeEventHandler(this, BForm::ResizeHandler(&SettingsForm::onResize));
}

void SettingsForm::onClose(void * sender, CancelEventArguments& e)
{
	e.cancel =  IDNO == MessageBox(this->hWnd(), L"Are you sure to close form??", L"Exit", MB_YESNO | MB_ICONEXCLAMATION );
}

void SettingsForm::onCreate(void * sender, CreateEventArguments& e)
{
#pragma region tabControl
	tabControl = new BTabControl(this, L"Tab settings", 20, 20, this->width()-40, this->height()-40) ;
	tabPage1 = tabControl->addPage(L"First page", 0);
	tabPage2 = tabControl->addPage(L"Second page", 1);
	testButton1 = new BButton(tabPage1,L"TEST 1", 50,50,90,32);
	testButton2 = new BButton(tabPage2,L"TEST 2", 50,90,90,32);
	tabPage1->setVisible(false);
	tabPage2->setVisible(true);
	tabControl->setVisible(true);

#pragma endregion
}

void SettingsForm::onResize(int width, int heihgt)
{

}

void SettingsForm::close()
{


}


