#include"User.hpp"
#include<algorithm>
#include<sstream>

#define SHELF_TYPE_READ_INDEX 2
#define SHELF_TYPE_WANT_TO_READ_INDEX 0
#define SHELF_TYPE_CURRENTLY_READING_INDEX 1
#define NUMBER_OF_SHELFS 3
#define SHELF_TYPE_READ "read"
#define SHELF_TYPE_WANT_TO_READ "want_to_read"
#define SHELF_TYPE_CURRENTLY_READING "currently_reading"
#define WITH_REVIEWS 2
#define WITHOUT_REVIEWS 1

using namespace std;


void User::set_followings_series(vector<User*> _followings){

		series_of_followings = _followings;
	}

void User::set_id(ID _id) { id = _id; }

void User::set_name(string _name) { name = _name; }

void User::set_place_of_birth(string _place_of_birth){

	place_of_birth = _place_of_birth;
}

void User::set_personal_info(ID id, string name, string place_of_birth){

	set_id(id);
	set_name(name);
	set_place_of_birth(place_of_birth);
}

void User::set_favorite_genres(vector<string> _genres){

	favorite_genres = _genres;
}
void User::set_favorite_aurthors(vector<Author*> _authors_ptr){

	favorite_authors = _authors_ptr;
}

void User::set_shelf(vector<Book*> books_ptr, int shelf_type){

	if(shelf_type == SHELF_TYPE_READ_INDEX){
		shelfs[SHELF_TYPE_READ_INDEX] = books_ptr;
	}
	if(shelf_type == SHELF_TYPE_WANT_TO_READ_INDEX){
		shelfs[SHELF_TYPE_WANT_TO_READ_INDEX] = books_ptr;
	}
	if(shelf_type == SHELF_TYPE_CURRENTLY_READING_INDEX){
		shelfs[SHELF_TYPE_CURRENTLY_READING_INDEX] = books_ptr;
	}
}

User::User(ID _id, string _name, string _place_of_birth, string _member_since, vector<Author*> _favorite_authors,
	 vector<string> _faorite_genres, vector<vector<Book*> > _shelfs, std::vector<User*> _followings)

	: member_since( _member_since )
{
	sort(_faorite_genres.begin(), _faorite_genres.end());
	sort(_favorite_authors.begin(), _favorite_authors.end(), order_sorting_authors_manner);

	set_personal_info(_id, _name, _place_of_birth);
	set_favorite_genres(_faorite_genres);
	set_favorite_aurthors(_favorite_authors);
	set_followings_series(_followings);

	for(int shelf_type = 0; shelf_type < NUMBER_OF_SHELFS; shelf_type ++){
		set_shelf(_shelfs[shelf_type], shelf_type);
	}
}

ID User::get_id() { return id; }

string User::get_name() { return name; }

vector<User*> User::get_followings_series() { return series_of_followings; }

vector<Book*> User::get_shelf(int type) { return shelfs[type]; }

void User::sort_shelf(int shelf_type, string genre_in_emergency){

		vector<Book*> books_in_emergency, other_books;

		for(int book_index = 0; book_index < shelfs[shelf_type].size(); book_index++){

			if(shelfs[shelf_type][book_index]->get_genre() == genre_in_emergency){
				books_in_emergency.push_back(shelfs[shelf_type][book_index]);
			}
			else{
				other_books.push_back(shelfs[shelf_type][book_index]);
			}
		}
		sort(books_in_emergency.begin(), books_in_emergency.end(), order_sorting_books_manner);
		sort(other_books.begin(), other_books.end(), order_sorting_books_manner);

		shelfs[shelf_type] = books_in_emergency;
		shelfs[shelf_type].insert(shelfs[shelf_type].end(), other_books.begin(), other_books.end());
	}

string User::get_sorted_shelf_info(string shelf_type, string genre_in_emergency){

		int shelf_index = 0;
		const string  book_delimiter_sign = "***\n";
		string books_info = "";

		if(shelf_type != SHELF_TYPE_WANT_TO_READ){
			shelf_index++;
			if(shelf_type != SHELF_TYPE_CURRENTLY_READING)
				shelf_index++;
		}
		sort_shelf(shelf_index, genre_in_emergency);
		for(Book* b_ptr : shelfs[shelf_index]){

			 books_info += b_ptr->get_all_info_of_book_in_string(WITHOUT_REVIEWS);
			 books_info += book_delimiter_sign;
		}

		return books_info;
	}

string User::get_info(){

	ostringstream info_stream;

	info_stream << "id: " << get_id() << endl; 
	info_stream << "Name: " << name << endl;
	info_stream << "Place of Birth: " << place_of_birth << endl;
	info_stream << "Member Since: " << member_since.get_date_in_string() << endl;
	info_stream << "Favorite Genres: ";
	for(int i = 0; i < favorite_genres.size(); i++){

		info_stream << favorite_genres[i];
		if(i == favorite_genres.size() - 1){
			info_stream << endl;
		}
		else{
			info_stream << ", ";
		}
	}
	info_stream << "Favorite Authors: ";
	for(int i = 0; i < favorite_authors.size(); i++){

		info_stream << favorite_authors[i]->get_name();
		if(i == favorite_authors.size() - 1){
			info_stream << endl;
		}
		else{
				info_stream << ", ";
		}
	}
	info_stream << "Number of Books in Read Shelf: ";
	info_stream << shelfs[SHELF_TYPE_READ_INDEX].size() << endl;

	info_stream << "Number of Books in Want to Read Shelf: ";
	info_stream << shelfs[SHELF_TYPE_WANT_TO_READ_INDEX].size() << endl;

	info_stream << "Number of Books in Currently Reading Shelf: ";
	info_stream << shelfs[SHELF_TYPE_CURRENTLY_READING_INDEX].size() << endl;

	return info_stream.str();
}

bool User::is_among_favorite_genres(string genre){

	for(string f_genre : favorite_genres){

		if(genre == f_genre){
			return true;
		}
	}
	return false;
}

bool order_sorting_authors_manner(const Author* a1, const Author* a2){

	return (a1->get_id() < a2->get_id());
}

bool order_sorting_books_manner(const Book* b1, const Book* b2){

	if(b1->get_title() == b2->get_title()){
		return (b1->get_id() < b2->get_id());
	}
	return (b1->get_title() < b2->get_title());
}
