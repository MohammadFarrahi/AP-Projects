#include"Filter.hpp"
#include"Hotel.hpp"
#include"Exception.hpp"
#include<cmath>
#include<algorithm>

using namespace std;


void Filter::disable_filtering(){ state = DISABLE; }

bool Filter::is_active(){ return state; }

bool Filter::active_filtering(){ state = ACTIVE; return state; }

void Filter::set_user_order(string activation_order) {}

vector<Hotel*> FilterCity::filter_objects(vector<Hotel*> objects){
	vector<Hotel*> proper_hotels;

	for(Hotel* hotel : objects){
		if(hotel->is_in_this_city(proper_city)){
			proper_hotels.push_back(hotel);
		}
	}
	return proper_hotels;
}

void FilterCity::disable_filtering(){
	proper_city = DEFAULT_CONDITION_INFO.city;
	Filter::disable_filtering();
}

void FilterCity::set_proper_condition(const ProperConditionInfo& condition_info){
	state = ACTIVE;
	proper_city = condition_info.city;
}

vector<Hotel*> FilterStars::filter_objects(vector<Hotel*> objects){
	vector<Hotel*> proper_hotels;
	
	for(Hotel* hotel : objects){
		if(min_stars <= hotel->get_stars() && hotel->get_stars() <= max_stars){
			proper_hotels.push_back(hotel);
		}
	}
	return proper_hotels;
}

void FilterStars::disable_filtering(){
	min_stars = DEFAULT_CONDITION_INFO.min_stars;
	max_stars = DEFAULT_CONDITION_INFO.max_stars;
	Filter::disable_filtering();
}

void FilterStars::set_proper_condition(const ProperConditionInfo& condition_info){
	if(!is_valid_condition(condition_info.min_stars, condition_info.max_stars)){
		throw failed_task();
	}
	state = ACTIVE;
	min_stars = condition_info.min_stars;
	max_stars = condition_info.max_stars;
}

vector<Hotel*> FilterPrice::filter_objects(vector<Hotel*> objects){
	vector<Hotel*> proper_hotels;

	for(Hotel* hotel : objects){
		if(min_average_price <= hotel->get_average_room_price() &&  hotel->get_average_room_price() <= max_average_price){
			proper_hotels.push_back(hotel);
		}
	}
	return proper_hotels;
}

void FilterPrice::disable_filtering(){
	min_average_price = DEFAULT_CONDITION_INFO.min_average_price;
	max_average_price = DEFAULT_CONDITION_INFO.max_average_price;
	Filter::disable_filtering();
}

void FilterPrice::set_proper_condition(const ProperConditionInfo& condition_info){
	state = ACTIVE;
	min_average_price = condition_info.min_average_price;
	max_average_price = condition_info.max_average_price;
}

vector<Hotel*> FilterProperRooms::filter_objects(vector<Hotel*> objects){
	vector<Hotel*> proper_hotels;

	for(Hotel* hotel : objects){
		if(hotel->has_enough_rooms(room_type, quantity, check_in_check_out_time)){
			proper_hotels.push_back(hotel);
		}
	}
	return proper_hotels;
}

void FilterProperRooms::disable_filtering(){
	quantity = DEFAULT_CONDITION_INFO.quantity;
	room_type = DEFAULT_CONDITION_INFO.room_type;
	check_in_check_out_time = DEFAULT_CONDITION_INFO.check_in_check_out_time;
	Filter::disable_filtering();
}

void FilterProperRooms::set_proper_condition(const ProperConditionInfo& condition_info){
	state = ACTIVE;
	quantity = condition_info.quantity;
	room_type = condition_info.room_type;
	check_in_check_out_time = condition_info.check_in_check_out_time;
}

bool FilterStars::is_valid_condition(int min_stars, int max_stars){
	return (1 <= min_stars && max_stars <= 5 && min_stars <= max_stars);
}

bool FilterPrice::is_valid_condition(double min_average_price, double max_average_price){
	return (min_average_price >= 0 && max_average_price >= min_average_price);
}

bool FilterCity::is_valid_condition(string city){
	return (city != "" && city[city.length() - 1] != ' ');
}

bool FilterProperRooms::is_valid_condition(string room_type, int quantity){
	return (Hotel::is_valid_room_type(room_type) && (quantity > 0));
}

vector<Hotel*> BudgetBaseFilter::filter_objects(vector<Hotel*> objects){
	vector<Hotel*> proper_hotels;

	copy_if(objects.begin(), objects.end(), back_inserter(proper_hotels),
		[&](Hotel* hotel){ return (fabs(hotel->get_average_room_price() - average_user_budget) <= 2 * standard_deviation); });
	return proper_hotels;
}

void BudgetBaseFilter::disable_filtering(){}

void BudgetBaseFilter::set_proper_condition(const ProperConditionInfo& condition_info){
	standard_deviation = condition_info.standard_deviation;
	average_user_budget = condition_info.average_user_budget;
}

bool BudgetBaseFilter::active_filtering(){
	if(user_order == ACTIVE_ORDER){ state = ACTIVE; }
	else { state = DISABLE; }
	return state;
}

void BudgetBaseFilter::set_user_order(string activation_order){ user_order = activation_order; }

bool BudgetBaseFilter::is_valid_order(string order){
	return (order == ACTIVE_ORDER || order == DISABLE_ORDER);
}
