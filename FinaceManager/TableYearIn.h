#pragma once
#include "tablefather.h"
#include "YearRecord.h"
class TableYearIn :
	public TableFather
{
public:
	int nItem;
	int nSubItem;
	YearRecord * year_p;
	TableYearIn(void);
	~TableYearIn(void);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombox();
	afx_msg void OnCbnKillfocusCombox();
	virtual BOOL OnInitDialog();
};

