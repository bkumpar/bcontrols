#pragma once

#include "StdAfx.h"
#include "ExportImport.h"
#include "BEvent.h"
#include "BFont.h"
#include "BControl.h"
#include <map>


IMPORT_EXPORT class BVisualControl : public BControl 
{
public:
	BVisualControl();
	BVisualControl(BVisualControl* parent);	
	~BVisualControl();
	BVisualControl* parent();
	void setBackgroundColor(BColor color);
	BColor backgroundColor();
	void setTextColor(BColor color);
	BColor textColor();
	void setBackgroundMode(BBackgroundMode backgroundMode);
	BBackgroundMode backgroundMode();

private:
	BVisualControl* _parent;

};