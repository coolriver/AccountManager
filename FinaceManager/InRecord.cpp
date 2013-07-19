// InRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "InRecord.h"
#include "afxdialogex.h"


// InRecord �Ի���

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


// InRecord ��Ϣ�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	if (direct == "�ֽ�")
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
		MessageBox("����Ľ���ʽ����,����","����");
		free(record);
		return;
	}

	if ("" == money_num)
	{
		MessageBox("����Ľ���Ϊ 0 ","����");
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

	in_type_combox.AddString("���п�");
	in_type_combox.AddString("�ֽ�");
	in_type_combox.SelectString(0,"�ֽ�");

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void InRecord::OnCbnSelchangeTypeCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString type;
	GetDlgItemText(IN_TYPE_COMBOX,type);
	if ( type == "�ֽ�")
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}

BOOL InRecord::IsFloat(CString &str, int ID)
{
 int dotFlag=0;
//�Ƿ�Ϊ������
 for(int i = 0; i < str.GetLength(); i++) 
 { 
  if(str[i] == '.')
   dotFlag++;
  if ((dotFlag>1 )//С�������һ��
   ||
   !((str[i] == '.')|| (str[i] >= '0' && str[i] <= '9'))//�������������.0-9
   )
  { 
   //MessageBox("��������","����");
   ((CEdit*)GetDlgItem(ID))->SetSel(0,1000,true) ; 
   return false;
  } 
 } 
//ֻ��������λС��

 return true;
}
