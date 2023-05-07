#ifndef SUPPLEMENT_HPP
#define SUPPLEMENT_HPP "SUPPLEMENT_HPP"

#include<vector>
#include"User.hpp"
#include"Book.hpp"
#include"Review.hpp"

typedef int ID;

class SupplementData {
public:
	void set_reviews(std::vector<Review> _reviews);
	void set_books(std::vector<Book> _books);
	std::vector<Book> get_books();
	std::vector<Review> get_reviews();
	void* find_supplement_data(char category, ID id);
	double get_credit_of_user(ID user_id);
	std::string get_best_book_info();
	std::pair<double, ID> find_best_user(std::vector<User> users);
	std::string recommend_suitable_book_to_user_type_1(User* user);
	std::string recommend_suitable_book_to_user_type_2(User* user);

private:
	std::vector<Book> books;
	std::vector<Review> reviews;

	Book* find_book(ID id);
	Review* find_review(ID id);
	std::pair<double, ID> find_best_book();
	double calculate_rating_of_book(std::vector<std::pair<int, ID> > reviews_info);
	std::vector<ID> find_best_read_books(std::vector<Book*> read_shelf_books);
};

ID get_commen_id(std::vector<ID> ides);
bool order_sorting_books_score_manner(const std::pair<double, ID>& p1,const std::pair<double, ID>& p2);

#endif