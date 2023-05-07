#include"Exception.hpp"

using namespace std;

const char* invalid_input::what() const noexcept{ return "Not Found"; }

const char* bad_request::what() const noexcept{ return "Bad Request"; }

const char* invalid_access::what() const noexcept{ return "Permission Denied"; }

const char* lack_of_room::what() const noexcept{ return "Not Enough Room"; }

const char* lack_of_money::what() const noexcept{ return "Not Enough Credit"; }

const char* insufficient_ratings::what() const noexcept{ return "Insufficient Ratings"; }

const char* failed_task::what() const noexcept{ return "!!Operation failed. Try again!!"; }

