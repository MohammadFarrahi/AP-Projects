#include<iostream>
#include"GoodReads.hpp"
#include"InputDataProcess.hpp"

#define CHAR_SIZE 1
#define SPACE ' '

enum CommandType { C_author_info, C_sorted_shelf, C_credit, C_best_book, C_best_reviewer, C_recommend_1, C_recommend_2 };

typedef int ID;

using namespace std;


int main(int argc, char* argv[]){

	ID input_id;
	string input_command;
	const vector<string> commands = {
		"show_author_info", "show_sorted_shelf", "credit", "best_book",
		"best_reviewer", "recommend_first_approach", "recommend_second_approach"
	};
	GoodReads goodreads;
	InputDataProcess process_csv_files;

	process_csv_files.extract_input_data(goodreads, argv[1]);
	while(cin >> input_command){

		if(input_command == commands[C_author_info]){

			cin >> input_id;
			cout << goodreads.get_author_info(input_id);
		}
		if(input_command == commands[C_sorted_shelf]){

			string shelf_type, genre;

			cin >> input_id;
			cin.ignore(CHAR_SIZE, SPACE);
			getline(cin, shelf_type, SPACE);
			getline(cin, genre);
			cout << goodreads.get_sorted_shelf_info(input_id, shelf_type, genre);
		}
		if(input_command == commands[C_credit]){

			cin >> input_id;
			cout << goodreads.get_user_credit(input_id) << endl;
		}
		if(input_command == commands[C_best_book]){

			cout << goodreads.get_best_book_info();	
		}
		if(input_command == commands[C_best_reviewer]){

			cout << goodreads.get_best_user_info();
		}
		if(input_command == commands[C_recommend_1]){

			cin >> input_id;
			cout << goodreads.recommend_first_approach(input_id);
		}
		if(input_command == commands[C_recommend_2]){

			cin >> input_id;
			cout << goodreads.recommend_second_approach(input_id);
		}
	}	
	return 0;
}