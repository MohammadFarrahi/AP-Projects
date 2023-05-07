#include "Review.hpp"
#include<sstream>

using namespace std;


Review::Review(ID _id, int _rating, int _likes, string _date, Book* _book_ptr, User* _user_ptr)

	: date_of_review(_date)
{
	id = _id;
	rating_of_book = _rating;
	review_likes = _likes;
	book_ptr = _book_ptr;
	reviewer = _user_ptr;
}

Book* Review::get_book_ptr() { return book_ptr; }

ID Review::get_id()const { return id; }

int Review::get_review_likes() { return review_likes; }

int Review::get_rating_of_book() { return rating_of_book; }

User* Review::get_reviewer_ptr() { return reviewer; }

string Review::get_info(){

	ostringstream os;

	os << "id: " << id << " Rating: " << rating_of_book << " Likes: " << review_likes << " Date: " ;
	os << date_of_review.get_date_in_string() << endl;

	return os.str();
}
