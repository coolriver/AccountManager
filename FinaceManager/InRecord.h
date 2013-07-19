#pragma once
#include "DayRecord.h"
#include "afxwin.h"

// InRecord �Ի���

class InRecord : public CDialog
{
	DECLARE_DYNAMIC(InRecord)

public:
	InRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InRecord();
	void set_cards(CString * card);

// �Ի�������
	enum { IDD = ADD_IN_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL IsFloat(CString &str, int ID);
	CString cards[MAXCARD];
	afx_msg void OnBnClickedSubmit();
	virtual BOOL OnInitDialog();
	CComboBox in_type_combox;
	CComboBox in_card_combox;
	afx_msg void OnCbnSelchangeTypeCombox();
	afx_msg void OnBnClickedBack();
};
