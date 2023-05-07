#ifndef DATA_HPP
#define DATA_HPP "DATA_HPP"

#include<string>
#include<vector>
#include<map>
#include"Date.hpp"
#include"Author.hpp"
#include"SupplementData.hpp"
#include"User.hpp"
#include"Book.hpp"
#include"Review.hpp"
#include"GoodReads.hpp"

enum AuthorItems { A_id, A_name, A_gender, A_member_since, A_year_of_birth, A_place_of_birth, A_genres };
enum BookItems { B_id, B_title, B_author_id, B_genre };
enum UserItems { U_id, U_name, U_place_of_birth, U_member_since, U_favorie_authors, U_favorite_genres, U_shelfs };
enum ReviewItems { R_id, R_book_id, R_reviewer, R_rating, R_date, R_number_of_likes };
enum FollowEdgesItems { F_id, F_followings, F_followers };

class InputDataProcess {
public:
	void extract_input_data(GoodReads& goodreads, std::string directory_path);

private:
	std::vector<Author> read_authors_info_from_file(std::string file_path);
	std::vector<Book> read_books_info_from_file(std::string file_path, GoodReads& goodreads);
	std::vector<User> read_users_info_from_file(std::string file_path, GoodReads& goodreads);
	std::vector<Review> read_reviews_info_from_file(std::string file_path, GoodReads& goodreads);
	std::vector<Book> set_reviews_ralated_to_each_book(GoodReads& goodreads);
	std::map <ID, std::vector<ID> > extract_low_level_users_followings_from_file(std::string file_path);
	std::vector<ID> find_deep_level_user_followings(ID user_id, std::map <ID, std::vector<ID> > users_followings_id,
	std::vector<ID> deep_level_followings = {}, int is_first_level = 0);
	void get_followings_of_users(std::string file_path, GoodReads& goodreads);
};

std::pair<ID, std::vector<ID> > get_followings_of_one_user(std::string followings_info);
std::vector<User*> convert_followings_ides_to_ptr(std::vector<ID> user_followings_id, GoodReads& goodreads);
std::vector<std::string> get_parts_of_line_based_delimiter(std::string line, char delimiter);
std::vector<std::string> get_genres(std::string genres_info);
Author get_info_of_one_author(std::string author_info);
Book get_info_of_one_book(std::string book_info, GoodReads& goodreads);
std::vector<Book*> convert_books_ides_to_ptr(std::string shelf_info, GoodReads& goodreads);
std::vector<Author*> convert_authors_ides_to_ptr(std::string authors_id, GoodReads& goodreads);
User get_info_of_one_user(std::string user_info, GoodReads& goodreads);
Review get_info_of_one_review(std::string review_info, GoodReads& goodreads);

#endif