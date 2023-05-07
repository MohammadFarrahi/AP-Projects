#ifndef BOOK_HPP
#define BOOK_HPP "BOOK_HPP"

#include"Author.hpp"
#include<string>

typedef int ID;
class Review;

class Book {
public:
	void set_reviews(std::vector<Review*> _reviews);
	Book(ID _id, std::string _title, std::string _genre, Author* _author_ptr,
	std::vector<Review*> _reviews = {});
	ID get_id() const;
	std::string get_title() const;
	std::string get_genre();
	Author* get_author_ptr();
	std::pair<double, ID> avrage_rating();
	std::vector<std::pair<int, ID> > get_reviews_rating();
	std::string get_all_info_of_book_in_string(int type);

private:
	ID id;
	std::string title;
	std::string genre;
	Author* author_ptr;
	std::vector<Review*> reviews;
};

bool order_sorting_reviews_manner(const Review* r1, const Review* r2);

#endif