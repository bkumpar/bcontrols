#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BProgressBar.h"
#include "BVisualControl.h"
#include <ctime>

#define UNKNOWN_TIME ((std::time_t) -1)

IMPORT_EXPORT class BProgressBar:public BVisualControl
{
public:
	
	BProgressBar(void);
	BProgressBar(  BVisualControl* parent, int left, int top, int width, int height);
	virtual ~BProgressBar(void);
	void setRange(int minValue, int maxValue);
	int minValue();
	int maxValue();
	void setStepValue(int value);
	int stepValue();
	void setValue(int value);
	int value();
	std::time_t elapsedTime();
	std::time_t estimatedTime();
	void resetTimer();

private:
	std::time_t _startTime;
	HWND createControl(HWND hwndParent, int left, int top, int width, int height);
};

