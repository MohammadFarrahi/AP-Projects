#ifndef CHANNEL_HPP
#define CHANNEL_HPP "CHANNEL_HPP"

#include<string>
#include<vector>


class Bot;

class Channel {
public:
	Channel(std::string name_);
	bool is_channel_name(std::string unknown_name);
	void register_bot(Bot* new_subscriber);
	void get_new_message_and_update(std::string new_message);

private:
	std::string name;
	std::string last_posted_message;
	std::vector<Bot*> subscribers;

	void notify_subscribers();
};

#endif
