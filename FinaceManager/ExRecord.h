#pragma once
#include "afxwin.h"
#include "DayRecord.h"

// ExRecord �Ի���

class ExRecord : public CDialog
{
	DECLARE_DYNAMIC(ExRecord)

public:
	ExRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ExRecord();
	void set_cards(CString * card);
// �Ի�������
	enum { IDD = ADD_EX_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
