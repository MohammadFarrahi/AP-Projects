#ifndef DATE_HPP
#define DATE_HPP "DATE_HPP"
#include<string>

class Date {
public:
	
	Date(std::string _month, int _day, int _year);
	Date(std::string date_in_string);
	void set_date(std::string _month, int _day, int _year);
	std::string get_month();
	int get_day();
	int get_year();
	std::string get_date_in_string();

private:
	std::string month;
	int day;
	int year;
};

#endif