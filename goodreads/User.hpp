#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include<string>
#include<vector>
#include"Date.hpp"
#include"Book.hpp"
#include"Author.hpp"

#define NUMBER_OF_SHELFS 3

typedef int ID;

class User {
public:
	void set_favorite_genres(std::vector<std::string> _genres);
	void set_favorite_aurthors(std::vector<Author*> _authors_ptr);
	void set_shelf(std::vector<Book*> books_ptr, int shelf_type);
	void set_personal_info(ID id, std::string name, std::string place_of_birth);
	void set_followings_series(std::vector<User*> _followings);
	User(ID _id, std::string _name, std::string _place_of_birth, std::string _member_since, std::vector<Author*> _favorite_authors,
	 std::vector<std::string> _faorite_genres, std::vector<std::vector<Book*> > _shelfs, std::vector<User*> _followings = {});
	ID get_id();
	std::string get_name();
	std::vector<Book*> get_shelf(int type);
	std::vector<User*> get_followings_series();
	std::string get_sorted_shelf_info(std::string shelf_type, std::string genre_in_emergency);
	std::string get_info();
	bool is_among_favorite_genres(std::string genre);

private:
	ID id;
	std::string name;
	std::string place_of_birth;
	Date member_since;
	std::vector<std::string> favorite_genres;
	std::vector<Author*> favorite_authors;
	std::vector<std::vector<Book*> > shelfs =std::vector<std::vector<Book*> >(NUMBER_OF_SHELFS);
	std::vector<User*> series_of_followings;
	
	void set_id(ID _id);
	void set_name(std::string _name);
	void set_place_of_birth(std::string _place_of_birth);
	void sort_shelf(int shelf_type, std::string genre_in_emergency);
};

bool order_sorting_authors_manner(const Author* a1, const Author* a2);
bool order_sorting_books_manner(const Book* b1, const Book* b2);

#endif