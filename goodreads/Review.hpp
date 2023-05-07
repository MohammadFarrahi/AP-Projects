#ifndef REVIEW_HPP
#define REVIEW_HPP "REVIEW_HPP"

#include"Date.hpp"
#include"Author.hpp"
#include"User.hpp"
#include"Book.hpp"

typedef int ID;

class Review {
public:
	Review(ID _id, int _rating, int _likes, std::string _date, Book* _book_ptr, User* _user_ptr);
	Book* get_book_ptr();
	User* get_reviewer_ptr();
	int get_review_likes();
	int get_rating_of_book();
	ID get_id() const;
	std::string get_info();

private:
	ID id;
	Book* book_ptr;
	User* reviewer;
	int rating_of_book;
	int review_likes;
	Date date_of_review;

};

#endif