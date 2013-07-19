#pragma once
#include "DayRecord.h"
#include "afxwin.h"

// OutRecord 对话框

class OutRecord : public CDialog
{
	DECLARE_DYNAMIC(OutRecord)

public:
	OutRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OutRecord();
	void set_cards(CString * card);
// 对话框数据
	enum { IDD = ADD_OUT_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL IsFloat(CString &str, int ID);
	CString cards[MAXCARD];
	CComboBox out_type_combox;
	CComboBox out_card_combox;
	afx_msg void OnCbnSelchangeTypeCombox();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedSubmit();
	virtual BOOL OnInitDialog();
};
