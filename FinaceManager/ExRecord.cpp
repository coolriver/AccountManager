// ExRecord.cpp : 实现文件
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "ExRecord.h"
#include "afxdialogex.h"


// ExRecord 对话框

IMPLEMENT_DYNAMIC(ExRecord, CDialog)

ExRecord::ExRecord(CWnd* pParent /*=NULL*/)
	: CDialog(ExRecord::IDD, pParent)
{

}

ExRecord::~ExRecord()
{
}

void ExRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EX_COMBOX_FROM, combox_from);
	DDX_Control(pDX, EX_COMBOX_TO, combox_to);
}


BEGIN_MESSAGE_MAP(ExRecord, CDialog)
	ON_CBN_SELCHANGE(EX_COMBOX_FROM, &ExRecord::OnCbnSelchangeComboxFrom)
	ON_CBN_SELCHANGE(EX_COMBOX_TO, &ExRecord::OnCbnSelchangeComboxTo)
	ON_BN_CLICKED(EX_BACK, &ExRecord::OnBnClickedBack)
	ON_BN_CLICKED(EX_SUBMIT, &ExRecord::OnBnClickedSubmit)
END_MESSAGE_MAP()


// ExRecord 消息处理程序
void ExRecord::set_cards(CString * card)
{
	for (int i = 0;i < MAXCARD;i++)
	{
		this->cards[i] = card[i];
		//MessageBox(card[i]);
	}
}

BOOL ExRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	combox_from.AddString("现金");

	int n = 0;
	for (int i = 0;i < MAXCARD;i++)
	{
		if (cards[i] != "")
		{
			n = i;
			combox_from.AddString(cards[i]);
			combox_to.AddString(cards[i]);
		}
	}
	combox_from.DeleteString(combox_from.FindString(0,cards[n]));
	combox_from.SelectString(0,"现金");
	combox_to.SelectString(0,cards[n]);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ExRecord::OnCbnSelchangeComboxFrom()
{
	// TODO: 在此添加控件通知处理程序代码
	CString from,to;
	GetDlgItemText(EX_COMBOX_FROM,from);
	GetDlgItemText(EX_COMBOX_TO,to);
	combox_to.ResetContent();
	if (from == "现金")
	{
		int n = 0;
		for (int i = 0;i < MAXCARD;i++)
		{
			if (cards[i] != "")
			{
				n = i;
				combox_to.AddString(cards[i]);
			}

		}
		if (to == "现金")
		{
			combox_to.SelectString(0,cards[n]);
		}
		else
		{
			combox_to.SelectString(0,to);
		}
	}
	else
	{
		combox_to.AddString("现金");
		int n = 0;
		for (int i = 0;i < MAXCARD;i++)
		{
			if (cards[i] != "")
			{
				n = i;
				combox_to.AddString(cards[i]);
			}

		}
		combox_to.DeleteString(combox_to.FindString(0,from));
		if (from == to)
		{
			combox_to.SelectString(0,"现金");
		}
		else
		{
			combox_to.SelectString(0,to);
		}
	}
}


void ExRecord::OnCbnSelchangeComboxTo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString to,from;
	GetDlgItemText(EX_COMBOX_TO,to);
	GetDlgItemText(EX_COMBOX_FROM,from);
	combox_from.ResetContent();
	if (to == "现金")
	{
		int n = 0;
		for (int i = 0;i < MAXCARD;i++)
		{
			if (cards[i] != "")
			{
				n = i;
				combox_from.AddString(cards[i]);
			}

		}
		if (from == "现金")
		{
			combox_from.SelectString(0,cards[n]);
		}
		else
		{
			combox_from.SelectString(0,from);
		}
	}
	else
	{
		combox_from.AddString("现金");
		int n = 0;
		for (int i = 0;i < MAXCARD;i++)
		{
			if (cards[i] != "")
			{
				n = i;
				combox_from.AddString(cards[i]);
			}

		}
		combox_from.DeleteString(combox_from.FindString(0,to));
		if (from == to)
		{
			combox_from.SelectString(0,"现金");
		}
		else
		{
			combox_from.SelectString(0,from);
		}
	}
}

BOOL ExRecord::IsFloat(CString &str, int ID)
{
 int dotFlag=0;
//是否为浮点数
 for(int i = 0; i < str.GetLength(); i++) 
 { 
  if(str[i] == '.')
   dotFlag++;
  if ((dotFlag>1 )//小数点多于一个
   ||
   !((str[i] == '.')|| (str[i] >= '0' && str[i] <= '9'))//所输入的数不是.0-9
   )
  { 
   //MessageBox("不是数字","错误");
   ((CEdit*)GetDlgItem(ID))->SetSel(0,1000,true) ; 
   return false;
  } 
 } 
//只能输入两位小数

 return true;
}

void ExRecord::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

int ExRecord::FindCard(CString str)
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

void ExRecord::OnBnClickedSubmit()
{
	// TODO: 在此添加控件通知处理程序代码
	Records record = NULL;
	record = (Records)malloc(sizeof(Record));
	record->record_info = NULL;
	CString info,money_num,from,to;
	int from_n,to_n;

	record->type = exchange;
	GetDlgItemText(EX_COMBOX_FROM,from);
	GetDlgItemText(EX_COMBOX_TO,to);
	from_n = FindCard(from);
	to_n = FindCard(to);
	GetDlgItemText(EX_MONEY_NUM,money_num);
	if (FALSE == IsFloat(money_num,IN_MONEY_NUM))
	{
		MessageBox("输入的金额格式有误,请检查","错误");
		free(record);
		return;
	}

	if ("" == money_num)
	{
		MessageBox("输入的金额不可为 0 ","错误");
		free(record);
		return;		
	}
	record->money_num = atof(money_num);
	record->record_info = new CString();
	record->record_info->Format("#%s#%s#%d#%d",from,to,from_n,to_n);
	record->next = NULL;
	HWND hwnd = ::GetParent(m_hWnd);
	::SendMessage(hwnd,WM_MyMessage1,0,(LPARAM)record);
	EndDialog(0);
}



