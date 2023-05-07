#include"InputDataProcess.hpp"

#include<sstream>
#include<fstream>

#define FIND_USER_TYPE 'U'
#define FIND_AUTHOR_TYPE 'A'
#define FIND_BOOK_TYPE 'B'
#define FIND_REVIEW_TYPE 'R'

#define DELIMTER_1 ','
#define DELIMTER_2 '$'
#define NEWLINE_DELIMITER '\n'
#define IGNORE_FIRST_LINE '\n'
#define CHAR_SIZE 1

#define NUMBER_OF_SHELFS 3

#define USERS_FILE_NAME "/users.csv"
#define AUTHORS_FILE_NAME "/authors.csv"
#define BOOKS_FILE_NAME "/books.csv"
#define REVIEWS_FILE_NAME "/reviews.csv"
#define FOLLOW_EDGES_FILE_NAME "/follow_edges.csv"

using namespace std;


vector<string> get_parts_of_line_based_delimiter(string line, char delimiter){

	string subline;
	stringstream line_stream(line);
	vector<string> extracted_sublines_in_string;

	while(getline(line_stream, subline, delimiter)){
		extracted_sublines_in_string.push_back(subline);
	}

	return extracted_sublines_in_string;
}

vector<string> get_genres(string genres_info){

	vector<string> genres;

	genres = get_parts_of_line_based_delimiter(genres_info, DELIMTER_2);

	return genres;
}

Author get_info_of_one_author(string author_info){

	ID id;
	int year_of_birth;
	string name, gender, place_of_birth;
	vector<string> genres;
	vector<string> author_items = get_parts_of_line_based_delimiter(author_info, DELIMTER_1);
	
	id = stoi(author_items[A_id]);
	name = author_items[A_name];
	gender = author_items[A_gender];
	year_of_birth = stoi(author_items[A_year_of_birth]);
	place_of_birth = author_items[A_place_of_birth];
	genres = get_genres(author_items[A_genres]);
	
	return Author(id, name, gender, author_items[A_member_since], year_of_birth, place_of_birth, genres);
}

vector<Author> InputDataProcess::read_authors_info_from_file(string file_path){

	ifstream file_stream(file_path);
	string line;
	vector<Author> authors;

	getline(file_stream, line, IGNORE_FIRST_LINE);
	while(getline(file_stream, line, NEWLINE_DELIMITER)){

		authors.push_back( get_info_of_one_author(line) );
	}
	return authors;
}

Book get_info_of_one_book(string book_info, GoodReads& goodreads){

	ID id , author_id;
	string title, genre;
	Author* author_ptr;
	vector<string> book_items = get_parts_of_line_based_delimiter(book_info, DELIMTER_1);

	id = stoi(book_items[B_id]);
	title = book_items[B_title];
	author_id = stoi(book_items[B_author_id]);
	genre = book_items[B_genre];
	author_ptr = (Author*)goodreads.find_special_item(FIND_AUTHOR_TYPE, author_id);

	return Book(id, title, genre, author_ptr);
}

vector<Book> InputDataProcess::read_books_info_from_file(string file_path, GoodReads& goodreads){

	ifstream file_stream(file_path);
	string line;
	vector<Book> books;

	getline(file_stream, line, IGNORE_FIRST_LINE);
	while(getline(file_stream, line, NEWLINE_DELIMITER)){
		books.push_back( get_info_of_one_book(line, goodreads));
	}

	return books;
}

vector<Book*> convert_books_ides_to_ptr(string shelf_info, GoodReads& goodreads){

	ID id;
	vector<Book*> books_ptr;
	vector<string> books_id_in_string = get_parts_of_line_based_delimiter(shelf_info, DELIMTER_2);

	for(int index = 0; index < books_id_in_string.size(); index++){

		id = stoi(books_id_in_string[index]);
		books_ptr.push_back((Book*)goodreads.find_special_item(FIND_BOOK_TYPE, id));
	}
	return books_ptr;
}

