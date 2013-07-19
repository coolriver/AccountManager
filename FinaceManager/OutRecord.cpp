// OutRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "OutRecord.h"
#include "afxdialogex.h"


// OutRecord �Ի���

IMPLEMENT_DYNAMIC(OutRecord, CDialog)

OutRecord::OutRecord(CWnd* pParent /*=NULL*/)
	: CDialog(OutRecord::IDD, pParent)
{

}

OutRecord::~OutRecord()
{
}

void OutRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, OUT_TYPE_COMBOX, out_type_combox);
	DDX_Control(pDX, OUT_CARD_COMBOX, out_card_combox);
}


BEGIN_MESSAGE_MAP(OutRecord, CDialog)
	ON_CBN_SELCHANGE(OUT_TYPE_COMBOX, &OutRecord::OnCbnSelchangeTypeCombox)
	ON_BN_CLICKED(OUT_BACK, &OutRecord::OnBnClickedBack)
	ON_BN_CLICKED(OUT_SUBMIT, &OutRecord::OnBnClickedSubmit)
END_MESSAGE_MAP()


// OutRecord ��Ϣ�������
void OutRecord::set_cards(CString * card)
{
	for (int i = 0;i < MAXCARD;i++)
	{
		this->cards[i] = card[i];
		//MessageBox(card[i]);
	}
}

void OutRecord::OnCbnSelchangeTypeCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString type;
	GetDlgItemText(OUT_TYPE_COMBOX,type);
	if ( type == "�ֽ�")
	{
		 ::ShowWindow(::GetDlgItem(m_hWnd,OUT_CARD_COMBOX),SW_HIDE);
	}
	else
	{
		::ShowWindow(::GetDlgItem(m_hWnd,OUT_CARD_COMBOX),SW_SHOW);
	}
}


void OutRecord::OnBnClickedBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	EndDialog(0);
}


void OutRecord::OnBnClickedSubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Records record = NULL;
	record = (Records)malloc(sizeof(Record));
	CString card_num,info,money_num,direct;

	record->type = outcome;
	record->record_info = NULL;
	GetDlgItemText(OUT_TYPE_COMBOX,direct);
	GetDlgItemText(OUT_CARD_COMBOX,card_num);
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

	GetDlgItemText(OUT_MONEY_NUM,money_num);
	if (FALSE == IsFloat(money_num,OUT_MONEY_NUM))
	{
		MessageBox("����Ľ���ʽ����,���顣","����");
		free(record);
		return;
	}

	record->money_num = atof(money_num);
	if ("" == money_num)
	{
		MessageBox("����Ľ���Ϊ 0 ��","����");
		free(record);
		return;		
	}
	record->record_info = new CString();
	GetDlgItemText(OUT_INFO,(*record->record_info));
	//memset(record->record_info,0,256);
//	record->record_info = info.GetBuffer(info.GetLength());
	//memcpy(record->record_info,info.GetBuffer(),info.GetLength());
//	info.ReleaseBuffer();
	//record->record_info = info;
	record->next = NULL;

	HWND hwnd = ::GetParent(m_hWnd);
	::SendMessage(hwnd,WM_MyMessage1,0,(LPARAM)record);
	//MessageBoxA("��Ӽ�¼�ɹ���","��ʾ");
	EndDialog(0);
}


BOOL OutRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	out_type_combox.AddString("���п�");
	out_type_combox.AddString("�ֽ�");
	out_type_combox.SelectString(0,"�ֽ�");

	int n = 0;
	for (int i = 0;i < MAXCARD;i++)
	{
		if (cards[i] != "")
		{
			n = i;
			out_card_combox.AddString(cards[i]);
		}
	}
	out_card_combox.SelectString(0,cards[n]);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL OutRecord::IsFloat(CString &str, int ID)
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