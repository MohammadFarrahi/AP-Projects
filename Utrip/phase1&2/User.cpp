#include"UsersManager.hpp"
#include"User.hpp"
#include"Exception.hpp"
#include"ReserveItem.hpp"
#include"Filter.hpp"
#include"Tools.hpp"
#include<sstream>
#include<iomanip>
#include<algorithm>

using namespace std;


UsersManager::User::User(string username_, string email_, string password_, double money_, unsigned last_reservation_id_) : 
	username(username_), email(email_), money(money_), last_reservation_id(last_reservation_id_)
{
	password = hash<string>{}(password_);
	user_filters.push_back(new FilterCity());
	user_filters.push_back(new FilterStars());
	user_filters.push_back(new FilterPrice());
	user_filters.push_back(new FilterProperRooms());
	user_filters.push_back(new BudgetBaseFilter());
}

string UsersManager::User::avtive_buget_filter(){
	if(reservations.size() >= LEAST_RESERVES_FOR_BUDGET_FILTER && !user_filters[price]->is_active()){
		if(user_filters[budget]->active_filtering()){
			return BUDGET_FILTER_MESSAGE;
		}
	}
	return EMPTY_MESSAGE;
}

void UsersManager::User::update_buget_filter(){
	vector<pair<double, double> > reservations_price_info_per_night; 
	ProperConditionInfo filter_info = DEFAULT_CONDITION_INFO;

	transform(reservations.begin(), reservations.end(), back_inserter(reservations_price_info_per_night),
			[](pair<unsigned, ReserveItem*> reservation){ return (reservation.second)->get_price_info_per_night(); });

	double weighted_average = get_weighted_average(reservations_price_info_per_night);
	filter_info.standard_deviation = get_standard_deviation(reservations_price_info_per_night, weighted_average);
	filter_info.average_user_budget = weighted_average;
	user_filters[budget]->set_proper_condition(filter_info);
}

void UsersManager::User::add_rating(Hotel* hotel, map<string, double> ratings_items){
	user_rating.add_rating(hotel, ratings_items);
}

UsersManager::User::~User(){
	for(Filter* filter : user_filters){
		delete filter;
	}
	for(auto& reservation : reservations){
		delete reservation.second;
	}
}

string UsersManager::User::get_manual_weights_in_text(){ return user_rating.get_manual_weights_in_text(); }

string UsersManager::User::get_estimated_weights_in_text(){ return user_rating.get_estimated_weights_in_text(); }

void UsersManager::User::prepare_logout(){
	disable_filters();
	user_filters[budget]->set_user_order();
	user_rating.set_manual_weights_state();
}

void UsersManager::User::set_filter(const pair<FilterType, ProperConditionInfo>& condition_info){
	user_filters[condition_info.first]->set_proper_condition(condition_info.second);
}

void UsersManager::User::disable_filters(){
	for(Filter* filter : user_filters){
		filter->disable_filtering();
	}
}

string UsersManager::User::show_recent_transactions(int count){
	ostringstream output_result;
	double sum_of_transaction_amounts = 0;
	int transaction_counter = (int)transactions.size() - 1;
	
	if(count <= 0){
		throw bad_request();
	}
	output_result << fixed << setprecision(0) << money << endl;
	count--;
	
	while(count > 0 && transaction_counter >= 0){
		sum_of_transaction_amounts += transactions[transaction_counter];
		output_result << fixed << setprecision(0) << money - sum_of_transaction_amounts << endl;
		transaction_counter--; 
		count--;
	}
	return output_result.str();
}

string UsersManager::User::add_reservation(ReserveItem* reservation){

	reservations[++last_reservation_id] = reservation;
	money -= reservation->get_reservation_cost();
	transactions.push_back((-1.0) * reservation->get_reservation_cost());
	if(reservations.size() >= LEAST_RESERVES_FOR_BUDGET_FILTER){
		update_buget_filter();
	}
	return reservation->get_booked_rooms_id_text();
}

void UsersManager::User::cancel_reservation(unsigned id){
	if(reservations.find(id) == reservations.end()){
		throw invalid_input();
	}
	double exchange = reservations[id]->cancel_reservation();
	money += exchange;
	transactions.push_back(exchange);
	delete reservations[id];
	reservations.erase(id);
	if(reservations.size() >= LEAST_RESERVES_FOR_BUDGET_FILTER){
		update_buget_filter();
	}
}

void UsersManager::User::increase_money(double amount){
	if(amount <= 0){
		throw bad_request();
	}
	transactions.push_back(amount);
	money += amount;
}

string UsersManager::User::show_reservations_info(){
	ostringstream output;

	if(reservations.size() == 0){
		return "Empty\n";
	}
	for(auto reservation_it = reservations.rbegin(); reservation_it != reservations.rend(); reservation_it++){
		output << reservation_it->second->get_reservation_info_text(reservation_it->first) << endl;
	}
	return output.str();
}

vector<Hotel*> UsersManager::User::apply_filters(vector<Hotel*> hotels, string& output_message){
	output_message = avtive_buget_filter();

	for(auto filter : user_filters){
		if(filter->is_active()){
			hotels = filter->filter_objects(hotels);
		}
	}

	return hotels;
}

double UsersManager::User::get_personal_rating(Hotel* hotel){
	return user_rating.get_personal_rating(hotel);
}
