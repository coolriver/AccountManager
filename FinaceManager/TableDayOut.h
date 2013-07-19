#pragma once
#include "tablefather.h"
#include "DayRecord.h"
class TableDayOut :
	public TableFather
{
public:
	DayRecord * day_p;
	TableDayOut(void);
	~TableDayOut(void);
	virtual BOOL OnInitDialog();
};

