#include"UsersManager.hpp"
#include"User.hpp"
#include"Exception.hpp"
#include"Tools.hpp"
#include"Filter.hpp"
#include"TimePeriod.hpp"
#include<map>
#include<functional>
#include<algorithm>

using namespace std;


UsersManager::~UsersManager(){
	for(auto user : users){
		delete user;
	}
}

bool UsersManager::is_new_user_info(const string& username, const string& email){
	for(auto user : users){
		if(username == user->username || email == user->email){
			return false;
		}
	}
	return true;
}

void UsersManager::add_user(string username, string email, string password){
	if(!is_new_user_info(username, email)){
		throw bad_request();
	}
	current_logged_in_user = new UsersManager::User(username, email, password);
	users.push_back(current_logged_in_user);
}

void UsersManager::login_user(string email, string password){
	for(auto user : users){
		if((user->email == email) && user->password == hash<string>{}(password)){
			current_logged_in_user = user;
			return;
		}
	}
	throw bad_request();
}

void UsersManager::logout(){
	current_logged_in_user->prepare_logout();
	current_logged_in_user = NULL;
}

ProperConditionInfo UsersManager::extract_city_filter_info(string filter_info){
	string filter_argument;
	ProperConditionInfo filter_condition = DEFAULT_CONDITION_INFO;

	if(parse_word_from_first(filter_info) != ARGUMENT_SPECIFIER){
		throw bad_request();
	}
	filter_argument = parse_word_from_first(filter_info);
	if(filter_argument == FILTER_ARGUMENTS[F_A_city]){
		if(!FilterCity::is_valid_condition(filter_info)){
			throw bad_request();
		}
		filter_condition.city = filter_info;
	}
	else{
		throw bad_request();
	}
	return filter_condition;
}

ProperConditionInfo UsersManager::extract_stars_filter_info(string filter_info){
	map<string, string> extracted_conditions_info;
	ProperConditionInfo filter_condition = DEFAULT_CONDITION_INFO;

	extracted_conditions_info = extract_arguments_values(filter_info, {FILTER_ARGUMENTS[F_A_min_star], FILTER_ARGUMENTS[F_A_max_star]});
	if(!FilterStars::is_valid_condition(stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_min_star]]),
										stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_max_star]])))
	{
		throw bad_request();
	}
	filter_condition.min_stars = stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_min_star]]);
	filter_condition.max_stars = stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_max_star]]);
	return filter_condition;
}

ProperConditionInfo UsersManager::extract_price_filter_info(string filter_info){
	map<string, string> extracted_conditions_info;
	ProperConditionInfo filter_condition = DEFAULT_CONDITION_INFO;

	extracted_conditions_info = extract_arguments_values(filter_info, {FILTER_ARGUMENTS[F_A_min_price], FILTER_ARGUMENTS[F_A_max_price]});
	if(!FilterPrice::is_valid_condition(stod(extracted_conditions_info[FILTER_ARGUMENTS[F_A_min_price]]),
										stod(extracted_conditions_info[FILTER_ARGUMENTS[F_A_max_price]])))
	{
		throw bad_request();
	}
	filter_condition.min_average_price = stod(extracted_conditions_info[FILTER_ARGUMENTS[F_A_min_price]]);
	filter_condition.max_average_price = stod(extracted_conditions_info[FILTER_ARGUMENTS[F_A_max_price]]);
	return filter_condition;
}

ProperConditionInfo UsersManager::extract_rooms_filter_info(string filter_info){
	map<string, string> extracted_conditions_info;
	ProperConditionInfo filter_condition = DEFAULT_CONDITION_INFO;

	extracted_conditions_info = extract_arguments_values(filter_info, {FILTER_ARGUMENTS[F_A_type], FILTER_ARGUMENTS[F_A_quantity],
														FILTER_ARGUMENTS[F_A_check_in], FILTER_ARGUMENTS[F_A_check_out]});
	if(!FilterProperRooms::is_valid_condition(extracted_conditions_info[FILTER_ARGUMENTS[F_A_type]],
											stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_quantity]])))
	{
		throw bad_request();
	}
	filter_condition.room_type = extracted_conditions_info[FILTER_ARGUMENTS[F_A_type]];
	filter_condition.quantity = stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_quantity]]);
	filter_condition.check_in_check_out_time = TimePeriod(stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_check_in]]),
														stoi(extracted_conditions_info[FILTER_ARGUMENTS[F_A_check_out]]));
	return filter_condition;
}

void UsersManager::extract_buget_filter_info(string filter_info){
	map<string, string> extracted_conditions_info = extract_arguments_values(filter_info, {FILTER_ARGUMENTS[F_A_buget_filter_order]});
	if(!BudgetBaseFilter::is_valid_order(extracted_conditions_info[FILTER_ARGUMENTS[F_A_buget_filter_order]])){
		throw bad_request();
	}
	current_logged_in_user->user_filters[budget]->set_user_order(extracted_conditions_info[FILTER_ARGUMENTS[F_A_buget_filter_order]]);
}

void UsersManager::set_filter_for_user_based_arguments(const string& filter_info){
	vector<string> temp_filter_info(NUM_OF_FILTERS, filter_info);
	bool is_any_condition_extracted = false;
	try{
		extract_buget_filter_info(temp_filter_info[FilterType::budget]);
		is_any_condition_extracted = true;
	}
	catch(exception& e){};
	if(is_any_condition_extracted){ return; }
	try{
		current_logged_in_user->set_filter({FilterType::city, extract_city_filter_info(temp_filter_info[FilterType::city])});
		is_any_condition_extracted = true;
	}
	catch(exception& e){};
	if(is_any_condition_extracted){	return; }
	try{
		current_logged_in_user->set_filter({FilterType::stars, extract_stars_filter_info(temp_filter_info[FilterType::stars])});
		is_any_condition_extracted = true;
	}
	catch(exception& e){};
	if(is_any_condition_extracted){ return; }
	try{
		current_logged_in_user->set_filter({FilterType::price, extract_price_filter_info(temp_filter_info[FilterType::price])});
		is_any_condition_extracted = true;
	}
	catch(exception& e){};
	if(is_any_condition_extracted){ return; }
	current_logged_in_user->set_filter({FilterType::rooms, extract_rooms_filter_info(temp_filter_info[FilterType::rooms])});
}

void UsersManager::extract_user_manual_weights(string weights_info){
	map<string, string> text_weights;
	map<string, double> weights;

	try{
		text_weights = extract_arguments_values(weights_info, {ARGUMENTS[A_active]});
		if(text_weights[ARGUMENTS[A_active]] != DISABLE_ORDER){ throw bad_request(); }
		current_logged_in_user->user_rating.set_manual_weights_state(text_weights[ARGUMENTS[A_active]]);
		return;
	}
	catch(exception& e){
		text_weights = extract_arguments_values(weights_info, {ARGUMENTS[A_active], ARGUMENTS[A_rating + Location], ARGUMENTS[A_rating + Cleanliness],
								ARGUMENTS[A_rating + Staff], ARGUMENTS[A_rating + Facilities], ARGUMENTS[A_rating + Value_for_money]});
		for_each(text_weights.begin(), text_weights.end(),
				[&](pair<string, string> p){ if(p.first != ARGUMENTS[A_active]){ weights[p.first] = stod(p.second); } });
		if(text_weights[ARGUMENTS[A_active]] == ACTIVE_ORDER &&
			current_logged_in_user->user_rating.set_manual_weights(weights)){
			current_logged_in_user->user_rating.set_manual_weights_state(text_weights[ARGUMENTS[A_active]]);
			return;
		}
		throw;
	}
}
