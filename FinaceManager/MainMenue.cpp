// MainMenue.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinaceManager.h"
#include "MainMenue.h"
#include "afxdialogex.h"


// MainMenue �Ի���

IMPLEMENT_DYNAMIC(MainMenue, CDialog)

MainMenue::MainMenue(CWnd* pParent /*=NULL*/)
	: CDialog(MainMenue::IDD, pParent)
{
	//state_day = FALSE;
	//state_month = FALSE;
	//state_year = FALSE;
	not_save = FALSE;
	years = NULL;
	cur_yearp = NULL;
	cur_monthp = NULL;
	cur_dayp = NULL;
	for (int i = 0;i < MAXCARD;i++)
	{
		cards[i] = "";
	}
	
}

MainMenue::~MainMenue()
{
	Years p = NULL;
	Years q = NULL;
	while(years != NULL)
	{
		p = years->next;
		YearRecord * yp = years->year_record;

		delete yp;
		years->year_record = NULL;

		free(years);
		
		years = p;
	}



}

void MainMenue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, DAY_START_COMBOX, day_start_combox);
	DDX_Control(pDX, DAY_END_COMBOX, day_end_combox);
	DDX_Control(pDX, DAY_OUT_COMBOX, day_out_combox);
	DDX_Control(pDX, DAY_IN_COMBOX, day_in_combox);
	DDX_Control(pDX, MONTH_START_COMBOX, month_start_combox);
	DDX_Control(pDX, MONTH_END_COMBOX, month_end_combox);
	DDX_Control(pDX, MONTH_OUT_COMBOX, month_out_combox);
	DDX_Control(pDX, MONTH_IN_COMBOX, month_in_combox);
	DDX_Control(pDX, YEAR_START_COMBOX, year_start_combox);
	DDX_Control(pDX, YEAR_END_COMBOX, year_end_combox);
	DDX_Control(pDX, YEAR_OUT_COMBOX, year_out_combox);
	DDX_Control(pDX, YEAR_IN_COMBOX, year_in_combox);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, date_ctrl);
}


BEGIN_MESSAGE_MAP(MainMenue, CDialog)
	ON_MESSAGE(WM_MyMessage1, OnMyMessage1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &MainMenue::OnDtnDatetimechangeDatetimepicker2)
	ON_BN_CLICKED(BUTTON_ADD, &MainMenue::OnBnClickedAdd)
	ON_CBN_SELCHANGE(DAY_START_COMBOX, &MainMenue::OnCbnSelchangeStartCombox)
	ON_CBN_SELCHANGE(DAY_END_COMBOX, &MainMenue::OnCbnSelchangeEndCombox)
	ON_CBN_SELCHANGE(DAY_OUT_COMBOX, &MainMenue::OnCbnSelchangeOutCombox)
	ON_CBN_SELCHANGE(DAY_IN_COMBOX, &MainMenue::OnCbnSelchangeInCombox)
	ON_CBN_SELCHANGE(MONTH_START_COMBOX, &MainMenue::OnCbnSelchangeStartComboxm)
	ON_CBN_SELCHANGE(MONTH_END_COMBOX, &MainMenue::OnCbnSelchangeEndComboxm)
	ON_CBN_SELCHANGE(MONTH_OUT_COMBOX, &MainMenue::OnCbnSelchangeOutComboxm)
	ON_CBN_SELCHANGE(MONTH_IN_COMBOX, &MainMenue::OnCbnSelchangeInComboxm)
	ON_CBN_SELCHANGE(YEAR_START_COMBOX, &MainMenue::OnCbnSelchangeStartComboxy)
	ON_CBN_SELCHANGE(YEAR_END_COMBOX, &MainMenue::OnCbnSelchangeEndComboxy)
	ON_CBN_SELCHANGE(YEAR_OUT_COMBOX, &MainMenue::OnCbnSelchangeOutComboxy)
	ON_CBN_SELCHANGE(YEAR_IN_COMBOX, &MainMenue::OnCbnSelchangeInComboxy)
	ON_BN_CLICKED(BUTTON_DE, &MainMenue::OnBnClickedDe)
	ON_BN_CLICKED(BUTTON_SAVE, &MainMenue::OnBnClickedSave)
	ON_BN_CLICKED(DAY_IN, &MainMenue::OnBnClickedIn)
	ON_BN_CLICKED(DAY_OUT, &MainMenue::OnBnClickedOut)
	ON_BN_CLICKED(MONTH_IN, &MainMenue::OnBnClickedInm)
	ON_BN_CLICKED(MONTH_OUT, &MainMenue::OnBnClickedOutm)
	ON_BN_CLICKED(YEAR_IN, &MainMenue::OnBnClickedIny)
	ON_BN_CLICKED(YEAR_OUT, &MainMenue::OnBnClickedOuty)
	ON_BN_CLICKED(BUTTON_EX, &MainMenue::OnBnClickedEx)
