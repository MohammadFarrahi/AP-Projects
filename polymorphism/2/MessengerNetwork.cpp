#include"MessengerNetwork.hpp"
#include"Exception.hpp"
#include<iostream>
#include<sstream>

#define ADD_CHANNEL_ORDER "add_channel"
#define ADD_BOT_ORDER "add_bot"
#define TELL_CHANNEL_ORDER "tell"

using namespace std;


bool MessengerNetwork::is_channel_name(string name){ return (channels.find(name) != channels.end()); }

void MessengerNetwork::process_input_command(string command){

	string order, order_details;
	istringstream command_stream(command);
	command_stream >> order;
	getline(command_stream, order_details);
	if(order == ADD_CHANNEL_ORDER){
		add_channel(order_details);
	}
	else if(order == ADD_BOT_ORDER){
		process_adding_bot(order_details);
	}
	else if(order == TELL_CHANNEL_ORDER){
		process_posting_message_to_channel(order_details);
	}
}

void MessengerNetwork::add_channel(string new_channel_info){

	string channel_name = "";
	istringstream input_stream(new_channel_info);
	input_stream >> channel_name;
	if(!is_channel_name(channel_name)){

		channels.insert(pair<string, Channel*>(channel_name, new Channel(channel_name)));
		return;
	}
	throw duplicate_channel_name();
}

void MessengerNetwork::process_adding_bot(string new_bot_info){

	Bot* new_bot;
	string bot_name = "", channel_to_be_connected = "";
	istringstream input_stream(new_bot_info);
	input_stream >> bot_name;
	if(bot_name == bot_names[echo]){
		
		string dest_channel = "";
		input_stream >> channel_to_be_connected >> dest_channel;
		if(channel_to_be_connected == dest_channel){
			throw same_channel_name();
		}
		if(!is_channel_name(channel_to_be_connected) || !is_channel_name(dest_channel)){
			throw invalid_channel_name();
		}
		new_bot = new Echo(channels[dest_channel]);
		channels[channel_to_be_connected]->register_bot(new_bot);
	}
	else if(bot_name == bot_names[logger]){

		string file_name;
		input_stream >> file_name;
		new_bot = new Logger(file_name);
		for(auto channel : channels){
			channel.second->register_bot(new_bot);
		}
	}
	else if(bot_name == bot_names[fred]){

		input_stream >> channel_to_be_connected;
		if(!is_channel_name(channel_to_be_connected)){
			throw invalid_channel_name();
		}
		new_bot = new Friend(channels[channel_to_be_connected]);
		channels[channel_to_be_connected]->register_bot(new_bot);
	}
	else if(bot_name == bot_names[librarian]){

		input_stream >> channel_to_be_connected;
		if(!is_channel_name(channel_to_be_connected)){
			throw invalid_channel_name();
		}
		new_bot = new Librarian(channels[channel_to_be_connected]);
		channels[channel_to_be_connected]->register_bot(new_bot);
	}
	added_bots.push_back(new_bot);
}

void MessengerNetwork::process_exiting(){

	for(auto channel : channels){
		delete channel.second;
	}
	for(Bot* bot : added_bots){
		delete bot;
	}
}

void MessengerNetwork::process_posting_message_to_channel(string info){
	
	string channel_name, message;
	istringstream input_stream(info);
	input_stream >> channel_name;
	input_stream.ignore(1, ' ');
	getline(input_stream, message);
	if(is_channel_name(channel_name)){
		channels[channel_name]->get_new_message_and_update(message);
		return;
	}
	throw invalid_channel_name();
}
