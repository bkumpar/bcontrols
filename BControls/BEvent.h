#pragma once

#include "StdAfx.h"
#include "ExportImport.h"

IMPORT_EXPORT class EventArguments
{
public:
	EventArguments(){};
};

IMPORT_EXPORT class TimerEventArguments : public EventArguments
{
public:
	 TimerEventArguments(DWORD time )
		 : time(time){};
	 DWORD time;
};

IMPORT_EXPORT class MouseEventArguments : public EventArguments
{
 public:
    MouseEventArguments(int button, int xPos, int yPos, int delta = 0)
		: button(button), xPos(xPos), yPos(yPos), delta(delta) {};

	int button;
    int xPos;
    int yPos;
    int delta;
};

IMPORT_EXPORT class CancelEventArguments : public EventArguments
{
 public:
    CancelEventArguments(bool cancel)
		:cancel(cancel){};

	bool cancel;
};

IMPORT_EXPORT class CreateEventArguments : public EventArguments
{
 public:
    CreateEventArguments(HWND hWnd)
		: hWnd(hWnd) {};

	HWND hWnd;
};

IMPORT_EXPORT class MoveEventArguments : public EventArguments
{
 public:
    MoveEventArguments(	int left,int top,int width,	int height)
		:	left(left), top(top), width(width),	height(height) {}; 

	int left; 
	int top; 
	int width;
	int height;

};


IMPORT_EXPORT class PaintEventArguments : public EventArguments
{
 public:
    PaintEventArguments(HWND hWnd, PAINTSTRUCT ps,HDC hdc)
		: hWnd(hWnd), ps(ps), hdc(hdc) {};

	const HWND hWnd;
	PAINTSTRUCT ps;
	HDC hdc;
};

IMPORT_EXPORT class ChangeEventArguments : public EventArguments
{
 public:
    ChangeEventArguments(HWND hWnd) 
		: hWnd(hWnd){}; 
	const HWND hWnd;
};