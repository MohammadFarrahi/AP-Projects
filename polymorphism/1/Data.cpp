#include"Data.hpp"
#include<sstream>

using namespace std;


void Data::delete_included_data() {}

Integer::Integer(int data_) : data(data_) {}

string Integer::make_text_to_be_showed(int number_of_tabs_of_line, string additional_info){

	string text_of_data = NONE;
	text_of_data += add_tabs_to_text(number_of_tabs_of_line);
	text_of_data += additional_info;
	text_of_data += to_string(data);
	return text_of_data;
}

String::String(string data_) : data(data_) {}

string String::make_text_to_be_showed(int number_of_tabs_of_line, string additional_info){

	string text_of_data = NONE;
	text_of_data += add_tabs_to_text(number_of_tabs_of_line);
	text_of_data += additional_info;
	text_of_data += NOTATIONS[D_cote] + data + NOTATIONS[D_cote];
	return text_of_data;
}

string add_tabs_to_text(int number_of_tabs_of_line){

	string tabs = NONE;
	for(int i = 0; i < number_of_tabs_of_line; i++){
		tabs += TAB;
	}
	return tabs;
}
