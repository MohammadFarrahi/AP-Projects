#include"Handlers.hpp"
#include"UTrip.hpp"
#include"Const.hpp"
#include"Exception.hpp"
#include"Filter.hpp"

using namespace std;


Response* RegisterHandler::callback(Request* req){
	try{
		string session_id = utrip->signup_new_user(req->getBodyParam(ARGUMENTS[A_username]), req->getBodyParam(ARGUMENTS[A_password]),
									req->getBodyParam(ARGUMENTS[A_R_password]), req->getBodyParam(ARGUMENTS[A_email]));
		Response* res = Response::redirect("/home");
		res->setSessionId(session_id);
		return res;
	}
	catch(exception& e){
		utrip->set_result_message(e.what());
		return Response::redirect("/signup");
	}
}

Response* LoginHandler::callback(Request* req){
	try{
		string session_id = utrip->login_user(req->getBodyParam(ARGUMENTS[A_email]), req->getBodyParam(ARGUMENTS[A_password]));
		Response* res = Response::redirect("/home");
		res->setSessionId(session_id);
		return res;
	}
	catch(exception& e){
		utrip->set_result_message(e.what());
		return Response::redirect("/login");
	}
}

Response* StarsFilterHandler::callback(Request* req){
	utrip->detect_request_owner(req->getSessionId());
	ProperConditionInfo filter_condition_info = DEFAULT_CONDITION_INFO;
	
	if(req->getBodyParam(FILTER_ARGUMENTS[F_A_min_star]) == EMPTY || req->getBodyParam(FILTER_ARGUMENTS[F_A_max_star]) == EMPTY){
		utrip->offline_requset_owner();
		return Response::redirect("/home");
	}
	filter_condition_info.min_stars = stoi(req->getBodyParam(FILTER_ARGUMENTS[F_A_min_star]));
	filter_condition_info.max_stars = stoi(req->getBodyParam(FILTER_ARGUMENTS[F_A_max_star]));
	try{
		utrip->set_stars_filter_condition_info(filter_condition_info);
	}
	catch(exception& e){
		utrip->set_result_message(e.what());
	}
	utrip->offline_requset_owner();
	return Response::redirect("/home");
}

Response* CreditHandler::callback(Request* req){
	utrip->detect_request_owner(req->getSessionId());
	if(req->getBodyParam(ARGUMENTS[A_amount]) == EMPTY){
		utrip->offline_requset_owner();
		return Response::redirect("/credit");
	}
	try{
		utrip->increase_user_credit(stod(req->getBodyParam(ARGUMENTS[A_amount])));
	}
	catch(exception& e){
		utrip->set_result_message(e.what());
	}
	utrip->offline_requset_owner();
	return Response::redirect("/credit");
}