vector<Author*> convert_authors_ides_to_ptr(string authors_id, GoodReads& goodreads){

	ID author_id;
	vector<Author*> favorie_authors_ptr;
	vector<string> favorie_authors_id_in_string = get_parts_of_line_based_delimiter(authors_id, DELIMTER_2);
	
	for(int index = 0; index < favorie_authors_id_in_string.size(); index++){

		author_id = stoi(favorie_authors_id_in_string[index]);
		favorie_authors_ptr.push_back((Author*)goodreads.find_special_item(FIND_AUTHOR_TYPE, author_id));
	}
	return favorie_authors_ptr;
}


User get_info_of_one_user(string user_info, GoodReads& goodreads){

	ID id;
	string place_of_birth, name;
	vector<string> genres;
	vector<Author*> favorie_authors_ptr;
	vector<vector<Book*> > shelfs;
	vector<string> user_items = get_parts_of_line_based_delimiter(user_info, DELIMTER_1);
	
	id = stoi(user_items[U_id]);
	name = user_items[U_name];
	place_of_birth = user_items[U_place_of_birth];

	favorie_authors_ptr =  convert_authors_ides_to_ptr(user_items[U_favorie_authors], goodreads);
	genres = get_genres(user_items[U_favorite_genres]);
	for(int index = U_shelfs; index < (NUMBER_OF_SHELFS + U_shelfs); index++){

		vector<Book*> books_ptr;
		books_ptr = convert_books_ides_to_ptr(user_items[index], goodreads);
		shelfs.push_back(books_ptr);
	}
	return User(id, name, place_of_birth, user_items[U_member_since], favorie_authors_ptr, genres, shelfs);
}


vector<User> InputDataProcess::read_users_info_from_file(string file_path, GoodReads& goodreads){

	ifstream file_stream(file_path);
	string line;
	vector<User> users;

	getline(file_stream, line, IGNORE_FIRST_LINE);
	while(getline(file_stream, line, NEWLINE_DELIMITER)){

		users.push_back( get_info_of_one_user(line, goodreads));
	}
	return users;
}

Review get_info_of_one_review(string review_info, GoodReads& goodreads){

	ID id;
	Book* book_ptr;
	User* reviewer_ptr;
	int rating, likes;
	vector<string> review_items = get_parts_of_line_based_delimiter(review_info, DELIMTER_1);

	id = stoi(review_items[R_id]);
	rating = stoi(review_items[R_rating]);
	likes = stoi(review_items[R_number_of_likes]);
	reviewer_ptr = (User*)goodreads.find_special_item(FIND_USER_TYPE, stoi(review_items[R_reviewer]));
	book_ptr = (Book*)goodreads.find_special_item(FIND_BOOK_TYPE, stoi(review_items[R_book_id]));

	return Review(id, rating, likes, review_items[R_date], book_ptr, reviewer_ptr);
}

vector<Review> InputDataProcess::read_reviews_info_from_file(string file_path, GoodReads& goodreads){

	ifstream file_stream(file_path);
	string line;
	vector<Review> reviews;

	getline(file_stream, line, IGNORE_FIRST_LINE);
	while(getline(file_stream, line, NEWLINE_DELIMITER)){

		reviews.push_back( get_info_of_one_review(line, goodreads));
	}
	return reviews;
}

pair<ID, vector<ID> > get_followings_of_one_user(string followings_info){

	vector<ID> followings_id;
	vector<string> info_items = get_parts_of_line_based_delimiter(followings_info, DELIMTER_1), followings_id_in_string;

	followings_id_in_string = get_parts_of_line_based_delimiter(info_items[F_followings], DELIMTER_2);
	for(string id_in_string : followings_id_in_string){
		followings_id.push_back(stoi(id_in_string));
	}
	return pair<ID, vector<ID> > (stoi(info_items[F_id]), followings_id);
}

map <ID, vector<ID> > InputDataProcess::extract_low_level_users_followings_from_file(string file_path){

	ifstream file_stream(file_path);
	string line;
	map <ID, vector<ID> > users_followings;
	
	getline(file_stream, line, IGNORE_FIRST_LINE);
	while(getline(file_stream, line, NEWLINE_DELIMITER)){
		users_followings.insert(get_followings_of_one_user(line));
	}
	return users_followings;
}

