#include"UTrip.hpp"
#include"TimePeriod.hpp"
#include"Exception.hpp"
#include"Tools.hpp"
#include"User.hpp"
#include<algorithm>

using namespace std;


UTrip::~UTrip(){
	for(auto hotel : hotels){
		delete hotel;
	}
}

string UTrip::get_output_message(){
	return output_message;
}

void UTrip::load_data(string hotel_data_file_path, string ratings_data_file_path){
	hotels = data_reader.extract_hotels_data(hotel_data_file_path);
	hotels = data_reader.extract_ratings_data(hotels, ratings_data_file_path);
	hotel_arrange.default_sort(hotels);
}

Hotel* UTrip::find_hotel_by_id(string id){
	if(id == EMPTY){
		throw bad_request();
	}
	for(auto hotel : hotels){
		if(hotel->get_id() == id){
			return hotel;
		}
	}
	throw invalid_input();
}

bool UTrip::has_user_logged_in(){
	return users_manager.current_logged_in_user != NULL;
}

void UTrip::process_request(string input_request){
	string type_of_request = parse_word_from_first(input_request);
	output_message = EMPTY;

	try{
		if(input_request == EMPTY){
			throw bad_request();
		}
		if(type_of_request == POST_TYPE_REQUSET){
			process_post_type_requests(input_request);
		}
		else if(type_of_request == GET_TYPE_REQUEST){
			if(!has_user_logged_in()){
				throw invalid_access();
			}
			process_get_type_requests(input_request);
		}
		else if(type_of_request == DELETE_TYPE_REQUEST){
			if(!has_user_logged_in()){
				throw invalid_access();
			}
			process_delete_type_requests(input_request);
		}
		else{
			throw bad_request();
		}
	}
	catch(exception& e){
		output_message = e.what();
		output_message += NEW_LINE;
	}
}

void UTrip::process_delete_type_requests(string input_request){
	string request = parse_word_from_first(input_request);

	if(request == REQUESTS[R_filters]){
		if(input_request != EMPTY){
			throw bad_request();
		}
		users_manager.current_logged_in_user->disable_filters();
	}
	else if(request == REQUESTS[R_reserves]){
		users_manager.current_logged_in_user->cancel_reservation(stoi(extract_arguments_values(input_request, {ARGUMENTS[A_id]})[ARGUMENTS[A_id]]));
	}
	else{
		throw invalid_input();
	}
	output_message = DEFAULT_OUTPUT_MESSAGE;
}

void UTrip::get_general_hotels_info(){
	vector<Hotel*> proper_hotels = users_manager.current_logged_in_user->apply_filters(hotels, output_message);
	if(proper_hotels.size() == 0){
		output_message += "Empty\n";
	}
	hotel_arrange.sort_list(proper_hotels);
	for_each(proper_hotels.begin(), proper_hotels.end(), [this](Hotel* h){ this->output_message += h->show_general_hotel_info_text(); });
}

void UTrip::get_hotel_info(string arguments_info){
	if(arguments_info == EMPTY){
		get_general_hotels_info();
		return;
	}
	output_message = find_hotel_by_id(extract_arguments_values(arguments_info, {ARGUMENTS[A_id]})[ARGUMENTS[A_id]])->show_total_hotel_info_text();
}

void UTrip::process_get_type_requests(string input_request){
	string request = parse_word_from_first(input_request);
	map<string, string> arguments_values;
	
	if(request == REQUESTS[R_wallet]){
		arguments_values = extract_arguments_values(input_request, {ARGUMENTS[A_count]});
		output_message = users_manager.current_logged_in_user->show_recent_transactions(stoi(arguments_values[ARGUMENTS[A_count]]));
	}
	else if(request == REQUESTS[R_hotels]){
		get_hotel_info(input_request);
	}
	else if(request == REQUESTS[R_reserves]){
		if(input_request != EMPTY){
			throw bad_request();
		}
		output_message = users_manager.current_logged_in_user->show_reservations_info();
	}
	else if(request == REQUESTS[R_comments]){
		output_message = find_hotel_by_id(extract_arguments_values(input_request, {ARGUMENTS[A_hotel]})[ARGUMENTS[A_hotel]])->show_users_comments_text();
	}
	else if(request == REQUESTS[R_ratings]){
		output_message = find_hotel_by_id(extract_arguments_values(input_request, {ARGUMENTS[A_hotel]})[ARGUMENTS[A_hotel]])->show_average_users_rating_text();
	}
	else if(request == REQUESTS[R_manual_weights]){
		if(input_request != EMPTY){
			throw bad_request();
		}
		output_message = users_manager.current_logged_in_user->get_manual_weights_in_text();
	}
	else if(request == REQUESTS[R_estimated_weights]){
		if(input_request != EMPTY){
			throw bad_request();
		}
		output_message = users_manager.current_logged_in_user->get_estimated_weights_in_text();
	}
	else{
		throw invalid_input();
	}
}

void UTrip::reserve_rooms_for_user(const string& hotel_id, const string& room_type, int quantity, TimePeriod length_of_staying){
	auto hotel = find_hotel_by_id(hotel_id);
	output_message = users_manager.current_logged_in_user->add_reservation(hotel->make_reservation(room_type, quantity, length_of_staying,
																		users_manager.current_logged_in_user->get_money())) + NEW_LINE;
}

