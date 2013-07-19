#pragma once
#include "afxwin.h"
#include "DayRecord.h"

// ExRecord 对话框

class ExRecord : public CDialog
{
	DECLARE_DYNAMIC(ExRecord)

public:
	ExRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ExRecord();
	void set_cards(CString * card);
// 对话框数据
	enum { IDD = ADD_EX_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int FindCard(CString);
	BOOL IsFloat(CString &str, int ID);
	CString cards[MAXCARD];
	CComboBox combox_from;
	CComboBox combox_to;
	afx_msg void OnCbnSelchangeComboxFrom();
	afx_msg void OnCbnSelchangeComboxTo();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedSubmit();
	virtual BOOL OnInitDialog();
};
