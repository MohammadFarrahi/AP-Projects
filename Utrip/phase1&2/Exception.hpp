#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP "EXCEPTION_HPP"

#include<stdexcept>


class invalid_input : public std::exception {
public:
	const char* what() const noexcept;
};

class bad_request : public std::exception {
public:
	const char* what() const noexcept;
};

class invalid_access : public std::exception {
public:
	const char* what() const noexcept;
};

class lack_of_room : public std::exception {
public:
	const char* what() const noexcept;
};

class lack_of_money : public std::exception {
public:
	const char* what() const noexcept;
};

class insufficient_ratings : public std::exception {
public:
	const char* what() const noexcept;
};

#endif
