#pragma once
#include "YearRecord.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "InRecord.h"
#include "OutRecord.h"
#include "TableDayIn.h"
#include "TableDayOut.h"
#include "TableMonthIn.h"
#include "TableMonthOut.h"
#include "TableYearIn.h"
#include "TableYearOut.h"
#include "ExRecord.h"
// MainMenue 对话框
typedef struct yyear
{
	YearRecord * year_record;
	struct yyear * next;
}Year,*Years;

class MainMenue : public CDialog
{
	DECLARE_DYNAMIC(MainMenue)

public:
	BOOL not_save;
	COleDateTime  Date;
	Years years;
	CString cards[MAXCARD];
	InRecord *inrecord;
	MainMenue(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MainMenue();

// 对话框数据
	enum { IDD = MAIN_MENUE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnMyMessage1(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	//BOOL state_day;
	//BOOL state_month;
	//BOOL state_year;
	Years cur_yearp;
	MonthRecord * cur_monthp;
	DayRecord * cur_dayp;
	void FlushMenue();
	void CheckState();
	int FindCard(CString);
    void insert_record(Records record);
	BOOL CheckDate();
	Years search_year(int year);
	MonthRecord * search_month(int month,Years year);
	DayRecord * search_day(int day,MonthRecord * month);
	virtual BOOL OnInitDialog();
	CComboBox day_start_combox;
	CComboBox day_end_combox;
	CComboBox day_out_combox;
	CComboBox day_in_combox;
	CComboBox month_start_combox;
	CComboBox month_end_combox;
	CComboBox month_out_combox;
	CComboBox month_in_combox;
	CComboBox year_start_combox;
	CComboBox year_end_combox;
	CComboBox year_out_combox;
	CComboBox year_in_combox;
	CDateTimeCtrl date_ctrl;
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnCbnSelchangeStartCombox();
	afx_msg void OnCbnSelchangeEndCombox();
	afx_msg void OnCbnSelchangeOutCombox();
	afx_msg void OnCbnSelchangeInCombox();
	afx_msg void OnCbnSelchangeStartComboxm();
	afx_msg void OnCbnSelchangeEndComboxm();
	afx_msg void OnCbnSelchangeOutComboxm();
	afx_msg void OnCbnSelchangeInComboxm();
	afx_msg void OnCbnSelchangeStartComboxy();
	afx_msg void OnCbnSelchangeEndComboxy();
	afx_msg void OnCbnSelchangeOutComboxy();
	afx_msg void OnCbnSelchangeInComboxy();
	afx_msg void OnBnClickedDe();
	BOOL SaveData();
	BOOL LoadData();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedIn();
	afx_msg void OnBnClickedOut();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedInm();
	afx_msg void OnBnClickedOutm();
	afx_msg void OnBnClickedIny();
	afx_msg void OnBnClickedOuty();
	afx_msg void OnBnClickedEx();
};