END_MESSAGE_MAP()


// MainMenue ��Ϣ�������


BOOL MainMenue::OnInitDialog()
{
	CDialog::OnInitDialog();



	//char path[256];
	//char cur_temp[500];
	CString key,StrTmp;
	char m_data[256];

	char szBuf[MAX_PATH];
    CString strPath("");
    ::GetModuleFileName(NULL, szBuf, MAX_PATH);
    strPath = (LPCSTR)szBuf;
    strPath = strPath.Left(strPath.ReverseFind('\\'));
    strPath += "\\card.ini";

	for (int i = 0;i < MAXCARD;i++)
	{
		memset(m_data,0,256);
		key.Format("%d",i);
		if (0 != GetPrivateProfileString("cardlist", key, "", m_data, 256, strPath))
		{
			StrTmp.Format("%s",m_data);
			cards[i] = StrTmp;
		}
	}
	day_start_combox.AddString("�ܿ����");
	day_end_combox.AddString("�ܿ����");
	day_out_combox.AddString("�ܿ����");
	day_in_combox.AddString("�ܿ����");
	month_start_combox.AddString("�ܿ����");
	month_end_combox.AddString("�ܿ����");
	month_out_combox.AddString("�ܿ����");
	month_in_combox.AddString("�ܿ����");
	year_start_combox.AddString("�ܿ����");
	year_end_combox.AddString("�ܿ����");
	year_out_combox.AddString("�ܿ����");
	year_in_combox.AddString("�ܿ����");

	for (int i = 0;i < MAXCARD;i++)
	{
		if ("" != cards[i])
		{
			day_start_combox.AddString(cards[i]);
			day_end_combox.AddString(cards[i]);
			day_out_combox.AddString(cards[i]);
			day_in_combox.AddString(cards[i]);
			month_start_combox.AddString(cards[i]);
			month_end_combox.AddString(cards[i]);
			month_out_combox.AddString(cards[i]);
			month_in_combox.AddString(cards[i]);
			year_start_combox.AddString(cards[i]);
			year_end_combox.AddString(cards[i]);
			year_out_combox.AddString(cards[i]);
			year_in_combox.AddString(cards[i]);
		}
	}

	day_start_combox.SelectString(0,"�ܿ����");
	day_end_combox.SelectString(0,"�ܿ����");
	day_out_combox.SelectString(0,"�ܿ����");
	day_in_combox.SelectString(0,"�ܿ����");
	month_start_combox.SelectString(0,"�ܿ����");
	month_end_combox.SelectString(0,"�ܿ����");
	month_out_combox.SelectString(0,"�ܿ����");
	month_in_combox.SelectString(0,"�ܿ����");
	year_start_combox.SelectString(0,"�ܿ����");
	year_end_combox.SelectString(0,"�ܿ����");
	year_out_combox.SelectString(0,"�ܿ����");
	year_in_combox.SelectString(0,"�ܿ����");

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//inrecord = new InRecord();
	//inrecord->set_cards(cards);
	//inrecord->Create(ADD_IN_RECORD,this);
	LoadData();
	date_ctrl.GetTime(Date);
	FlushMenue();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MainMenue::OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	date_ctrl.GetTime(Date);
	FlushMenue();
	*pResult = 0;
}