void UTrip::add_new_user_rating(map<string, string> ratings_info){
	map<string, double> ratings_values;
	
		for_each(ratings_info.begin(), ratings_info.end(),
			[&](pair<string, string> p){ if(p.first != ARGUMENTS[A_hotel]){ ratings_values[p.first] = stod(p.second);} });
	if(UserRating::is_valid_values(ratings_values)){
		users_manager.current_logged_in_user->add_rating(find_hotel_by_id(ratings_info[ARGUMENTS[A_hotel]]), ratings_values);
	}
	else{ throw bad_request(); }
}

void UTrip::process_post_type_requests_for_logged_in_users(string request, string arguments_info){
	map<string, string> arguments_values;
	
	if(request == REQUESTS[R_logout]){
		if(arguments_info != EMPTY){
			throw bad_request();
		}
		users_manager.logout();
		hotel_arrange.reset_arrange_order();
	}
	else if(request == REQUESTS[R_wallet]){
		arguments_values = extract_arguments_values(arguments_info, {ARGUMENTS[A_amount]});
		users_manager.current_logged_in_user->increase_money(stod(arguments_values[ARGUMENTS[A_amount]]));
	}
	else if(request == REQUESTS[R_filters]){
		users_manager.set_filter_for_user_based_arguments(arguments_info);
	}
	else if(request == REQUESTS[R_reserves]){
		arguments_values = extract_arguments_values(arguments_info, {ARGUMENTS[A_hotel], ARGUMENTS[A_type],
								ARGUMENTS[A_check_in], ARGUMENTS[A_quantity], ARGUMENTS[A_check_out]});
		reserve_rooms_for_user(arguments_values[ARGUMENTS[A_hotel]], arguments_values[ARGUMENTS[A_type]], stoi(arguments_values[ARGUMENTS[A_quantity]]),
						TimePeriod(stoi(arguments_values[ARGUMENTS[A_check_in]]), stoi(arguments_values[ARGUMENTS[A_check_out]])));
		return;
	}
	else if(request == REQUESTS[R_comments]){
		arguments_values = extract_arguments_values(arguments_info, {ARGUMENTS[A_hotel], ARGUMENTS[A_comment]});
		find_hotel_by_id(arguments_values[ARGUMENTS[A_hotel]])->add_user_comment(users_manager.current_logged_in_user->get_username(), arguments_values[ARGUMENTS[A_comment]]);
	}
	else if(request == REQUESTS[R_ratings]){
		vector<string> arguments = {ARGUMENTS[A_hotel], ARGUMENTS[A_rating + Location], ARGUMENTS[A_rating + Cleanliness],
				ARGUMENTS[A_rating + Staff], ARGUMENTS[A_rating + Facilities], ARGUMENTS[A_rating + Overall_rating], ARGUMENTS[A_rating + Value_for_money]};
		arguments_values = extract_arguments_values(arguments_info, arguments);

		add_new_user_rating(arguments_values);
	}
	else if(request == REQUESTS[R_budget_filter]){
		users_manager.set_filter_for_user_based_arguments(arguments_info);
	}
	else if(request == REQUESTS[R_sort]){
		arguments_values = extract_arguments_values(arguments_info, {ARGUMENTS[A_property], ARGUMENTS[A_order]});
		hotel_arrange.set_hotel_arrange_property(arguments_values[ARGUMENTS[A_property]], arguments_values[ARGUMENTS[A_order]]);
	}
	else if(request == REQUESTS[R_manual_weights]){
		users_manager.extract_user_manual_weights(arguments_info);
	}
	else if(request == REQUESTS[R_signup] || request == REQUESTS[R_login]){
		throw bad_request();
	}
	else{
		throw invalid_input();
	}
	output_message = DEFAULT_OUTPUT_MESSAGE;
}

void UTrip::process_post_type_requests(string input_request){
	string request = parse_word_from_first(input_request);
	map<string, string> arguments_values;
	
	if(has_user_logged_in()){
		process_post_type_requests_for_logged_in_users(request, input_request);
	}
	else{
		if(request == REQUESTS[R_signup]){
			arguments_values = extract_arguments_values(input_request, {ARGUMENTS[A_username], ARGUMENTS[A_password], ARGUMENTS[A_email]});
			users_manager.add_user(arguments_values[ARGUMENTS[A_username]], arguments_values[ARGUMENTS[A_email]],
									arguments_values[ARGUMENTS[A_password]]);
		}
		else if(request == REQUESTS[R_login]){
			arguments_values = extract_arguments_values(input_request, {ARGUMENTS[A_password], ARGUMENTS[A_email]});
			users_manager.login_user(arguments_values[ARGUMENTS[A_email]], arguments_values[ARGUMENTS[A_password]]);
		}
		else{
			throw invalid_access();
		}
		hotel_arrange.set_logged_in_user(users_manager.current_logged_in_user);
		output_message = DEFAULT_OUTPUT_MESSAGE;
	}
}
