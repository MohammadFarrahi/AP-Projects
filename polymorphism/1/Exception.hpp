#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP "EXCEPTION_HPP"

#include<stdexcept>


class InvalidId : public std::exception {
public:
	const char* what() const noexcept;
};

class DuplicateKey : public std::exception {
public:
	const char* what() const noexcept;
};

class UndefinedType : public std::exception {
public:
	const char* what() const noexcept;
};

#endif