BOOL  MainMenue::CheckDate()
{
	int year = Date.GetYear();
	int month = Date.GetMonth();
	int day = Date.GetDay();

	COleDateTime  DateNow = COleDateTime::GetCurrentTime(); 
	if (DateNow < Date)
	{
		MessageBox("��������δ��������������Ŀ��","����");
		return FALSE;
	}
	//CString str;
	//str.Format("%.1lf year %.1lf month %.1lf day",year,month,day);
	//MessageBox(str);
	Years yearp = years;
	if (NULL == yearp)
	{
		return TRUE;
	}
	if (yearp->year_record->year > year)
	{
		MessageBox("���������������Ŀ������֮ǰ������Ŀ��","����");
		return FALSE;		
	}
	else if (yearp->year_record->year < year)
	{
		return TRUE;
	}
	int n = 11;
	for (;n >= 0;n--)
	{
		if (NULL != yearp->year_record->month_records[n])
		{
			break;
		}
	}
	if (n + 1 > month)
	{
		MessageBox("���������������Ŀ������֮ǰ������Ŀ��","����");
		return FALSE;		
	}
	if (n + 1 < month)
	{
		return TRUE;
	}
	int m = 30;
	for (;m >= 0;m--)
	{
		if (NULL != yearp->year_record->month_records[n]->day_records[m])
		{
			break;
		}	
	}
	if (m + 1 > day)
	{
		MessageBox("���������������Ŀ������֮ǰ������Ŀ��","����");
		return FALSE;		
	}
	return TRUE;
	
}

void MainMenue::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	
//	inrecord->ShowWindow(SW_SHOW);
	if (FALSE == CheckDate())
	{
		return;
	}

	InRecord indlg;
	indlg.set_cards(cards);
	indlg.DoModal();

/*	Records record = (Records)malloc(sizeof(Record));
	record->card_num = 0;
	record->direct = cash;
	record->money_num = 2000;
	record->next = NULL;
	record->type = income;
	record->record_info = "sadfasdf";
	::SendMessage(m_hWnd,WM_MyMessage1,0,(LPARAM)record);*/
}


LRESULT MainMenue::OnMyMessage1(WPARAM wParam, LPARAM lParam)
{
	
	//MessageBox("alallalaal");
	Records record = (Records)lParam;
	
	//MessageBox(records->record_info);
	insert_record(record);

	//free(record);
	FlushMenue();
	return 0;
}

void MainMenue::insert_record(Records record)
{
	//MessageBox(record->record_info);
	int year = Date.GetYear();
	int month = Date.GetMonth();
	int day = Date.GetDay();
	//CString str;
	//str.Format("%.1lf year %.1lf month %.1lf day",year,month,day);
	//MessageBox(str);
	cur_yearp = search_year(year);
	cur_monthp = search_month(month,cur_yearp);
	cur_dayp = search_day(day,cur_monthp);
	cur_dayp->AddRecord(record);
	cur_dayp->calculate(record);
	cur_monthp->calculate(record);
	cur_yearp->year_record->calculate(record);
	not_save = TRUE;
	MessageBoxA("��Ӽ�¼�ɹ���","��ʾ");
	/*
	in_dayp->AddRecord(record);
	in_dayp->calculate(record);
	in_monthp->calculate(record);
	in_yearp->year_record->calculate(record);
	
	MessageBoxA("��Ӽ�¼�ɹ���","��ʾ");*/
/*	if (NULL == yearp)
	{
		MessageBox("���������������Ŀ������֮ǰ������Ŀ��");
		free(record);
		return;
	}
	else
	{
		MonthRecord * monthp = search_month(month,yearp);
		if (NULL == monthp)
		{
			MessageBox("���������������Ŀ������֮ǰ������Ŀ��");
			free(record);
			return;
		}
		else
		{
			DayRecord * dayp = search_day(day,monthp);
			if (NULL == dayp)
			{
				MessageBox("���������������Ŀ������֮ǰ������Ŀ��");
				free(record);
				return;
			}
			else
			{
				dayp->AddRecord(record);
				dayp->calculate(record);
				monthp->calculate(record);
				yearp->year_record->calculate(record);
				MessageBoxA("��Ӽ�¼�ɹ���","��ʾ");
			}
		}
	}*/
}

Years MainMenue::search_year(int year)
{
	Years p = years;
	if (NULL == p)
	{
		p = (Years)malloc(sizeof(yyear));
		p->year_record = new YearRecord();
		p->year_record->year = year;
		p->next = years;
		years = p;
		return p;
	}
	else
	{
		if (year == p->year_record->year)
		{
			return p;
		}

		if (year < p->year_record->year)
		{
			return NULL;
		}

		if (year > p->year_record->year)
		{
			Years q;
			q = (Years)malloc(sizeof(yyear));
			q->year_record = new YearRecord();
			q->year_record->year = year;
			q->year_record->set_year_money_start_cash(years->year_record->get_year_money_end_cash());
			q->year_record->set_year_money_end_cash(years->year_record->get_year_money_end_cash());
			q->year_record->set_year_money_start_card(years->year_record->get_year_money_end_card());
			q->year_record->set_year_money_end_card(years->year_record->get_year_money_end_card());
			for (int i = 0;i < MAXCARD;i++)
			{
				q->year_record->set_year_money_start_cards(years->year_record->get_year_money_end_cards(i),i);
				q->year_record->set_year_money_end_cards(years->year_record->get_year_money_end_cards(i),i);
			}
			q->next = years;
			years = q;
			p = NULL;
			return q;
		}
	}
}

