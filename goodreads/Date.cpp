#include"Date.hpp"
#include<sstream>

#define DEFAULT_MONTH "January"
#define DEFAULT_DAY 1
#define DEFAULT_YEAR 1990

using namespace std;


void Date::set_date(string _month, int _day, int _year){

	month = _month;
	day = _day;
	year = _year;
}

Date::Date(string _month = DEFAULT_MONTH, int _day = DEFAULT_DAY, int _year = DEFAULT_YEAR){

	set_date(_month, _day, _year);
}

Date::Date(string date_in_string){

	int day, year;
	string month;
	stringstream ss(date_in_string);

	ss >> month;
	ss >> day;
	ss >> year;

	set_date(month, day, year);
}

string Date::get_month(){ return month; }

int Date::get_day(){ return day; }

int Date::get_year(){ return year; }

string Date::get_date_in_string(){

	ostringstream os;

	os << month << ' ' << day << ' ' << year;

	return os.str();
}