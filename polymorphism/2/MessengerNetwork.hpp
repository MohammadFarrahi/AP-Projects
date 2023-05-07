#ifndef M_NETWORK_HPP
#define M_NETWORK_HPP "M_NETWORK_HPP"

#include<vector>
#include<map>
#include<string>
#include"Channel.hpp"
#include"Bot.hpp"

class MessengerNetwork {
public:
	void process_input_command(std::string command);
	void process_exiting();

private:
	std::map<std::string, Channel*> channels;
	std::vector<Bot*> added_bots;

	void add_channel(std::string new_channel_info);
	void process_adding_bot(std::string new_bot_info);
	void process_posting_message_to_channel(std::string info);
	bool is_channel_name(std::string name);
};

#endif
