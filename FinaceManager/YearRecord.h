#pragma once

#include "MonthRecord.h"

class YearRecord
{
private:
	
	
	
	double year_money_start_cash;
	double year_money_start_card;
	double year_money_end_cash;
	double year_money_end_card;
	double year_money_in_cash;
	double year_money_in_card;
	double year_money_out_cash;
	double year_money_out_card;
	double year_money_start_cards[MAXCARD];
	double year_money_end_cards[MAXCARD];
	double year_money_in_cards[MAXCARD];
	double year_money_out_cards[MAXCARD];
public:
	short year;
	MonthRecord * month_records[12];
	void calculate(Records record);
	void set_year_money_start_cash(double num);
	void set_year_money_start_card(double num);
	void set_year_money_end_cash(double num);
	void set_year_money_end_card(double num);
	void set_year_money_start_cards(double num,int card_num);
	void set_year_money_end_cards(double num,int card_num);

	double get_year_money_start_cash();
	double get_year_money_start_card();
	double get_year_money_end_cash();
	double get_year_money_end_card();
	double get_year_money_in_cash();
	double get_year_money_in_card();
	double get_year_money_out_cash();
	double get_year_money_out_card();
	double get_year_money_start_cards(int card_num);
	double get_year_money_end_cards(int card_num);
	double get_year_money_in_cards(int card_num);
	double get_year_money_out_cards(int card_num);

	YearRecord(void);
	~YearRecord(void);
};

