#include"SupplementData.hpp"
#include<utility>
#include<sstream>
#include<algorithm>

#define AVRAGE_RATING_PRECISION 100
#define WITH_REVIEWS 2
#define WITHOUT_REVIEWS 1
#define FIND_BOOK_TYPE 'B'
#define FIND_REVIEW_TYPE 'R'

using namespace std;


void SupplementData::set_books(vector<Book> _books){

	books = _books;
}

void SupplementData::set_reviews(vector<Review> _reviews){

	reviews = _reviews;
}

Book* SupplementData::find_book(ID id){

	for(int index = 0; index < books.size(); index++){

		if(id == books[index].get_id()){
			return &books[index];
		}
	}
	return NULL;
}

Review* SupplementData::find_review(ID id){

	for(int index = 0; index < reviews.size(); index++){

		if(id == reviews[index].get_id()){
			return &reviews[index];
		}
	}
	return NULL;
}

void* SupplementData::find_supplement_data(char category, ID id){

	if(category == FIND_BOOK_TYPE){

		Book* book_ptr = find_book(id);
		return book_ptr;
	}
	if(category == FIND_REVIEW_TYPE){

		Review* review_ptr = find_review(id);
		return review_ptr;
	}
}

vector<Book> SupplementData::get_books() { return books; }

vector<Review> SupplementData::get_reviews() { return reviews; }

double SupplementData::get_credit_of_user(ID user_id){

		double user_credit = 0;
		long number_of_reviews = reviews.size();
		long number_of_user_reviews_likes = 0, number_of_user_review = 0, number_of_likes = 0;

	for(int review_index = 0; review_index < number_of_reviews; review_index++){

		number_of_likes += reviews[review_index].get_review_likes();
		if(reviews[review_index].get_reviewer_ptr()->get_id() == user_id){

			number_of_user_review ++;
			number_of_user_reviews_likes += reviews[review_index].get_review_likes();
		}
	}
	if(number_of_likes != 0 && number_of_reviews != 0){
		user_credit = ((double)number_of_user_reviews_likes / number_of_likes + (double)number_of_user_review / number_of_reviews) / 2;
	}
	else if(number_of_reviews != 0){
		user_credit = ((double)number_of_user_review / number_of_reviews) / 2;
	}
	return user_credit;
}

pair<double, ID> SupplementData::find_best_book(){

	pair<double, ID> best_book_avrage_rating(0,0), avrage_rating_of_cuurent_book(0,0);
	
	for(int index = 0; index < books.size(); index++){

		avrage_rating_of_cuurent_book = books[index].avrage_rating();
		if(avrage_rating_of_cuurent_book.first >= best_book_avrage_rating.first){

			if(avrage_rating_of_cuurent_book.first > best_book_avrage_rating.first){
				best_book_avrage_rating = avrage_rating_of_cuurent_book;
			}
			else{
				best_book_avrage_rating = avrage_rating_of_cuurent_book > best_book_avrage_rating ? best_book_avrage_rating : avrage_rating_of_cuurent_book;
			}
		}
	}
	return best_book_avrage_rating;
}

string SupplementData::get_best_book_info(){
	
	ostringstream best_book_info;
	pair<double, ID> best_book = find_best_book();
	best_book.first = (int)(best_book.first * AVRAGE_RATING_PRECISION + 0.5);
	best_book_info  << find_book(best_book.second)->get_all_info_of_book_in_string(WITHOUT_REVIEWS);
	best_book_info << "Average Rating: ";
	best_book_info << best_book.first / AVRAGE_RATING_PRECISION << endl;
	return best_book_info.str();
}

pair<double, ID> SupplementData::find_best_user(vector<User> users){

	pair<double, ID> best_user(0,0), current_user(0,0);

	for(int user_index = 0; user_index < users.size(); user_index++){

		long number_of_likes = 0;
		current_user.second = users[user_index].get_id();
		for(int review_index = 0; review_index < reviews.size(); review_index++){

			if(current_user.second == reviews[review_index].get_reviewer_ptr()->get_id()){
				number_of_likes += reviews[review_index].get_review_likes();
			}
		}
		current_user.first = (double)number_of_likes;
		if(current_user.first >= best_user.first){

			if(current_user.first > best_user.first){
				best_user = current_user;
			}
			else{
				best_user = current_user > best_user ? best_user : current_user;
			}
		}
	}
	return best_user;
}

