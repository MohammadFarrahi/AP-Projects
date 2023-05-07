#include"Exception.hpp"

#define INVALID_ID_EXCEPTION_MESSAGE "Invalid id.\n"
#define DUPLICATE_KEY_EXCEPTION_MESSAGE "Duplicate key.\n"
#define UNDEFINED_TYPE_EXCEPTION_MESSAGE "Undefined type.\n"


using namespace std;


const char* InvalidId::what() const noexcept{
	return INVALID_ID_EXCEPTION_MESSAGE;
}

const char* DuplicateKey::what() const noexcept{
	return DUPLICATE_KEY_EXCEPTION_MESSAGE;
}

const char* UndefinedType::what() const noexcept{
	return UNDEFINED_TYPE_EXCEPTION_MESSAGE;
}
