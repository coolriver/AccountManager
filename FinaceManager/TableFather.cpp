// TableFather.cpp : 实现文件
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "TableFather.h"
#include "afxdialogex.h"


// TableFather 对话框

IMPLEMENT_DYNAMIC(TableFather, CDialog)

TableFather::TableFather(CWnd* pParent /*=NULL*/)
	: CDialog(TableFather::IDD, pParent)
{

}

TableFather::~TableFather()
{
}

void TableFather::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, TABLE_LIST, table_list);
	DDX_Control(pDX, COMBOX, combox);
}


BEGIN_MESSAGE_MAP(TableFather, CDialog)
	ON_BN_CLICKED(TABLE_BACK, &TableFather::OnBnClickedBack)
	ON_NOTIFY(NM_CLICK, TABLE_LIST, &TableFather::OnNMClickList)
	ON_NOTIFY(NM_DBLCLK, TABLE_LIST, &TableFather::OnNMDblclkList)
	ON_CBN_SELCHANGE(COMBOX, &TableFather::OnCbnSelchangeCombox)
	ON_CBN_KILLFOCUS(COMBOX, &TableFather::OnCbnKillfocusCombox)
END_MESSAGE_MAP()


// TableFather 消息处理程序
void TableFather::set_cards(CString * card)
{
	for (int i = 0;i < MAXCARD;i++)
	{
		this->cards[i] = card[i];
		//MessageBox(card[i]);
	}
}

void TableFather::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void TableFather::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void TableFather::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}

CString TableFather::GetItemText(HWND hWnd, int nItem, int nSubItem)
{
	LVITEM lvi;
    memset(&lvi, 0, sizeof(LVITEM));
    lvi.iSubItem = nSubItem;
    CString str;
    int nLen = 128;
    int nRes;
    
        nLen *= 2;
        lvi.cchTextMax = nLen;
        lvi.pszText = str.GetBufferSetLength(nLen);
        nRes  = (int)::SendMessage(hWnd, 
            LVM_GETITEMTEXT, (WPARAM)nItem,
            (LPARAM)&lvi);
	
    str.ReleaseBuffer();
    return str;
}

void TableFather::OnCbnSelchangeCombox()
{
	// TODO: 在此添加控件通知处理程序代码
}


void TableFather::OnCbnKillfocusCombox()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TableFather::SetCell(HWND hWnd1, CString value, int nRow, int nCol)
{
	TCHAR     szString [256];
    wsprintf(szString,value ,0);

    //Fill the LVITEM structure with the 

    //values given as parameters.

    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nRow;
    lvItem.pszText = szString;
    lvItem.iSubItem = nCol;
    if(nCol >0)
        //set the value of listItem

        ::SendMessage(hWnd1,LVM_SETITEM, 
            (WPARAM)0,(WPARAM)&lvItem);
    else
        //Insert the value into List

        ListView_InsertItem(hWnd1,&lvItem);
}

int TableFather::FindCard(CString str)
{
	for (int i = 0;i < MAXCARD;i++)
	{
		if (str == cards[i])
		{
			return i;
		}
	}
	return -1;
}