#include"MessengerNetwork.hpp"
#include<iostream>
#include<string>

using namespace std;


int main(){

	string input_command;
	MessengerNetwork messenger_network;
	while(getline(cin, input_command)){

		try{
			messenger_network.process_input_command(input_command);
		}
		catch(exception& command_exception){
			cerr << command_exception.what();
		}
	}
	messenger_network.process_exiting();
	return 0;
}