vector<ID> InputDataProcess::find_deep_level_user_followings(ID user_id, map <ID, vector<ID> > users_followings_id,
	vector<ID> deep_level_followings, int is_first_level)
{
	vector<ID> low_level_user_followings;

	for(ID new_id : users_followings_id[user_id]){
		
		bool is_already_exist = false;
		for(ID id : deep_level_followings){
			
			if(id == new_id){
				is_already_exist = true;
			}
		}
		if(is_already_exist == false){

			low_level_user_followings.push_back(new_id);
			deep_level_followings.push_back(new_id);
		}
	}
	for(int index = 0; index < low_level_user_followings.size(); index++){
		deep_level_followings = find_deep_level_user_followings(low_level_user_followings[index],
			users_followings_id, deep_level_followings, is_first_level + 1);
	}
	if(is_first_level == 0){

		for(int index = 0; index < deep_level_followings.size(); index++){

			if(user_id == deep_level_followings[index]){

				deep_level_followings.erase(deep_level_followings.begin() + index);
				index--;
			}
		}
	}
	return deep_level_followings;
}

vector<User*> convert_followings_ides_to_ptr(vector<ID> followings_id, GoodReads& goodreads){

	vector<User*> user_followings_ptr;

	for(int index = 0; index < followings_id.size(); index++){
		user_followings_ptr.push_back((User*)goodreads.find_special_item(FIND_USER_TYPE, followings_id[index]));
	}
	return user_followings_ptr;
}

void InputDataProcess::get_followings_of_users(string file_path, GoodReads& goodreads){

	map <ID, vector<ID> > users_followings_id;
	User* user_ptr;

	users_followings_id = extract_low_level_users_followings_from_file(file_path);
	for(auto user_followings : users_followings_id){

		user_followings.second = find_deep_level_user_followings(user_followings.first, users_followings_id);
		user_ptr = (User*)goodreads.find_special_item(FIND_USER_TYPE, user_followings.first);
		user_ptr->set_followings_series(convert_followings_ides_to_ptr(user_followings.second, goodreads));
	}
 }

vector<Book> InputDataProcess::set_reviews_ralated_to_each_book(GoodReads& goodreads){

	vector<Book> books = goodreads.get_supplement_datas().get_books();
	vector<Review> reviews = goodreads.get_supplement_datas().get_reviews();
	ID book_id, book_id_of_review;
	vector<Review*> related_reviews;

	for(int index1 = 0; index1 < books.size(); index1++){

		book_id = books[index1].get_id();
		for(int index2 = 0; index2 < reviews.size(); index2++){

			book_id_of_review = reviews[index2].get_book_ptr()->get_id();
			if(book_id == book_id_of_review){
				related_reviews.push_back((Review*)goodreads.find_special_item(FIND_REVIEW_TYPE, reviews[index2].get_id()));
			}
		}
		books[index1].set_reviews(related_reviews);
		related_reviews.resize(0);
	}
	return books;
}

void InputDataProcess::extract_input_data(GoodReads& goodreads, string directory_path){

	string file_path = directory_path + AUTHORS_FILE_NAME;

	goodreads.set_authors(read_authors_info_from_file(file_path));
	file_path = directory_path + BOOKS_FILE_NAME;
	goodreads.set_books(read_books_info_from_file(file_path, goodreads));
	file_path = directory_path + USERS_FILE_NAME;
	goodreads.set_users(read_users_info_from_file(file_path, goodreads));
	file_path = directory_path + REVIEWS_FILE_NAME;
	goodreads.set_reviews(read_reviews_info_from_file(file_path, goodreads));
	
	goodreads.set_books(set_reviews_ralated_to_each_book(goodreads));

	file_path = directory_path + FOLLOW_EDGES_FILE_NAME;
	get_followings_of_users(file_path, goodreads);
}
