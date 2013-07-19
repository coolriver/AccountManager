#include "StdAfx.h"
#include "MonthRecord.h"


MonthRecord::MonthRecord(void)
{
	month = 0;
	for (int i = 0;i < 31;i++)
	{
		day_records[i] = NULL;
	}
	month_money_start_cash = 0;
	month_money_start_card = 0;
	month_money_end_cash = 0;
	month_money_end_card = 0;
	month_money_in_cash = 0;
	month_money_in_card = 0;
	month_money_out_cash = 0;
	month_money_out_card = 0;

	for (int i = 0;i < MAXCARD;i++)
	{
		month_money_start_cards[i] = 0;
		month_money_end_cards[i] = 0;
		month_money_in_cards[i] = 0;
		month_money_out_cards[i] = 0;
	}
}


MonthRecord::~MonthRecord(void)
{
	for (int i = 0;i < 31;i++)
	{
		if (NULL != this->day_records[i])
		{
			delete day_records[i];
			day_records[i] = NULL;
		}
	}
}



void MonthRecord::set_month_money_start_cash(double num)
{
	this->month_money_start_cash = num;
}

void MonthRecord::set_month_money_start_card(double num)
{
	this->month_money_start_card = num;
}

void MonthRecord::set_month_money_end_cash(double num)
{
	this->month_money_end_cash = num;
}

void MonthRecord::set_month_money_end_card(double num)
{
	this->month_money_end_card = num;
}

void MonthRecord::set_month_money_start_cards(double num,int card_num)
{
	this->month_money_start_cards[card_num] = num;
}

void MonthRecord::set_month_money_end_cards(double num,int card_num)
{
	this->month_money_end_cards[card_num] = num;
}

double MonthRecord::get_month_money_start_cash()
{
	return this->month_money_start_cash;
}

double MonthRecord::get_month_money_start_card()
{
	return this->month_money_start_card;
}

double MonthRecord::get_month_money_end_cash()
{
	return this->month_money_end_cash;
}

double MonthRecord::get_month_money_end_card()
{
	return this->month_money_end_card;
}

double MonthRecord::get_month_money_in_cash()
{
	return this->month_money_in_cash;
}

double MonthRecord::get_month_money_in_card()
{
	return this->month_money_in_card;
}

double MonthRecord::get_month_money_out_cash()
{
	return this->month_money_out_cash;
}

double MonthRecord::get_month_money_out_card()
{
	return this->month_money_out_card;
}

double MonthRecord::get_month_money_start_cards(int card_num)
{
	return this->month_money_start_cards[card_num];
}

double MonthRecord::get_month_money_end_cards(int card_num)
{
	return this->month_money_end_cards[card_num];
}

double MonthRecord::get_month_money_in_cards(int card_num)
{
	return this->month_money_in_cards[card_num];
}

double MonthRecord::get_month_money_out_cards(int card_num)
{
	return this->month_money_out_cards[card_num];
}

void MonthRecord::calculate(Records recordp)
{
	if (recordp->type == income)
	{
		if (recordp->direct == cash)
		{
			month_money_in_cash += recordp->money_num;
			month_money_end_cash += recordp->money_num;
		}
		else
		{
			month_money_in_card += recordp->money_num;
			month_money_in_cards[recordp->card_num] += recordp->money_num;
			month_money_end_cards[recordp->card_num] += recordp->money_num;
			month_money_end_card += recordp->money_num;
		}
	}
	else if (recordp->type == outcome)
	{
		if(recordp->direct == cash)
		{
			month_money_out_cash += recordp->money_num;
			month_money_end_cash -= recordp->money_num;

		}
		else
		{
			month_money_out_card += recordp->money_num;
			month_money_out_cards[recordp->card_num] += recordp->money_num;
			month_money_end_cards[recordp->card_num] -= recordp->money_num;
			month_money_end_card -= recordp->money_num;
		}
	}
	else if (recordp->type == exchange)
	{

		int curPos = 0;
		CString from = recordp->record_info->Tokenize("#",curPos);
		CString to = recordp->record_info->Tokenize("#",curPos);
		CString from_num = recordp->record_info->Tokenize("#",curPos);
		CString to_num = recordp->record_info->Tokenize("#",curPos);
		if (from == "现金" && to != "现金")
		{
			int t_num = atoi(to_num);
			month_money_end_cash -= recordp->money_num;
			month_money_end_card += recordp->money_num;
			month_money_end_cards[t_num] += recordp->money_num;
		}
		else if (from != "现金" && to == "现金")
		{
			int f_num = atoi(from_num);
			month_money_end_cash += recordp->money_num;
			month_money_end_card -= recordp->money_num;
			month_money_end_cards[f_num] -= recordp->money_num;
		}
		else if (from != "现金" && to != "现金")
		{
			int t_num = atoi(to_num);
			int f_num = atoi(from_num);
			month_money_end_cards[f_num] -= recordp->money_num;
			month_money_end_cards[t_num] += recordp->money_num;
		}	
	}
}