#include "StdAfx.h"
#include "BVisualControl.h"



BVisualControl::BVisualControl()
	: BControl()
{

}

BVisualControl::BVisualControl(BVisualControl* parent) 
	:  BControl(parent->hWnd()), _parent(parent)
{
	_backgroundMode=transparent;
	_textColor = RGB(0, 0, 0);
}

BVisualControl::~BVisualControl()
{
	_backgroundMode=transparent;
	_textColor = RGB(0, 0, 0);
}

BVisualControl* BVisualControl::parent()
{
	return _parent;
}


void BVisualControl::setBackgroundColor(BColor color)
{
	_backgroundColor = color;
	RedrawWindow(this->hWnd(), NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

BColor BVisualControl::backgroundColor()
{
	return _backgroundColor;
}

void BVisualControl::setBackgroundMode(BBackgroundMode backgroundMode )
{
	_backgroundMode = backgroundMode;

}
BBackgroundMode BVisualControl::backgroundMode()
{
	return _backgroundMode;

}

void BVisualControl::setTextColor(BColor color)
{
	_textColor = color;
}

BColor BVisualControl::textColor()
{
	return _textColor;
}
