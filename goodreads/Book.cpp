#include"Book.hpp"
#include"Review.hpp"
#include<sstream>
#include<utility>
#include<algorithm>

#define WITH_REVIEWS 2
#define WITHOUT_REVIEWS 1
#define BOOOK_DELIMITER_SIGN "***"

using namespace std;


void Book::set_reviews(vector<Review*> _reviews){

	sort(_reviews.begin(), _reviews.end(), order_sorting_reviews_manner);
	reviews = _reviews;
}

Book::Book(ID _id, std::string _title, std::string _genre, Author* _author_ptr,
vector<Review*> _reviews)
{
	id = _id;
	title = _title;
	genre = _genre;
	author_ptr = _author_ptr;
	reviews = _reviews;
}

ID Book::get_id()const { return id; }

string Book::get_title()const { return title; }

string Book::get_genre(){ return genre; }

Author* Book::get_author_ptr(){ return author_ptr; }

pair<double, ID> Book::avrage_rating(){

	double avrage_rating = 0;
	long number_of_reviews = reviews.size();

	if(number_of_reviews != 0){

		for(int index = 0; index < number_of_reviews; index++){
			avrage_rating += (double)reviews[index]->get_rating_of_book();
		}
	avrage_rating = avrage_rating / number_of_reviews;
	}

	return make_pair(avrage_rating , id);
}

vector<pair<int, ID> > Book::get_reviews_rating(){

	vector<pair<int, ID> > reviews_rating;

	for( Review* review : reviews){
		reviews_rating.push_back(make_pair(review->get_rating_of_book(), review->get_reviewer_ptr()->get_id()));
	}

	return reviews_rating;
}

string Book::get_all_info_of_book_in_string(int type){

	ostringstream info_stream;

	info_stream << "id: " << to_string(get_id()) <<endl;
	info_stream << "Title: " << get_title() << endl;
	info_stream << "Genre: " << get_genre() << endl;
	info_stream << "Author: " << author_ptr -> get_name() << endl;
	if(type == WITH_REVIEWS){

		info_stream << "Reviews:\n";
		for(Review* review : reviews){
			info_stream << review->get_info();
		}	
	}
	return info_stream.str();
}

bool order_sorting_reviews_manner(const Review* r1, const Review* r2){

	return (r1->get_id() < r2->get_id());
}