MonthRecord *  MainMenue::search_month(int month,Years year)
{
	int n = 11;
	for (;n >= 0;n--)
	{
		if (NULL != year->year_record->month_records[n])
		{
			break;
		}
	}
	if (n < 0)
	{
		MonthRecord * monthp = new MonthRecord();
		monthp->month = month;
		monthp->set_month_money_start_cash(year->year_record->get_year_money_end_cash());
		monthp->set_month_money_end_cash(year->year_record->get_year_money_end_cash());
		monthp->set_month_money_start_card(year->year_record->get_year_money_end_card());
		monthp->set_month_money_end_card(year->year_record->get_year_money_end_card());
		for (int i = 0;i < MAXCARD;i++)
		{
			monthp->set_month_money_start_cards(year->year_record->get_year_money_end_cards(i),i);
			monthp->set_month_money_end_cards(year->year_record->get_year_money_end_cards(i),i);
		}
		year->year_record->month_records[month - 1] = monthp;
		return monthp;
	}
	else if (n + 1 == month)
	{
		return year->year_record->month_records[n];
	}
	else if (n + 1 > month)
	{
		return NULL;
	}
	else if (n + 1 < month)
	{
		MonthRecord * monthp = new MonthRecord();
		monthp->month = month;
		monthp->set_month_money_start_card(year->year_record->month_records[n]->get_month_money_end_card());
		monthp->set_month_money_end_card(year->year_record->month_records[n]->get_month_money_end_card());
		monthp->set_month_money_start_cash(year->year_record->month_records[n]->get_month_money_end_cash());
		monthp->set_month_money_end_cash(year->year_record->month_records[n]->get_month_money_end_cash());
		for (int i = 0;i <MAXCARD;i++)
		{
			monthp->set_month_money_start_cards(year->year_record->month_records[n]->get_month_money_end_cards(i),i);
			monthp->set_month_money_end_cards(year->year_record->month_records[n]->get_month_money_end_cards(i),i);
		}
		
		year->year_record->month_records[month - 1] = monthp;
		return monthp;
	}
}

DayRecord * MainMenue::search_day(int day,MonthRecord * month)
{
	int n = 30;
	for (;n >= 0;n--)
	{
		if (NULL != month->day_records[n])
		{
			break;
		}
	}
	if (n < 0)
	{
		DayRecord * dayp = new DayRecord();
		dayp->day = day;
		dayp->set_day_money_start_card(month->get_month_money_end_card());
		dayp->set_day_money_end_card(month->get_month_money_end_card());
		dayp->set_day_money_start_cash(month->get_month_money_end_cash());
		dayp->set_day_money_end_cash(month->get_month_money_end_cash());
		for (int i = 0;i < MAXCARD;i++)
		{
			dayp->set_day_money_start_cards(month->get_month_money_end_cards(i),i);
			dayp->set_day_money_end_cards(month->get_month_money_end_cards(i),i);
		}
		month->day_records[day-1] = dayp;
		return dayp;
	}
	else if (n+1 == day)
	{
		return month->day_records[n];
	}
	else if (n+1 > day)
	{
		return NULL;
	}
	else if (n+1 < day)
	{
		DayRecord * dayp = new DayRecord();
		dayp->day = day;
		dayp->set_day_money_start_card(month->day_records[n]->get_day_money_end_card());
		dayp->set_day_money_end_card(month->day_records[n]->get_day_money_end_card());
		dayp->set_day_money_start_cash(month->day_records[n]->get_day_money_end_cash());
		dayp->set_day_money_end_cash(month->day_records[n]->get_day_money_end_cash());
		for (int i = 0;i < MAXCARD;i++)
		{
			dayp->set_day_money_start_cards(month->day_records[n]->get_day_money_end_cards(i),i);
			dayp->set_day_money_end_cards(month->day_records[n]->get_day_money_end_cards(i),i);
		}
		month->day_records[day - 1] = dayp;
		return dayp;
	}
}

