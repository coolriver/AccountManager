#pragma once
#include "DayRecord.h"

class MonthRecord
{
private:
	
	

	double month_money_start_cash;
	double month_money_start_card;
	double month_money_end_cash;
	double month_money_end_card;
	double month_money_in_cash;
	double month_money_in_card;
	double month_money_out_cash;
	double month_money_out_card;
	double month_money_start_cards[MAXCARD];
	double month_money_end_cards[MAXCARD];
	double month_money_in_cards[MAXCARD];
	double month_money_out_cards[MAXCARD];
public:
	short month;
	void calculate(Records record);
	DayRecord * day_records[31];
	void set_month_money_start_cash(double num);
	void set_month_money_start_card(double num);
	void set_month_money_end_cash(double num);
	void set_month_money_end_card(double num);
	void set_month_money_start_cards(double num,int card_num);
	void set_month_money_end_cards(double num,int card_num);

	double get_month_money_start_cash();
	double get_month_money_start_card();
	double get_month_money_end_cash();
	double get_month_money_end_card();
	double get_month_money_in_cash();
	double get_month_money_in_card();
	double get_month_money_out_cash();
	double get_month_money_out_card();
	double get_month_money_start_cards(int card_num);
	double get_month_money_end_cards(int card_num);
	double get_month_money_in_cards(int card_num);
	double get_month_money_out_cards(int card_num);

	MonthRecord(void);
	~MonthRecord(void);
};

