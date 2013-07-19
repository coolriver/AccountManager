#pragma once
#include "TableFather.h"
#include "DayRecord.h"
class TableDayIn :
	public TableFather
{
public:
	
	DayRecord * day_p;
	TableDayIn(void);
	~TableDayIn(void);
	virtual BOOL OnInitDialog();
};

