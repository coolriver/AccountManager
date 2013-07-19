#include "StdAfx.h"
#include "TableYearIn.h"
#include "TableMonthIn.h"
#define TABLE_LIST                      1227
#define COMBOX                          1029

TableYearIn::TableYearIn(void)
{
}


TableYearIn::~TableYearIn(void)
{
}


BOOL TableYearIn::OnInitDialog()
{
	TableFather::OnInitDialog();
	CString title = "";
	title.Format("%d年收入记录",Date.GetYear());
	this->SetWindowText(title);
	// TODO:  在此添加额外的初始化
	m_imlNull.Create(18, 18, ILC_COLORDDB|ILC_MASK, 2, 2);
	table_list.SetImageList(&m_imlNull, LVSIL_SMALL);
	LONG IStyle;
	IStyle=GetWindowLong(table_list.m_hWnd,GWL_STYLE);
	IStyle|=LVS_REPORT;
	SetWindowLong(table_list.m_hWnd,GWL_STYLE,IStyle);
	DWORD dwstyle=table_list.GetExtendedStyle();
	dwstyle|=LVS_EX_FULLROWSELECT;
	dwstyle|=LVS_EX_GRIDLINES;
	dwstyle |= LVS_EX_INFOTIP;
	//dwstyle|=LVS_EX_CHECKBOXES;
	//dwstyle|=LVS_EX_CHECKBOXES;
	table_list.SetExtendedStyle(dwstyle);
	table_list.InsertColumn(0, "",LVCFMT_LEFT, 0);

	table_list.InsertColumn(1,"序号",LVCFMT_CENTER);
	table_list.InsertColumn(2,"金额",LVCFMT_RIGHT);
	table_list.InsertColumn(3,"收入对象",LVCFMT_CENTER);
	table_list.InsertColumn(4,"收入月份",LVCFMT_CENTER);
	table_list.SetColumnWidth(1,40);
	table_list.SetColumnWidth(2,120);
	table_list.SetColumnWidth(3,120);
	table_list.SetColumnWidth(4,100);

	if (NULL == year_p)
	{
		return TRUE;
	}
	//Records rp = month_p->records;
	int row,i,j;
	for (i = 0,j = 0;i < 12;i++)
	{
		if (NULL != year_p->month_records[i])
		{
			j++;
			CString num,money,direct,month;
			num.Format("%d",j);
			money.Format("%.1lf",year_p->month_records[i]->get_month_money_in_cash() + year_p->month_records[i]->get_month_money_in_card());
			direct = "全部";
			month.Format("%d",i+1);
			row = table_list.InsertItem(j-1,"");
			table_list.SetItemText(row,1,num);
			table_list.SetItemText(row,2,money);
			table_list.SetItemText(row,3,direct);
			table_list.SetItemText(row,4,month);			
		}
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void TableYearIn::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	//MessageBox("dbclick");
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,TABLE_LIST);
    RECT rect;
    //get the row number

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;

	if (-1 != nItem)
	{
		TableMonthIn table_dlg;
		table_dlg.Date = Date;
		
	//cur_dayp->records->record_info = "sadf";
		CString str = GetItemText(hWnd1,nItem ,4);
		table_dlg.month_p = year_p->month_records[(int)atof(str)-1];
		table_dlg.Date.SetDate(Date.GetYear(),Date.GetMonth(),(int)atof(str));
		table_dlg.set_cards(cards);
		table_dlg.DoModal();
	}
	*pResult = 0;
}

void TableYearIn::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	//MessageBox("dbclick");
	CString str;
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,TABLE_LIST);
    RECT rect;
    //get the row number

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;
	if (-1 != nItem && 3 == nSubItem)
	{
		ListView_GetSubItemRect(hWnd1,temp->iItem,temp->iSubItem,LVIR_BOUNDS,&rect);
		RECT rect1,rect2;
		str = GetItemText(hWnd1,nItem ,3);
		::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog

	//::GetClientRect(m_hWnd,&rect2);
		::GetWindowRect(m_hWnd,&rect2);
		ScreenToClient(&rect1);
		int x = rect1.left;
		int y = rect1.top;
		combox.ResetContent();
		combox.AddString("全部");
		combox.AddString("现金");
		combox.AddString("银行卡(总)");
		for (int i = 0;i < MAXCARD;i++)
		{
			if ("" != cards[i])
			{
				combox.AddString(cards[i]);
			}
		}
		combox.SelectString(0,str);
		::SetWindowPos(::GetDlgItem(m_hWnd,COMBOX),
        HWND_TOP,rect.left+x+1,rect.top+y+1, 
        rect.right-rect.left+1,
        rect.bottom-rect.top+1,NULL);
		::ShowWindow(::GetDlgItem(m_hWnd,COMBOX),SW_SHOW);
		::SetFocus(::GetDlgItem(m_hWnd,COMBOX));

	}
	*pResult = 0;
}

void TableYearIn::OnCbnSelchangeCombox()
{
	// TODO: 在此添加控件通知处理程序代码
    CString str;
  //if the control is the EditBox 


        //get the text from the EditBox

    GetDlgItemText(COMBOX,str);

        //set the value in the listContorl with the

        //specified Item & SubItem values

    SetCell(::GetDlgItem (m_hWnd,TABLE_LIST),str,nItem,nSubItem);
	::SendDlgItemMessage(m_hWnd,COMBOX,WM_KILLFOCUS,0,0);
    ::ShowWindow(::GetDlgItem(m_hWnd,COMBOX),SW_HIDE);

	int day;
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,TABLE_LIST);
	day = (int)atof(GetItemText(hWnd1,nItem ,4));
	CString money;
	if ("现金" == str)
	{
		money.Format("%.1lf",year_p->month_records[day-1]->get_month_money_in_cash());
	}
	else if ("银行卡(总)" == str)
	{
		money.Format("%.1lf",year_p->month_records[day-1]->get_month_money_in_card());
	}
	else if ("全部" == str)
	{
		money.Format("%.1lf",year_p->month_records[day-1]->get_month_money_in_cash() + year_p->month_records[day-1]->get_month_money_in_card());
	}
	else
	{
		money.Format("%.1lf",year_p->month_records[day-1]->get_month_money_in_cards(FindCard(str)));
	}
	SetCell(::GetDlgItem (m_hWnd,TABLE_LIST),money,nItem,2);
}


void TableYearIn::OnCbnKillfocusCombox()
{
	// TODO: 在此添加控件通知处理程序代码
	::ShowWindow(::GetDlgItem(m_hWnd,COMBOX),SW_HIDE);
}
