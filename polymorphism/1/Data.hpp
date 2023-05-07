#ifndef DATA_HPP
#define DATA_HPP "DATA_HPP"

#include<string>
#include<vector>

#define NONE ""
#define TAB "    "

enum NotationIndex { colon, L_bracket, R_bracket, L_accolade, R_accolade, comma, newline, space, D_cote };

const std::vector<char> NOTATIONS = {':', '[', ']', '{', '}', ',', '\n', ' ', '"'};


class Data {
public:
	virtual std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info) = 0;
	virtual void delete_included_data();
};

class Integer : public Data {
public:
	Integer(int data_);
	std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info);
private:
	int data;
};

class String : public Data {
public:
	String(std::string data_);
	std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info);
private:
	std::string data;
};

std::string add_tabs_to_text(int number_of_tabs_of_line);

#endif