void MainMenue::CheckState()
{
	int year = Date.GetYear();
	int month = Date.GetMonth();
	int day = Date.GetDay();

	Years yearp = years;
	while(yearp != NULL)
	{
		if (yearp->year_record != NULL && yearp->year_record->year == year)
		{
			break;
		}
		yearp = yearp->next;
	}
	if (NULL == yearp)
	{
		cur_yearp = NULL;
		cur_monthp = NULL;
		cur_dayp = NULL;
		return;
	}
	cur_yearp = yearp;
	int i;
	for (i = 0;i < 12;i++)
	{
		if (NULL != yearp->year_record->month_records[i])
		{
			if (yearp->year_record->month_records[i]->month == month)
			{
				break;
			}
		}
	}
	if (12 == i)
	{
		cur_dayp = NULL;
		cur_monthp = NULL;
		return;
	}
	cur_monthp = yearp->year_record->month_records[i];
	int j;
	for (j = 0;j < 31;j++)
	{
		if (cur_monthp->day_records[j] != NULL && cur_monthp->day_records[j]->day == day)
		{
			break;
		}
	}
	if (31 == j)
	{
		cur_dayp = NULL;
		return;
	}
	cur_dayp = yearp->year_record->month_records[i]->day_records[j];
}

int MainMenue::FindCard(CString str)
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

