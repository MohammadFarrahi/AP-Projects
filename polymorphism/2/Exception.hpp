#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP "EXCEPTION_HPP"

#include<stdexcept>


class duplicate_channel_name : public std::exception {
public:
	const char* what() const noexcept;
};

class invalid_channel_name : public std::exception {
public:
	const char* what() const noexcept;
};

class same_channel_name : public std::exception {
public:
	const char* what() const noexcept;
};

class duplicate_filename : public std::exception {
public:
	const char* what() const noexcept;
};

#endif
