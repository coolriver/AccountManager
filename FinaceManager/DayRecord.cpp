#include "StdAfx.h"
#include "DayRecord.h"


DayRecord::DayRecord(void)
{
	day = 0;
	records = NULL;
	day_money_start_cash = 0;
	day_money_start_card = 0;
	day_money_end_cash = 0;
	day_money_end_card = 0;
	day_money_in_cash = 0;
	day_money_in_card = 0;
	day_money_out_cash = 0;
	day_money_out_card = 0;
	
	for (int i = 0;i < MAXCARD;i++)
	{
		day_money_start_cards[i] = 0;
		day_money_end_cards[i] = 0;
		day_money_in_cards[i] = 0;
		day_money_out_cards[i] = 0;
	}
	
}


DayRecord::~DayRecord(void)
{
	Records p = records;
	while (p != NULL)
	{
	    Records q = p;
		delete q->record_info;
		p = p->next;
		free(q);
		q = NULL;

	}
	records = NULL;
}

void DayRecord::AddRecord(record_type type,record_direct direct,short card_num,double money_num,CString info)
{
	/*
	Records adder = (Records)malloc(sizeof(Record));
	adder->type = type;
	adder->direct = direct;
	adder->card_num = card_num;
	adder->money_num = money_num;
	//adder->record_info = info.GetBuffer(info.GetLength());
	//memcpy(adder->record_info,info.GetBuffer(),info.GetLength());
	info.ReleaseBuffer();
	adder->next = records->next;
	records->next = adder;

	if (type = income)
	{
		if (direct = cash)
		{
			day_money_in_cash += money_num;
		}
		else
		{
			day_money_in_card += money_num;
			day_money_in_cards[card_num] += money_num;
		}
	}
	else
	{
		if(direct = cash)
		{
			day_money_out_cash += money_num;
		}
		else
		{
			day_money_out_card += money_num;
			day_money_out_cards[card_num] += money_num;
		}
	}*/
}

void DayRecord::set_day_money_start_cash(double num)
{
	this->day_money_start_cash = num;
}

void DayRecord::set_day_money_start_card(double num)
{
	this->day_money_start_card = num;
}

void DayRecord::set_day_money_end_cash(double num)
{
	this->day_money_end_cash = num;
}

void DayRecord::set_day_money_end_card(double num)
{
	this->day_money_end_card = num;
}

void DayRecord::set_day_money_start_cards(double num,int card_num)
{
	this->day_money_start_cards[card_num] = num;
}

void DayRecord::set_day_money_end_cards(double num,int card_num)
{
	this->day_money_end_cards[card_num] = num;
}

double DayRecord::get_day_money_start_cash()
{
	return this->day_money_start_cash;
}

double DayRecord::get_day_money_start_card()
{
	return this->day_money_start_card;
}

double DayRecord::get_day_money_end_cash()
{
	return this->day_money_end_cash;
}

double DayRecord::get_day_money_end_card()
{
	return this->day_money_end_card;
}

double DayRecord::get_day_money_in_cash()
{
	return this->day_money_in_cash;
}

double DayRecord::get_day_money_in_card()
{
	return this->day_money_in_card;
}

double DayRecord::get_day_money_out_cash()
{
	return this->day_money_out_cash;
}

double DayRecord::get_day_money_out_card()
{
	return this->day_money_out_card;
}

double DayRecord::get_day_money_start_cards(int card_num)
{
	return this->day_money_start_cards[card_num];
}

double DayRecord::get_day_money_end_cards(int card_num)
{
	return this->day_money_end_cards[card_num];
}

double DayRecord::get_day_money_in_cards(int card_num)
{
	return this->day_money_in_cards[card_num];
}

double DayRecord::get_day_money_out_cards(int card_num)
{
	return this->day_money_out_cards[card_num];
}

void DayRecord::calculate(Records recordp)
{
	if (recordp->type == income)
	{
		if (recordp->direct == cash)
		{
			day_money_in_cash += recordp->money_num;
			day_money_end_cash += recordp->money_num;
		}
		else
		{
			day_money_in_card += recordp->money_num;
			day_money_in_cards[recordp->card_num] += recordp->money_num;
			day_money_end_cards[recordp->card_num] += recordp->money_num;
			day_money_end_card += recordp->money_num;
		}
	}
	else if (recordp->type == outcome)
	{
		if(recordp->direct == cash)
		{
			day_money_out_cash += recordp->money_num;
			day_money_end_cash -= recordp->money_num;

		}
		else
		{
			day_money_out_card += recordp->money_num;
			day_money_out_cards[recordp->card_num] += recordp->money_num;
			day_money_end_cards[recordp->card_num] -= recordp->money_num;
			day_money_end_card -= recordp->money_num;
		}
	}
	else if (recordp->type == exchange)
	{
	//	char * str = recordp->record_info->GetBuffer();
	//	char * d = "#$@";
	//	char * from = strtok(str,d);
	//	char * to = strtok(NULL,d);
	//	char * from_num = strtok(NULL,d);
	//	char * to_num = strtok(NULL,d);
	//	day_money_end_cash = day_money_start_cash + day_money_in_cash - day_money_out_cash;
	//	day_money_end_card = day_money_start_card + day_money_in_card - day_money_out_card;
	//	for (int i = 0;i < MAXCARD;i++)
	//	{
	//		day_money_end_cards[i] = day_money_start_cards[i] + day_money_in_cards[i] - day_money_out_cards[i];
	//	}
		int curPos = 0;
		CString from = recordp->record_info->Tokenize("#",curPos);
		CString to = recordp->record_info->Tokenize("#",curPos);
		CString from_num = recordp->record_info->Tokenize("#",curPos);
		CString to_num = recordp->record_info->Tokenize("#",curPos);
		if (from == "现金" && to != "现金")
		{
			int t_num = atoi(to_num);
			day_money_end_cash -= recordp->money_num;
			day_money_end_card += recordp->money_num;
			day_money_end_cards[t_num] += recordp->money_num;
		}
		else if (from != "现金" && to == "现金")
		{
			int f_num = atoi(from_num);
			day_money_end_cash += recordp->money_num;
			day_money_end_card -= recordp->money_num;
			day_money_end_cards[f_num] -= recordp->money_num;
		}
		else if (from != "现金" && to != "现金")
		{
			int t_num = atoi(to_num);
			int f_num = atoi(from_num);
			day_money_end_cards[f_num] -= recordp->money_num;
			day_money_end_cards[t_num] += recordp->money_num;
		}

	//	recordp->record_info->ReleaseBuffer();

	}
}

void DayRecord::AddRecord(Records recordp)
{
	if (NULL == records)
	{
		records = recordp;
		recordp->next = NULL;
	}
	else
	{
		recordp->next = records;
		records = recordp;
	}

}