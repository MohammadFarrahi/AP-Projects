#ifndef GOODREADS_HPP
#define GOODREADS_HPP "GOODREADS_HPP"

#include<vector>
#include<string>
#include"Author.hpp"
#include"SupplementData.hpp"
#include"User.hpp"
#include"Book.hpp"
#include"Review.hpp"

typedef int ID;

class GoodReads {
public:
	void set_authors(std::vector<Author> _authors);
	void set_users(std::vector<User> _users);
	void set_books(std::vector<Book> books);
	void set_reviews(std::vector<Review> reviews);
	SupplementData get_supplement_datas();
	void* find_special_item(char category, ID id);
	std::string get_author_info(ID id);
	std::string get_user_credit(ID id);
	std::string get_best_book_info();
	std::string get_best_user_info();
	std::string get_sorted_shelf_info(ID id, std::string shelf_type, std::string genre);
	std::string recommend_first_approach(ID user_id);
	std::string recommend_second_approach(ID user_id);

private:
	std::vector<User> users;
	std::vector<Author> authors;
	SupplementData books_and_reviews;

	User* find_user(ID id);
	Author* find_author(ID id);
};

#endif