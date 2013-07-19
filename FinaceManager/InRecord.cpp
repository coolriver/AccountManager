// InRecord.cpp : 实现文件
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "InRecord.h"
#include "afxdialogex.h"


// InRecord 对话框

IMPLEMENT_DYNAMIC(InRecord, CDialog)

InRecord::InRecord(CWnd* pParent /*=NULL*/)
	: CDialog(InRecord::IDD, pParent)
{

}

InRecord::~InRecord()
{
}

void InRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IN_TYPE_COMBOX, in_type_combox);
	DDX_Control(pDX, IN_CARD_COMBOX, in_card_combox);
}


BEGIN_MESSAGE_MAP(InRecord, CDialog)
	ON_BN_CLICKED(IN_SUBMIT, &InRecord::OnBnClickedSubmit)
	ON_CBN_SELCHANGE(IN_TYPE_COMBOX, &InRecord::OnCbnSelchangeTypeCombox)
	ON_BN_CLICKED(IN_BACK, &InRecord::OnBnClickedBack)
END_MESSAGE_MAP()


// InRecord 消息处理程序
void InRecord::set_cards(CString * card)
{
	for (int i = 0;i < MAXCARD;i++)
	{
		this->cards[i] = card[i];
		//MessageBox(card[i]);
	}
}

void InRecord::OnBnClickedSubmit()
{
	// TODO: 在此添加控件通知处理程序代码
	Records record = NULL;
	record = (Records)malloc(sizeof(Record));
	record->record_info = NULL;
	CString card_num,info,money_num,direct;

	record->type = income;

	GetDlgItemText(IN_TYPE_COMBOX,direct);
	GetDlgItemText(IN_CARD_COMBOX,card_num);
	for (int i = 0;i < MAXCARD;i++)
	{
		if (cards[i] == card_num)
		{
			record->card_num = i;
		}
	}

	if (direct == "现金")
	{
		record->direct = cash;
	}
	else
	{
		record->direct = card;
	}

	GetDlgItemText(IN_MONEY_NUM,money_num);
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
	GetDlgItemText(IN_INFO,(*record->record_info));
	//memset(record->record_info,0,256);
	//record->record_info = info.GetBuffer(info.GetLength());
	//memcpy(record->record_info,info.GetBuffer(),info.GetLength());
	//info.ReleaseBuffer();
	//record->record_info = info;
	//record->record_info = (char *)malloc((info.GetLength()+1)*sizeof(char));
	//memcpy(record->record_info,info.GetBuffer(),info.GetLength());
	//info.ReleaseBuffer();
	//record->record_info =  (LPSTR)(LPCTSTR)info;
	//record->record_info[info.GetLength()] = '\0';
	record->next = NULL;

	HWND hwnd = ::GetParent(m_hWnd);
	::SendMessage(hwnd,WM_MyMessage1,0,(LPARAM)record);
	EndDialog(0);
}


BOOL InRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	in_type_combox.AddString("银行卡");
	in_type_combox.AddString("现金");
	in_type_combox.SelectString(0,"现金");

	int n = 0;
	for (int i = 0;i < MAXCARD;i++)
	{
		if (cards[i] != "")
		{
			n = i;
			in_card_combox.AddString(cards[i]);
		}
	}
	in_card_combox.SelectString(0,cards[n]);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void InRecord::OnCbnSelchangeTypeCombox()
{
	// TODO: 在此添加控件通知处理程序代码
	CString type;
	GetDlgItemText(IN_TYPE_COMBOX,type);
	if ( type == "现金")
	{
		 ::ShowWindow(::GetDlgItem(m_hWnd,IN_CARD_COMBOX),SW_HIDE);
	}
	else
	{
		::ShowWindow(::GetDlgItem(m_hWnd,IN_CARD_COMBOX),SW_SHOW);
	}
}


void InRecord::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

BOOL InRecord::IsFloat(CString &str, int ID)
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
