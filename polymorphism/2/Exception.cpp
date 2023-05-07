#include"Exception.hpp"

#define SAME_CHANNEL_NAME_EXCEPTION "Source and destination cannot be the same channel\n"
#define DUPLICATE_CHANNEL_NAME_EXCEPTION "Channel already exists\n"
#define INVALID_CHANNEL_NAME_EXCEPTION "Channel does not exist\n"
#define DUPLICATE_FILE_NAME_EXCEPTION "This filename has already existed.Another file created with name : "

using namespace std;


const char* duplicate_channel_name::what() const noexcept{
	return DUPLICATE_CHANNEL_NAME_EXCEPTION;
}

const char* invalid_channel_name::what() const noexcept{
	return INVALID_CHANNEL_NAME_EXCEPTION;
}

const char* same_channel_name::what() const noexcept{
	return SAME_CHANNEL_NAME_EXCEPTION;
}

const char* duplicate_filename::what() const noexcept{
	return DUPLICATE_FILE_NAME_EXCEPTION;
}
