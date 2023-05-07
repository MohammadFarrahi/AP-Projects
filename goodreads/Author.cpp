#include"Author.hpp"
#include"Book.hpp"
#include<sstream>
#include<algorithm>
#include<utility>

using namespace std;


Author::Author(ID _id, string _name, string _gender, string _member_since,
	int _year_of_birth, string _place_of_birth, vector<string> _genres)

	: member_since(_member_since)
{
	sort(_genres.begin(), _genres.end());
	id = _id;
	name = _name;
	gender = _gender;
	year_of_birth = _year_of_birth;
	place_of_birth = _place_of_birth;
	genres = _genres;
}

ID Author::get_id()const { return id; }

string Author::get_name()const { return name; }

string Author::get_personal_info_in_string(){

	ostringstream info_stream;

	info_stream << "id: " << id <<endl;
	info_stream << "Name: " << name << endl;
	info_stream << "Year of Birth: " << year_of_birth << endl;
	info_stream << "Place of Birth: " << place_of_birth << endl;
	info_stream << "Member Since: " << member_since.get_date_in_string() << endl;
	info_stream << "Genres: ";

	for(int i = 0; i < genres.size(); i++){

		info_stream << genres[i] ;
		if(i == genres.size() - 1){
			info_stream << endl;
		}
		else{
		info_stream << ", ";
		}
	}
	return info_stream.str();
}

string Author::get_info(vector<Book> books_list){

	ostringstream info_stream;
	vector<pair<ID, string> > author_books;

	info_stream << get_personal_info_in_string() << "Books:" << endl;

	for(int index = 0; index < books_list.size(); index++){

		if(books_list[index].get_author_ptr()->get_id() == id){
			author_books.push_back(make_pair(books_list[index].get_id(), books_list[index].get_title()));
		}
	}
	sort(author_books.begin(), author_books.end());
	for(pair<ID, string> book : author_books){
		info_stream << "id: " << book.first << " Title: " << book.second << endl;
	}
	
	return info_stream.str();
}

