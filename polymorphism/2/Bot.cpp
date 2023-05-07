#include"Bot.hpp"
#include"Exception.hpp"
#include<iostream>
#include<fstream>

using namespace std;


Bot::Bot(Channel* channel_to_be_effected_, string bot_message_)
			: channel_to_be_effected(channel_to_be_effected_), bot_message_for_channel(bot_message_) {}

void Bot::set_bot_message(string message_){ bot_message_for_channel = message_; }

Echo::Echo(Channel* channel_to_be_effected_) : Bot(channel_to_be_effected_) {}

void Echo::react_to_new_message(string new_channel_message){
	channel_to_be_effected->get_new_message_and_update(new_channel_message);	
}

vector<string> Logger::saving_file_names;

bool Logger::is_new_file_name(string file_name_){

	for(string file_name : saving_file_names){

		if(file_name_ == file_name){
			return false;
		}
	}
	return true;
}

Logger::Logger(string file_name_){
	
	if(!is_new_file_name(file_name_)){

		file_name_ += to_string(saving_file_names.size());
		cerr << duplicate_filename().what() << file_name_ << endl;
	}
	file_name_to_save_messages = file_name_;
	saving_file_names.push_back(file_name_);
}

void Logger::react_to_new_message(string new_channel_message){

	ofstream output_file_stream;
	output_file_stream.open(file_name_to_save_messages, ios_base::app);
	output_file_stream << new_channel_message.c_str() << endl;
}

Friend::Friend(Channel* channel_to_be_effected_, string message_to_be_replied_, string bot_message_)
			: Bot(channel_to_be_effected_, bot_message_), message_to_be_replied(message_to_be_replied_) {}

void Friend::react_to_new_message(string  new_channel_message){

	if(new_channel_message == message_to_be_replied){
		channel_to_be_effected->get_new_message_and_update(bot_message_for_channel);
	}
}

Librarian::Librarian(Channel* channel_to_be_effected_, unsigned num_of_messages_without_reaction_,
					string bot_message_) : Bot(channel_to_be_effected_, bot_message_), message_counter(ZERO),
					number_of_messages_without_reaction(num_of_messages_without_reaction_) {}

void Librarian::react_to_new_message(string new_channel_message){

	message_counter++;
	if(message_counter >= number_of_messages_without_reaction){

		message_counter = ZERO;
		channel_to_be_effected->get_new_message_and_update(bot_message_for_channel);
	}
}
