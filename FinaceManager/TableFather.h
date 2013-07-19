#pragma once
#include "afxcmn.h"
#include "DayRecord.h"
#include "afxwin.h"
#define TABLEDLG                        137
// TableFather 对话框

class TableFather : public CDialog
{
	DECLARE_DYNAMIC(TableFather)

public:
	TableFather(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TableFather();
	void set_cards(CString * card);
// 对话框数据
	enum { IDD = TABLEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime  Date;
	CImageList m_imlNull;
	CListCtrl table_list;
	CString cards[MAXCARD];
	afx_msg void OnBnClickedBack();
	virtual afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem);
	CComboBox combox;
	virtual afx_msg void OnCbnSelchangeCombox();
	virtual afx_msg void OnCbnKillfocusCombox();
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	int FindCard(CString str);
};
