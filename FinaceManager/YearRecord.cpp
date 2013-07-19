#include "StdAfx.h"
#include "YearRecord.h"


YearRecord::YearRecord(void)
{
	year = 0;
	for (int i = 0;i < 12;i++)
	{
		month_records[i] = NULL;
	}
	year_money_start_cash = 0;
	year_money_start_card = 0;
	year_money_end_cash = 0;
	year_money_end_card = 0;
	year_money_in_cash = 0;
	year_money_in_card = 0;
	year_money_out_cash = 0;
	year_money_out_card = 0;

	for (int i = 0;i < MAXCARD;i++)
	{
		year_money_start_cards[i] = 0;
		year_money_end_cards[i] = 0;
		year_money_in_cards[i] = 0;
		year_money_out_cards[i] = 0;
	}
}


YearRecord::~YearRecord(void)
{
	for (int i = 0;i < 12;i++)
	{
		if (this->month_records[i] != NULL)
		{
			delete month_records[i];
			month_records[i] = NULL;
		}
	//	delete [] month_records;
	}
}



void YearRecord::set_year_money_start_cash(double num)
{
	this->year_money_start_cash = num;
}

void YearRecord::set_year_money_start_card(double num)
{
	this->year_money_start_card = num;
}

void YearRecord::set_year_money_end_cash(double num)
{
	this->year_money_end_cash = num;
}

void YearRecord::set_year_money_end_card(double num)
{
	this->year_money_end_card = num;
}

void YearRecord::set_year_money_start_cards(double num,int card_num)
{
	this->year_money_start_cards[card_num] = num;
}

void YearRecord::set_year_money_end_cards(double num,int card_num)
{
	this->year_money_end_cards[card_num] = num;
}

double YearRecord::get_year_money_start_cash()
{
	return this->year_money_start_cash;
}

double YearRecord::get_year_money_start_card()
{
	return this->year_money_start_card;
}

double YearRecord::get_year_money_end_cash()
{
	return this->year_money_end_cash;
}

double YearRecord::get_year_money_end_card()
{
	return this->year_money_end_card;
}

double YearRecord::get_year_money_in_cash()
{
	return this->year_money_in_cash;
}

double YearRecord::get_year_money_in_card()
{
	return this->year_money_in_card;
}

double YearRecord::get_year_money_out_cash()
{
	return this->year_money_out_cash;
}

double YearRecord::get_year_money_out_card()
{
	return this->year_money_out_card;
}

double YearRecord::get_year_money_start_cards(int card_num)
{
	return this->year_money_start_cards[card_num];
}

double YearRecord::get_year_money_end_cards(int card_num)
{
	return this->year_money_end_cards[card_num];
}

double YearRecord::get_year_money_in_cards(int card_num)
{
	return this->year_money_in_cards[card_num];
}

double YearRecord::get_year_money_out_cards(int card_num)
{
	return this->year_money_out_cards[card_num];
}

void YearRecord::calculate(Records recordp)
{
	if (recordp->type == income)
	{
		if (recordp->direct == cash)
		{
			year_money_in_cash += recordp->money_num;
			year_money_end_cash += recordp->money_num;
		}
		else
		{
			year_money_in_card += recordp->money_num;
			year_money_in_cards[recordp->card_num] += recordp->money_num;
			year_money_end_cards[recordp->card_num] += recordp->money_num;
			year_money_end_card += recordp->money_num;
		}
	}
	else if (recordp->type == outcome)
	{
		if(recordp->direct == cash)
		{
			year_money_out_cash += recordp->money_num;
			year_money_end_cash -= recordp->money_num;

		}
		else
		{
			year_money_out_card += recordp->money_num;
			year_money_out_cards[recordp->card_num] += recordp->money_num;
			year_money_end_cards[recordp->card_num] -= recordp->money_num;
			year_money_end_card -= recordp->money_num;
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
			year_money_end_cash -= recordp->money_num;
			year_money_end_card += recordp->money_num;
			year_money_end_cards[t_num] += recordp->money_num;
		}
		else if (from != "现金" && to == "现金")
		{
			int f_num = atoi(from_num);
			year_money_end_cash += recordp->money_num;
			year_money_end_card -= recordp->money_num;
			year_money_end_cards[f_num] -= recordp->money_num;
		}
		else if (from != "现金" && to != "现金")
		{
			int t_num = atoi(to_num);
			int f_num = atoi(from_num);
			year_money_end_cards[f_num] -= recordp->money_num;
			year_money_end_cards[t_num] += recordp->money_num;
		}			
	}
}