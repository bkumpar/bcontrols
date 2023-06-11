#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BVisualControl.h"

IMPORT_EXPORT class BScrollBar:public BVisualControl
{
public:
	enum ScrollBarOrientation
	{
		vertical =  SBS_VERT ,
		horzontal = SBS_HORZ
	};

	BScrollBar(void);
	BScrollBar(  BVisualControl* parent, int left, int top, int width, int height, ScrollBarOrientation orientation);
	virtual ~BScrollBar(void);
	void setRange(int minValue, int maxValue);
	int minValue();
	int maxValue();
	void setValue(int value);
	int value();
	void setPage(int pageSize);
	int page(int pageSize);
	void setSmallStep(int value);
	int smallStep();
	void setLargeStep(int value);
	int largeStep();

private:
	HWND createControl(HWND hwndParent, int left, int top, int width, int height, ScrollBarOrientation orientation);
	int _smallStep;
	int _largeStep;
};

