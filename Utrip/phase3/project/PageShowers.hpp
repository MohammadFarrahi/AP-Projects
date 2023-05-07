#ifndef SHOW_PAGE_HPP
#define SHOW_PAGE_HPP "SHOW_PAGE_HPP"

#include "../server/server.hpp"
#include<sstream>


class UTrip;
class Hotel;

class SignupForm : public RequestHandler {
public:
	SignupForm(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class LoginForm : public RequestHandler {
public:
	LoginForm(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class HomePage : public RequestHandler {
public:
	HomePage(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;

	void fill_body_of_home_page(std::ostream& body);
};

class LogoutPage : public RequestHandler {
public:
	LogoutPage(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class CreditPage : public RequestHandler {
public:
	CreditPage(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;

	void fill_body_of_credit_page(std::ostream& body);
};

class HotelPage : public RequestHandler {
public:
	HotelPage(UTrip* _utrip) : utrip(_utrip), hotel(NULL) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
	Hotel* hotel;

	void fill_body_of_hotel_page(std::ostream& body);
};

#endif