void MainMenue::FlushMenue()
{
	CheckState();

	if (NULL == cur_yearp)
	{
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT2),"�޼�¼");

		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT2),"�޼�¼");

		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_START_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_START_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_END_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_END_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_OUT_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_OUT_EDIT2),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_IN_EDIT1),"�޼�¼");
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_IN_EDIT2),"�޼�¼");
	}
	else
	{
		CString year_combox;
		CString year_str1,year_str2,year_str3,year_str4,year_str5,year_str6,year_str7,year_str8;

		GetDlgItemText(YEAR_START_COMBOX,year_combox);
		if ("�ܿ����" == year_combox)
		{
			year_str1.Format("%.1lf",cur_yearp->year_record->get_year_money_start_card());
		}
		else
		{
			year_str1.Format("%.1lf",cur_yearp->year_record->get_year_money_start_cards(FindCard(year_combox)));
		}
		year_str2.Format("%.1lf",cur_yearp->year_record->get_year_money_start_cash());

		GetDlgItemText(YEAR_END_COMBOX,year_combox);
		if ("�ܿ����" == year_combox)
		{
			year_str3.Format("%.1lf",cur_yearp->year_record->get_year_money_end_card());
		}
		else
		{
			year_str3.Format("%.1lf",cur_yearp->year_record->get_year_money_end_cards(FindCard(year_combox)));
		}
		year_str4.Format("%.1lf",cur_yearp->year_record->get_year_money_end_cash());

		GetDlgItemText(YEAR_OUT_COMBOX,year_combox);
		if ("�ܿ����" == year_combox)
		{
			year_str5.Format("%.1lf",cur_yearp->year_record->get_year_money_out_card());
		}
		else
		{
			year_str5.Format("%.1lf",cur_yearp->year_record->get_year_money_out_cards(FindCard(year_combox)));
		}
		year_str6.Format("%.1lf",cur_yearp->year_record->get_year_money_out_cash());

		GetDlgItemText(YEAR_IN_COMBOX,year_combox);
		if ("�ܿ����" == year_combox)
		{
			year_str7.Format("%.1lf",cur_yearp->year_record->get_year_money_in_card());
		}
		else
		{
			year_str7.Format("%.1lf",cur_yearp->year_record->get_year_money_in_cards(FindCard(year_combox)));
		}
		year_str8.Format("%.1lf",cur_yearp->year_record->get_year_money_in_cash());

		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_START_EDIT1),year_str1);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_START_EDIT2),year_str2);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_END_EDIT1),year_str3);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_END_EDIT2),year_str4);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_OUT_EDIT1),year_str5);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_OUT_EDIT2),year_str6);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_IN_EDIT1),year_str7);
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_IN_EDIT2),year_str8);		


		if (NULL == cur_monthp)
		{
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT2),"�޼�¼");

			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT2),"�޼�¼");		
		}
		else
		{
		CString month_combox;
		CString month_str1,month_str2,month_str3,month_str4,month_str5,month_str6,month_str7,month_str8;

		GetDlgItemText(MONTH_START_COMBOX,month_combox);
		if ("�ܿ����" == month_combox)
		{
			month_str1.Format("%.1lf",cur_monthp->get_month_money_start_card());
		}
		else
		{
			month_str1.Format("%.1lf",cur_monthp->get_month_money_start_cards(FindCard(month_combox)));
		}
		month_str2.Format("%.1lf",cur_monthp->get_month_money_start_cash());

		GetDlgItemText(MONTH_END_COMBOX,month_combox);
		if ("�ܿ����" == month_combox)
		{
			month_str3.Format("%.1lf",cur_monthp->get_month_money_end_card());
		}
		else
		{
			month_str3.Format("%.1lf",cur_monthp->get_month_money_end_cards(FindCard(month_combox)));
		}
		month_str4.Format("%.1lf",cur_monthp->get_month_money_end_cash());

		GetDlgItemText(MONTH_OUT_COMBOX,month_combox);
		if ("�ܿ����" == month_combox)
		{
			month_str5.Format("%.1lf",cur_monthp->get_month_money_out_card());
		}
		else
		{
			month_str5.Format("%.1lf",cur_monthp->get_month_money_out_cards(FindCard(month_combox)));
		}
		month_str6.Format("%.1lf",cur_monthp->get_month_money_out_cash());

		GetDlgItemText(MONTH_IN_COMBOX,month_combox);
		if ("�ܿ����" == month_combox)
		{
			month_str7.Format("%.1lf",cur_monthp->get_month_money_in_card());
		}
		else
		{
			month_str7.Format("%.1lf",cur_monthp->get_month_money_in_cards(FindCard(month_combox)));
		}
		month_str8.Format("%.1lf",cur_monthp->get_month_money_in_cash());

		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT1),month_str1);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT2),month_str2);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT1),month_str3);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT2),month_str4);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT1),month_str5);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT2),month_str6);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT1),month_str7);
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT2),month_str8);				
		}

		if (NULL == cur_dayp)
		{
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT2),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT1),"�޼�¼");
			::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT2),"�޼�¼");
		}
		else
		{
		CString day_combox;
		CString day_str1,day_str2,day_str3,day_str4,day_str5,day_str6,day_str7,day_str8;

		GetDlgItemText(DAY_START_COMBOX,day_combox);
		if ("�ܿ����" == day_combox)
		{
			day_str1.Format("%.1lf",cur_dayp->get_day_money_start_card());
		}
		else
		{
			day_str1.Format("%.1lf",cur_dayp->get_day_money_start_cards(FindCard(day_combox)));
		}
		day_str2.Format("%.1lf",cur_dayp->get_day_money_start_cash());

		GetDlgItemText(DAY_END_COMBOX,day_combox);
		if ("�ܿ����" == day_combox)
		{
			day_str3.Format("%.1lf",cur_dayp->get_day_money_end_card());
		}
		else
		{
			day_str3.Format("%.1lf",cur_dayp->get_day_money_end_cards(FindCard(day_combox)));
		}
		day_str4.Format("%.1lf",cur_dayp->get_day_money_end_cash());

		GetDlgItemText(DAY_OUT_COMBOX,day_combox);
		if ("�ܿ����" == day_combox)
		{
			day_str5.Format("%.1lf",cur_dayp->get_day_money_out_card());
		}
		else
		{
			day_str5.Format("%.1lf",cur_dayp->get_day_money_out_cards(FindCard(day_combox)));
		}
		day_str6.Format("%.1lf",cur_dayp->get_day_money_out_cash());

		GetDlgItemText(DAY_IN_COMBOX,day_combox);
		if ("�ܿ����" == day_combox)
		{
			day_str7.Format("%.1lf",cur_dayp->get_day_money_in_card());
		}
		else
		{
			day_str7.Format("%.1lf",cur_dayp->get_day_money_in_cards(FindCard(day_combox)));
		}
		day_str8.Format("%.1lf",cur_dayp->get_day_money_in_cash());

		::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT1),day_str1);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT2),day_str2);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT1),day_str3);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT2),day_str4);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT1),day_str5);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT2),day_str6);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT1),day_str7);
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT2),day_str8);
		}
		
	}

}

void MainMenue::OnCbnSelchangeStartCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_dayp)
	{
		CString combox_str,data_str;
		GetDlgItemText(DAY_START_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_start_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_start_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_START_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeEndCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_dayp)
	{
		CString combox_str,data_str;
		GetDlgItemText(DAY_END_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_end_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_end_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_END_EDIT1),data_str);
	}
}

void MainMenue::OnCbnSelchangeOutCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_dayp)
	{
		CString combox_str,data_str;
		GetDlgItemText(DAY_OUT_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_out_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_out_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_OUT_EDIT1),data_str);
	}
}




void MainMenue::OnCbnSelchangeInCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_dayp)
	{
		CString combox_str,data_str;
		GetDlgItemText(DAY_IN_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_in_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_dayp->get_day_money_in_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,DAY_IN_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeStartComboxm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_monthp)
	{
		CString combox_str,data_str;
		GetDlgItemText(MONTH_START_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_start_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_start_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_START_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeEndComboxm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_monthp)
	{
		CString combox_str,data_str;
		GetDlgItemText(MONTH_END_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_end_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_end_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_END_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeOutComboxm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_monthp)
	{
		CString combox_str,data_str;
		GetDlgItemText(MONTH_OUT_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_out_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_out_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_OUT_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeInComboxm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_monthp)
	{
		CString combox_str,data_str;
		GetDlgItemText(MONTH_IN_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_in_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_monthp->get_month_money_in_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,MONTH_IN_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeStartComboxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_yearp)
	{
		CString combox_str,data_str;
		GetDlgItemText(YEAR_START_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_start_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_start_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_START_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeEndComboxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_yearp)
	{
		CString combox_str,data_str;
		GetDlgItemText(YEAR_END_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_end_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_end_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_END_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeOutComboxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_yearp)
	{
		CString combox_str,data_str;
		GetDlgItemText(YEAR_OUT_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_out_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_out_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_OUT_EDIT1),data_str);
	}
}


void MainMenue::OnCbnSelchangeInComboxy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CheckState();
	if (NULL != cur_yearp)
	{
		CString combox_str,data_str;
		GetDlgItemText(YEAR_IN_COMBOX,combox_str);
		if ("�ܿ����" == combox_str)
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_in_card());
		}
		else
		{
			data_str.Format("%.1lf",cur_yearp->year_record->get_year_money_in_cards(FindCard(combox_str)));
		}
		::SetWindowText(::GetDlgItem(m_hWnd,YEAR_IN_EDIT1),data_str);
	}
}


void MainMenue::OnBnClickedDe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (FALSE == CheckDate())
	{
		return;
	}
	OutRecord outdlg;
	outdlg.set_cards(cards);
	outdlg.DoModal();
}

BOOL MainMenue::SaveData()
{
	char szBuf[MAX_PATH];
    CString strPath("");
    ::GetModuleFileName(NULL, szBuf, MAX_PATH);
    strPath = (LPCSTR)szBuf;
    strPath = strPath.Left(strPath.ReverseFind('\\'));
    strPath += "\\record.dat";

	FILE *out1;
	if ((out1 = fopen(strPath,"wb")) == NULL)
	{
		return FALSE;
	}
	Years p = years;
	for (;NULL != p;p = p->next)
	{
		fwrite(p,sizeof(yyear),1,out1);
		YearRecord * yearp = p->year_record;
		fwrite(yearp,sizeof(YearRecord),1,out1);
		for (int i = 0;i < 12;i++)
		{
			if (yearp->month_records[i] != NULL)
			{
				MonthRecord * monthp = yearp->month_records[i];
				fwrite(monthp,sizeof(MonthRecord),1,out1);
				for (int j = 0;j < 31;j++)
				{
					if (monthp->day_records[j] != NULL)
					{
						DayRecord * dayp = monthp->day_records[j];
						fwrite(dayp,sizeof(DayRecord),1,out1);
						Records rp = dayp->records;
						for (;NULL != rp;rp = rp->next)
						{
							fwrite(rp,sizeof(Record),1,out1);
							if (NULL != rp->record_info)
							{
								CString * sp = rp->record_info;
								//fwrite(sp,sizeof(CString),1,out1);
								int len = sp->GetLength();
								fwrite(&len,sizeof(int),1,out1);
								fwrite(sp->GetBuffer(),sizeof(char),len,out1);
								sp->ReleaseBuffer();
							}
						}
					}
				}
			}
		}
	}
	fclose(out1);
	return TRUE;
}

BOOL MainMenue::LoadData()
{
	char szBuf[MAX_PATH];
    CString strPath("");
    ::GetModuleFileName(NULL, szBuf, MAX_PATH);
    strPath = (LPCSTR)szBuf;
    strPath = strPath.Left(strPath.ReverseFind('\\'));
    strPath += "\\record.dat";

	FILE * in1;
	if((in1 = fopen(strPath,"rb")) == NULL)
	{
		MessageBox("�Ҳ�����¼�ļ���ϵͳ���ݳ�ʼ����","��ʾ");
		return FALSE;
	}

	Years p = NULL;
	Years tail = NULL;
	while(!feof(in1))
	{
		p = (Years)malloc(sizeof(yyear));
		fread(p,sizeof(yyear),1,in1);
		if (!feof(in1))
		{
			if (NULL != tail)
			{
				tail->next = p;
				p->next = NULL;
				tail = p;
			}
			else
			{
				years = p;
				p->next = NULL;
				tail = p;
			}
			YearRecord * yearp = (YearRecord *)malloc(sizeof(YearRecord));
			fread(yearp,sizeof(YearRecord),1,in1);
			p->year_record = yearp;
			for (int i = 0;i < 12;i++)
			{
				if (NULL != yearp->month_records[i])
				{
					MonthRecord * monthp = (MonthRecord *)malloc(sizeof(MonthRecord));
					fread(monthp,sizeof(MonthRecord),1,in1);
					yearp->month_records[i] = monthp;
					for (int j = 0;j < 31;j++)
					{
						if (NULL != monthp->day_records[j])
						{
							DayRecord * dayp = (DayRecord *)malloc(sizeof(DayRecord));
							fread(dayp,sizeof(DayRecord),1,in1);
							monthp->day_records[j] = dayp;

							Records rp = dayp->records;
							Records rtail = NULL;
							while (NULL != rp)
							{
								rp = (Records)malloc(sizeof(Record));
								fread(rp,sizeof(Record),1,in1);
								if (NULL != rp->record_info)
								{
									CString * sp = new CString();
									//fread(sp,sizeof(CString),1,in1);
									int len = 0;
									fread(&len,sizeof(int),1,in1);
									char * cp = new char[len+1];

									fread(cp,sizeof(char),len,in1);
									cp[len] = '\0';
									sp->Format("%s",cp);
									delete [] cp;
									rp->record_info = sp;
								}
								if (NULL == rtail)
								{
									dayp->records = rp;
									rtail = rp;
								}
								else
								{
									rtail->next = rp;
									rtail = rp;

								}
								rp = rp->next;
							}
						

							
							
						}
					}
				}
			}
		}
	}
	fclose(in1);
	return TRUE;
}

void MainMenue::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE == SaveData())
	{
		not_save = FALSE;
		MessageBox("����ɹ���","��ʾ");
	}
	else
	{
		MessageBox("����ʧ�ܣ�","��ʾ");
	}
}


