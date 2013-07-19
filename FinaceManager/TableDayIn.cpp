#include "StdAfx.h"
#include "TableDayIn.h"


TableDayIn::TableDayIn(void)
{
	day_p = NULL;
}


TableDayIn::~TableDayIn(void)
{
}



BOOL TableDayIn::OnInitDialog()
{
	TableFather::OnInitDialog();
	CString title = "";
	title.Format("%d年%d月%d日收入记录",Date.GetYear(),Date.GetMonth(),Date.GetDay());
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
	table_list.InsertColumn(4,"收入说明",LVCFMT_CENTER);
	table_list.SetColumnWidth(1,40);
	table_list.SetColumnWidth(2,80);
	table_list.SetColumnWidth(3,100);
	table_list.SetColumnWidth(4,310);

	if (NULL == day_p)
	{
		return TRUE;
	}
	Records rp = day_p->records;
	int row,i;
	for (i = 0;NULL != rp;rp = rp->next)
	{
		if (income == rp->type)
		{
			i++;
			CString num,money,direct,info;
			
			money.Format("%.1lf",rp->money_num);
			if (cash == rp->direct)
			{
				direct = "现金";
			}
			else
			{
				direct = cards[rp->card_num];
			}
			info = (*(rp->record_info));
		    row = table_list.InsertItem(i-1,"");
			num.Format("%d",i);
			table_list.SetItemText(row,1,num);
			table_list.SetItemText(row,2,money);
			table_list.SetItemText(row,3,direct);
			table_list.SetItemText(row,4,info);
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