double SupplementData::calculate_rating_of_book(vector<pair<int, ID> > reviews_rating_info){

	double book_rating = 0;

	if(reviews_rating_info.size() != 0){
		for(pair<int, ID> review_info : reviews_rating_info){
			book_rating += (double)review_info.first * get_credit_of_user(review_info.second);
		}
		book_rating = book_rating / reviews_rating_info.size();
	}
	return book_rating;
}

string SupplementData::recommend_suitable_book_to_user_type_1(User* user){

	const double no_match_genre_points = 0, match_genre_points = 5;
	pair<double, ID> recommended_book_score(0,0), current_book_score(0,0);

	for(int book_index = 0; book_index < books.size(); book_index++){

		current_book_score.second = books[book_index].get_id();
		current_book_score.first = calculate_rating_of_book(books[book_index].get_reviews_rating());
		current_book_score.first += (user->is_among_favorite_genres(books[book_index].get_genre())) ? match_genre_points : no_match_genre_points;
		if(recommended_book_score.first <= current_book_score.first){

			if(recommended_book_score.first < current_book_score.first){
				recommended_book_score = current_book_score;
			}
			else {
				recommended_book_score = recommended_book_score < current_book_score ? recommended_book_score : current_book_score;
			}
		}
	}
	return find_book(recommended_book_score.second)->get_all_info_of_book_in_string(WITH_REVIEWS);
}

ID get_commen_id(vector<ID> ides){

	int id, repetition = -1;
	bool is_new = true;
	vector<ID> unique_ides;
	vector<int> repetition_of_ides;

	for(int i = 0; i < ides.size(); i++){

		for(int j = 0; j < unique_ides.size(); j++){

			if(ides[i] == unique_ides[j]){
				is_new = false;
				repetition_of_ides[j]++;
			}
		}
		if(is_new){
			repetition_of_ides.push_back(1);
			unique_ides.push_back(ides[i]);
		}
		is_new = true;
	}
	for(int k = 0; k < repetition_of_ides.size(); k++){

		if(repetition_of_ides[k] > repetition){
			id = unique_ides[k];
			repetition = repetition_of_ides[k];
		}
		if(repetition_of_ides[k] == repetition){
			if(id > unique_ides[k]){
				id = unique_ides[k];
			}
		}
	}
	return id;
}

bool order_sorting_books_score_manner(const pair<double, ID>& p1,const pair<double, ID>& p2){

	if(p1.first == p2.first){
		return (p1.second < p2.second);
	}
	return (p1.first > p2.first);
}

vector<ID> SupplementData::find_best_read_books(vector<Book*> read_shelf_books){

	vector<pair<double, ID> > books_score;
	vector<ID> books_id;

	for(Book* book : read_shelf_books){

		pair<double, ID> read_book_score(0,0);
		read_book_score.second = book->get_id();
		read_book_score.first = calculate_rating_of_book(book->get_reviews_rating());
		books_score.push_back(read_book_score);
	}
	sort(books_score.begin(), books_score.end(), order_sorting_books_score_manner);
	for(int i = 0; i<3 && i<books_score.size(); i++){
		books_id.push_back(books_score[i].second);
	}

	return books_id;
}

string SupplementData::recommend_suitable_book_to_user_type_2(User* user){

	const int read_shelf = 2;
	ID book_id;
	vector<ID> possible_books_to_recommend;
	vector<User*> followings = user->get_followings_series();

	for(User* user_following : followings){

		vector<ID> best_books_of_user_following = find_best_read_books(user_following->get_shelf(read_shelf));
		possible_books_to_recommend.insert(possible_books_to_recommend.end(), best_books_of_user_following.begin(), best_books_of_user_following.end());
	}

	return find_book(get_commen_id(possible_books_to_recommend))->get_all_info_of_book_in_string(WITH_REVIEWS);
}
