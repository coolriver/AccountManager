#include "StdAfx.h"
#include "TableMonthOut.h"
#include "TableDayOut.h"
#define TABLE_LIST                      1227
#define COMBOX                          1029

TableMonthOut::TableMonthOut(void)
{
}


TableMonthOut::~TableMonthOut(void)
{
}


BOOL TableMonthOut::OnInitDialog()
{
	TableFather::OnInitDialog();
	CString title = "";
	title.Format("%d��%d��֧����¼",Date.GetYear(),Date.GetMonth());
	this->SetWindowText(title);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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

	table_list.InsertColumn(1,"���",LVCFMT_CENTER);
	table_list.InsertColumn(2,"���",LVCFMT_RIGHT);
	table_list.InsertColumn(3,"֧��Դ",LVCFMT_CENTER);
	table_list.InsertColumn(4,"֧����",LVCFMT_CENTER);
	table_list.SetColumnWidth(1,40);
	table_list.SetColumnWidth(2,120);
	table_list.SetColumnWidth(3,120);
	table_list.SetColumnWidth(4,100);

	if (NULL == month_p)
	{
		return TRUE;
	}
	//Records rp = month_p->records;
	int row,i,j;
	for (i = 0,j = 0;i < 31;i++)
	{
		if (NULL != month_p->day_records[i])
		{
			j++;
			CString num,money,direct,day;
			num.Format("%d",j);
			money.Format("%.1lf",month_p->day_records[i]->get_day_money_out_cash() + month_p->day_records[i]->get_day_money_out_card());
			direct = "ȫ��";
			day.Format("%d",i+1);
			row = table_list.InsertItem(j-1,"");
			table_list.SetItemText(row,1,num);
			table_list.SetItemText(row,2,money);
			table_list.SetItemText(row,3,direct);
			table_list.SetItemText(row,4,day);			
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void TableMonthOut::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		TableDayOut table_dlg;
		table_dlg.Date = Date;
		
	//cur_dayp->records->record_info = "sadf";
		CString str = GetItemText(hWnd1,nItem ,4);
		table_dlg.day_p = month_p->day_records[(int)atof(str)-1];
		table_dlg.Date.SetDate(Date.GetYear(),Date.GetMonth(),(int)atof(str));
		table_dlg.set_cards(cards);
		table_dlg.DoModal();
	}
	*pResult = 0;
}

void TableMonthOut::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		combox.AddString("ȫ��");
		combox.AddString("�ֽ�");
		combox.AddString("���п�(��)");
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

void TableMonthOut::OnCbnSelchangeCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	if ("�ֽ�" == str)
	{
		money.Format("%.1lf",month_p->day_records[day-1]->get_day_money_out_cash());
	}
	else if ("���п�(��)" == str)
	{
		money.Format("%.1lf",month_p->day_records[day-1]->get_day_money_out_card());
	}
	else if ("ȫ��" == str)
	{
		money.Format("%.1lf",month_p->day_records[day-1]->get_day_money_out_cash() + month_p->day_records[day-1]->get_day_money_out_card());
	}
	else
	{
		money.Format("%.1lf",month_p->day_records[day-1]->get_day_money_out_cards(FindCard(str)));
	}
	SetCell(::GetDlgItem (m_hWnd,TABLE_LIST),money,nItem,2);
}


void TableMonthOut::OnCbnKillfocusCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::ShowWindow(::GetDlgItem(m_hWnd,COMBOX),SW_HIDE);
}