#pragma once
#include "tablefather.h"
#include "MonthRecord.h"
class TableMonthOut :
	public TableFather
{
public:
	int nItem;
	int nSubItem;
	MonthRecord * month_p;
	TableMonthOut(void);
	~TableMonthOut(void);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombox();
	afx_msg void OnCbnKillfocusCombox();
	virtual BOOL OnInitDialog();
};

