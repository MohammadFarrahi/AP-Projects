#include"GoodReads.hpp"
#include<iomanip>
#include<sstream>

#define CREDIT_PERCISION 6
#define FIND_USER_TYPE 'U'
#define FIND_AUTHOR_TYPE 'A'
#define FIND_BOOK_TYPE 'B'
#define FIND_REVIEW_TYPE 'R'

using namespace std;


void GoodReads::set_authors(vector<Author> _authors){

	authors = _authors;
}

void GoodReads::set_users(vector<User> _users){

	users = _users;
}
void GoodReads::set_books(std::vector<Book> books){

	books_and_reviews.set_books(books);
}

void GoodReads::set_reviews(std::vector<Review> reviews){

	books_and_reviews.set_reviews(reviews);
}

User* GoodReads::find_user(ID id){

	for(int index = 0; index < users.size(); index++){

		if(id == users[index].get_id()){
			return &users[index];
		}
	}
	return NULL;
}

Author* GoodReads::find_author(ID id){

	for(int index = 0; index < authors.size(); index++){

		if(id == authors[index].get_id()){
			return &authors[index];
		}
	}
	return NULL;
}

void* GoodReads::find_special_item(char category, ID id){

	if(category == FIND_USER_TYPE){

		User* user_ptr = find_user(id);
		return user_ptr;
	}
	if(category == FIND_AUTHOR_TYPE){

		Author* author_ptr = find_author(id);
		return author_ptr;
	}
	if(category == FIND_BOOK_TYPE || category == FIND_REVIEW_TYPE){

		void* ptr = books_and_reviews.find_supplement_data(category, id);
		return ptr;
	}
}

SupplementData GoodReads::get_supplement_datas() { return books_and_reviews; }

string GoodReads::get_author_info(ID id){

		string author_info;
		Author* author_to_be_showed = find_author(id);
		author_info = author_to_be_showed->get_info(books_and_reviews.get_books());

		return author_info;
}

string GoodReads::get_sorted_shelf_info(ID id, string shelf_type, string genre){

	User* user_to_show_shelf = find_user(id);
	return user_to_show_shelf -> get_sorted_shelf_info(shelf_type, genre);
}

string GoodReads::get_user_credit(ID id){

	double user_credit = books_and_reviews.get_credit_of_user(id);
	ostringstream os;
	os << fixed << setprecision(CREDIT_PERCISION) << user_credit;
	return os.str();
}

string GoodReads::get_best_book_info(){

	return books_and_reviews.get_best_book_info();
}

string GoodReads::get_best_user_info(){

	string best_user_info;
	pair<double, ID> best_user = books_and_reviews.find_best_user(users);

	best_user_info = find_user(best_user.second)-> get_info();
	best_user_info += "Number of Likes: ";
	best_user_info = best_user_info + to_string((long)best_user.first) + '\n';

	return best_user_info;
}

string GoodReads::recommend_first_approach(ID user_id){

	return books_and_reviews.recommend_suitable_book_to_user_type_1(find_user(user_id));
}

string GoodReads::recommend_second_approach(ID user_id){

	return books_and_reviews.recommend_suitable_book_to_user_type_2(find_user(user_id));
}
