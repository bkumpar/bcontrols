#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BEvent.h"
#include "BFont.h"
#include <map>

#define BWM_CLICKED  WM_USER + 1
#define WM_TRAYICON WM_USER + 2

typedef void * DataPtr;
extern int firstID;
extern std::map<int, HWND> _idToHandle; 
typedef COLORREF BColor;
typedef enum {
	opaque = OPAQUE,
	transparent = TRANSPARENT
} BBackgroundMode;

IMPORT_EXPORT class BControl 
{
public:
	typedef void (BControl::*ClickHandler)(void*, EventArguments &e);
	typedef void (BControl::*MouseDownHandler)(void*, MouseEventArguments &e);
	typedef void (BControl::*MouseWheelHandler)(void*, MouseEventArguments &e);
	typedef void (BControl::*CreateHandler)(void*, EventArguments &e);
	typedef void (BControl::*ResizeHandler)(void*, EventArguments &e);
	typedef void (BControl::*PaintHandler)(void*, PaintEventArguments &e);
	typedef void (BControl::*ChangeHandler)(void*, EventArguments &e);
	
	BControl(void);
	BControl(HWND parent);
	virtual ~BControl(void);
	HWND hWnd(void);
	int id(void);
	HWND hWndParent(void);

    void setText(std::wstring text);
	std::wstring text(void);
    
    void setXPos(LONG xPos);
    LONG xPos();
    
    void setYPos(LONG yPos);
    LONG yPos();
    
    void setWidth(LONG width);
    LONG width(void);
    
    void setHeight(LONG height);
    LONG height();

	void setFont(BFont& font);
	
	void setData(DataPtr data);
	DataPtr getData();

	void setVisible(bool visible);
	bool visible();

	void setEnabled(bool enable);
	bool enabled();

	void setCustomPaint(bool enable);
	bool customPaint();


	void setClickEventHandler(void* target, ClickHandler handler);
	void setMouseDownEventHandler(void* target, MouseDownHandler handler);
	void setMouseWheelEventHandler(void* target, MouseWheelHandler handler);
	void setCreateEventHandler(void* target, CreateHandler handler);
	void setResizeEventHandler(void* target, ResizeHandler handler);
	void setPaintEventHandler(void* target, PaintHandler handler);
	void setChangeEventHandler(void* target, ChangeHandler handler);

	void click();
    void mouseUp(UINT button, int xPos,int yPos);
    void mouseDown(UINT button, int xPos,int yPos);
    void mouseWheel(UINT button, int xPos,int yPos, int delta);
	void resize(EventArguments& e);
	void create(CreateEventArguments& e);
	void move(EventArguments& e);
	void paint(PaintEventArguments& e);
	void change(ChangeEventArguments& e);

private:
	int nextID();
	bool _customPaint;
	HBRUSH _hbrBkgnd;

protected:
	HWND _hWnd;
	int _id;
	HWND _hWndParent;
	std::wstring _text;
	void setWindowPos(RECT rect);
//	HWND createControl(HWND hwndParent, RECT rect );

	static LRESULT CALLBACK  subWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	LRESULT CALLBACK  realSubWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

	DataPtr _data;
	BColor _textColor;
	BColor _backgroundColor;
	BBackgroundMode _backgroundMode;

	ClickHandler _clickHandler;
	void * _clickTarget;
	
	MouseDownHandler _mouseDownHandler;
	void * _mouseDownTarget;
	
	MouseWheelHandler _mouseWheelHandler;
	void * _mouseWheelTarget;

	CreateHandler _createHandler;
	void * _createTarget;
	ResizeHandler _resizeHandler;
	void * _resizeTarget;

	PaintHandler _paintHandler;
	void * _paintTarget;

	ChangeHandler _changeHandler;
	void * _changeTarget;


};

