#include"UTrip.hpp"
#include"TimePeriod.hpp"
#include"Exception.hpp"
#include"Tools.hpp"
#include"User.hpp"
#include<algorithm>
#include<sstream>

using namespace std;


UTrip::~UTrip(){
	for(auto hotel : hotels){
		delete hotel;
	}
}

void UTrip::increase_user_credit(double amount){
	users_manager.current_online_user->increase_money(amount);
	result_meesage = SUCCESSFUL_OPERATION;
}

double UTrip::get_user_credit(){ return users_manager.current_online_user->get_money(); }

void UTrip::offline_requset_owner(){
	users_manager.current_online_user = NULL;
}

string UTrip::get_result_message(){
	string temp_string = result_meesage;
	result_meesage = EMPTY;
	return temp_string;
}

void UTrip::detect_request_owner(std::string session_id){
	users_manager.detect_online_user(session_id);
}

string UTrip::get_user_name(){ return users_manager.current_online_user->get_username(); }

void UTrip::set_stars_filter_condition_info(ProperConditionInfo filter_condition_info){
	users_manager.current_online_user->set_filter({FilterType::stars, filter_condition_info});

	ostringstream result_stream;
	result_stream << "Filter Applied. Hotels shown below has minimum " << filter_condition_info.min_stars
	<< " and maximum " << filter_condition_info.max_stars << " star rating";
	result_meesage = result_stream.str();
}

void UTrip::set_result_message(std::string message){ result_meesage = message; }

void UTrip::logout_user(string session_id){ users_manager.logout_user(session_id); }

bool UTrip::has_user_logged_in(string session_id){ return users_manager.has_user_logged_in(session_id); }

string UTrip::signup_new_user(std::string username, std::string password, std::string R_password, std::string email){
	if(password != R_password){ throw failed_task(); }
	return users_manager.add_user(username, email, password);
}

string UTrip::login_user(string email, string password){
	return users_manager.login_user(email, password);
}

void UTrip::load_data(string hotel_data_file_path, string ratings_data_file_path){
	hotels = data_reader.extract_hotels_data(hotel_data_file_path);
	hotels = data_reader.extract_ratings_data(hotels, ratings_data_file_path);
	hotel_arrange.default_sort(hotels);
}

Hotel* UTrip::find_hotel_by_id(string id){
	for(auto hotel : hotels){
		if(hotel->get_id() == id){
			return hotel;
		}
	}
}

vector<Hotel*> UTrip::get_hotels_to_be_showed_for_user(){
	vector<Hotel*> proper_hotels = users_manager.current_online_user->apply_filters(hotels);
	hotel_arrange.sort_list(proper_hotels);
	return proper_hotels;
}


void UTrip::reserve_rooms_for_user(const string& hotel_id, const string& room_type, int quantity, TimePeriod length_of_staying){
	auto hotel = find_hotel_by_id(hotel_id);
	result_meesage = users_manager.current_online_user->add_reservation(hotel->make_reservation(room_type, quantity, length_of_staying,
																		users_manager.current_online_user->get_money())) + NEW_LINE;
}

void UTrip::add_new_user_rating(map<string, string> ratings_info){
	map<string, double> ratings_values;
	
		for_each(ratings_info.begin(), ratings_info.end(),
			[&](pair<string, string> p){ if(p.first != ARGUMENTS[A_hotel]){ ratings_values[p.first] = stod(p.second);} });
	if(UserRating::is_valid_values(ratings_values)){
		users_manager.current_online_user->add_rating(find_hotel_by_id(ratings_info[ARGUMENTS[A_hotel]]), ratings_values);
	}
	else{ throw bad_request(); }
}
