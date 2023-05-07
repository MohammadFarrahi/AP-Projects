#include<iostream>
#include<string>
#include"Const.hpp"
#include"UTrip.hpp"

using namespace std;


int main(int argc, char* argv[]){
	UTrip utrip;
	string request;

	utrip.load_data(argv[HOTEL_DATA_FILE_PATH_COMMAND_INDEX], argv[RATING_DATA_FILE_PATH_COMMAND_INDEX]);
	while(getline(cin, request)){
		utrip.process_request(request);
		cout << utrip.get_output_message();
	}
	return 0;
}
