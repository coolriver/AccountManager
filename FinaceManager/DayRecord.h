#pragma once
#define MAXCARD 20

enum record_type{income,outcome,exchange};
enum record_direct{cash,card};
typedef struct re{
	
	record_type type;
	record_direct direct;
	short card_num;
	double money_num;
	CString * record_info;
	//CString record_info;
	struct re * next;
}Record,* Records;

class DayRecord
{
private:
	
	
	double day_money_start_cash;
	double day_money_start_card;
	double day_money_end_cash;
	double day_money_end_card;
	double day_money_in_cash;
	double day_money_in_card;
	double day_money_out_cash;
	double day_money_out_card;
	double day_money_start_cards[MAXCARD];
	double day_money_end_cards[MAXCARD];
	double day_money_in_cards[MAXCARD];
	double day_money_out_cards[MAXCARD];
public:
	Records records;
	short day;
	void calculate(Records record);
	void AddRecord(record_type type,record_direct direct,short card_num,double money_num,CString info);
	void AddRecord(Records recordp);
	void set_day_money_start_cash(double num);
	void set_day_money_start_card(double num);
	void set_day_money_end_cash(double num);
	void set_day_money_end_card(double num);
	void set_day_money_start_cards(double num,int card_num);
	void set_day_money_end_cards(double num,int card_num);

	double get_day_money_start_cash();
	double get_day_money_start_card();
	double get_day_money_end_cash();
	double get_day_money_end_card();
	double get_day_money_in_cash();
	double get_day_money_in_card();
	double get_day_money_out_cash();
	double get_day_money_out_card();
	double get_day_money_start_cards(int card_num);
	double get_day_money_end_cards(int card_num);
	double get_day_money_in_cards(int card_num);
	double get_day_money_out_cards(int card_num);

	DayRecord(void);
	~DayRecord(void);
};

