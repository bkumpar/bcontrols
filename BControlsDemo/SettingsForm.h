#pragma once
#include <BForm.h>
#include <BTabControl.h>
#include <BTabPage.h>
#include <BButton.h>

class SettingsForm : public BForm
{
public:
	SettingsForm(BVisualControl* parent,HINSTANCE hInstance, int nCmdShow, HICON icon,HICON iconSmall, HCURSOR cursor, LPCWSTR menuName );
	virtual ~SettingsForm(void);
	void close();
private:

#pragma region tabControl
	BTabControl* tabControl;
#pragma endregion

#pragma region tabPages
	BTabPage * tabPage1;
	BTabPage * tabPage2;
#pragma endregion

#pragma region testButton
	BButton * testButton1;
	BButton * testButton2;
#pragma endregion

#pragma region SettingsForm
	void initialize();
	void onClose(void * sender, CancelEventArguments& e);
	void onCreate(void * sender, CreateEventArguments& e);
	void onResize(int width, int heihgt);
#pragma endregion

};

