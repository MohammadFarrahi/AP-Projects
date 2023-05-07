#ifndef HANDLE_HPP
#define HANDLE_HPP "HANDLE_HPP"

#include "../server/server.hpp"
#include<sstream>


class UTrip;

class LoginHandler : public RequestHandler {
public:
	LoginHandler(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class RegisterHandler : public RequestHandler {
public:
	RegisterHandler(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class StarsFilterHandler : public RequestHandler {
public:
	StarsFilterHandler(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

class CreditHandler : public RequestHandler {
public:
	CreditHandler(UTrip* _utrip) : utrip(_utrip) {}
	Response* callback(Request* req);

private:
	UTrip* utrip;
};

#endif
