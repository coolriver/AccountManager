#pragma once
#include "tablefather.h"
#include "MonthRecord.h"
class TableMonthIn :
	public TableFather
{
public:
	int nItem;
	int nSubItem;
	MonthRecord * month_p;
	TableMonthIn(void);
	~TableMonthIn(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombox();
	afx_msg void OnCbnKillfocusCombox();
	
};

