#include"Channel.hpp"
#include"Bot.hpp"

using namespace std;


Channel::Channel(string name_) : name(name_) {}

bool Channel::is_channel_name(string unknown_name){ return (name == unknown_name); }

void Channel::register_bot(Bot* new_subscriber){
	subscribers.push_back(new_subscriber);
}

void Channel::get_new_message_and_update(string new_message){

	last_posted_message = new_message;
	notify_subscribers();
}

void Channel::notify_subscribers(){

	for(Bot* bot : subscribers){
		bot->react_to_new_message(last_posted_message);
	}
}
