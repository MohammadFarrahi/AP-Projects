#ifndef BOT_HPP
#define BOT_HPP "BOT_HPP"

#include<string>
#include<vector>
#include"Channel.hpp"

#define FRIEND_BOT_MESSAGE "Hello"
#define DEFAULT_MESSAGE_TO_BE_REPLIED "Hi"

#define LIBRARIAN_MESSAGE "Quiet!"
#define DEFAULT_NUMBER 5
#define ZERO 0

#define DEFAULT_MESSAGE ""

enum BotNameIndex { echo, logger, fred, librarian };

const std::vector<std::string> bot_names = {"echo", "logger", "fred", "librarian"};

class Bot {
public:
	Bot(Channel* channel_to_be_effected_ = NULL, std::string bot_message_ = DEFAULT_MESSAGE);
	virtual void react_to_new_message(std::string new_channel_message) = 0;
	void set_bot_message(std::string message_);

protected:
	Channel* channel_to_be_effected;
	std::string bot_message_for_channel;
};

class Echo : public Bot {
public:
	Echo(Channel* channel_to_be_effected_);
	void react_to_new_message(std::string new_channel_message);
};

class Logger : public Bot {
public:
	Logger(std::string file_name_);
	void react_to_new_message(std::string new_channel_message);

private:
	static std::vector<std::string> saving_file_names;
	std::string file_name_to_save_messages;

	bool is_new_file_name(std::string file_name_);
};

class Friend : public Bot {
public:
	Friend(Channel* channel_to_be_effected_, std::string message_to_be_replied_ = DEFAULT_MESSAGE_TO_BE_REPLIED,
			std::string bot_message_ = FRIEND_BOT_MESSAGE);
	void react_to_new_message(std::string new_channel_message);

private:
	std::string message_to_be_replied;
};

class Librarian : public Bot {
public:
	Librarian(Channel* channel_to_be_effected_, unsigned num_of_messages_without_reaction_ = DEFAULT_NUMBER,
				std::string bot_message_ = LIBRARIAN_MESSAGE);
	void react_to_new_message(std::string new_channel_message);

private:
	unsigned number_of_messages_without_reaction;
	unsigned message_counter;
};

#endif
