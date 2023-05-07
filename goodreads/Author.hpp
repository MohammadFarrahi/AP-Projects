#ifndef AUTHOR_HPP
#define AUTHOR_HPP "AUTHOR_HPP"

#include"Date.hpp"
#include<vector>
#include<string>

typedef int ID;
class Book;

class Author {
public:
	Author(ID _id, std::string _name, std::string _gender, std::string _member_since,
	int _year_of_birth, std::string _place_of_birth, std::vector<std::string> _genres);
	ID get_id() const;
	std::string get_name() const;
	std::string get_personal_info_in_string();
	std::string get_info(std::vector<Book> books_list);

private:
	ID id;
	std::string name;
	std::string gender;
	Date member_since;
	int year_of_birth;
	std::string place_of_birth;
	std::vector< std::string > genres;
};

#endif