void MainMenue::OnBnClickedIn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CheckState();
	TableDayIn table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.day_p = cur_dayp;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnBnClickedOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TableDayOut table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.day_p = cur_dayp;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	return;
}


void MainMenue::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (TRUE == not_save)
	{
		int result = MessageBox("��δ�����������¼���Ƿ񱣴棿","��ʾ",MB_YESNO);
		if (IDYES == result)
		{
			if (TRUE == SaveData())
			{
				not_save = FALSE;
				MessageBox("����ɹ���","��ʾ");
			}
			else
			{
				MessageBox("����ʧ�ܣ�","��ʾ");
			}
			not_save = FALSE;
		}
	}
	CDialog::OnCancel();
}


void MainMenue::OnBnClickedInm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TableMonthIn table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.month_p = cur_monthp;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnBnClickedOutm()
{
	TableMonthOut table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.month_p = cur_monthp;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnBnClickedIny()
{
	TableYearIn table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.year_p = cur_yearp->year_record;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnBnClickedOuty()
{
	TableYearOut table_dlg;
	table_dlg.Date = Date;
	//cur_dayp->records->record_info = "sadf";
	table_dlg.year_p = cur_yearp->year_record;
	table_dlg.set_cards(cards);
	table_dlg.DoModal();
}


void MainMenue::OnBnClickedEx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (FALSE == CheckDate())
	{
		return;
	}

	ExRecord indlg;
	indlg.set_cards(cards);
	indlg.DoModal();
}
