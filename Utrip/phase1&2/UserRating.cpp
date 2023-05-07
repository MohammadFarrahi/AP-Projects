#include"UserRating.hpp"
#include<sstream>
#include<algorithm>
#include<iomanip>
#include"Tools.hpp"
#include"Exception.hpp"
#include"Hotel.hpp"
#include<cmath>

using namespace std;


UserRating::UserRating() : manual_weights_state(DISABLE_ORDER){
	for_each(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1,
		[this](string key_value){ this->estimated_weights[key_value] = get_random_number_in_range(FIRST_OF_RATING_VALUE_RANGE, END_OF_RATING_VALUE_RANGE); });
}

bool UserRating::set_manual_weights(map<string, double> weights){
	if(is_valid_values(weights)){
		manual_weights_of_rating_items = weights;
		return true;
	}
	return false;
}
void UserRating::set_manual_weights_state(string state_){ manual_weights_state = state_; }

string UserRating::get_manual_weights_in_text(){
	ostringstream output_stream;

	if(manual_weights_state == DISABLE_ORDER){ output_stream << "active " << DISABLE_ORDER << NEW_LINE; }
	else{
		output_stream << "active " << ACTIVE_ORDER;
		for_each(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1,
			[this, &output_stream](string key_value){
				output_stream << SPACE_CHAR << key_value;
				output_stream << SPACE_CHAR << fixed << setprecision(2);
				output_stream << (double)(((int)(this->manual_weights_of_rating_items[key_value] * 100)) / 100.0);
			});
		output_stream << SPACE_CHAR << NEW_LINE;
	}
	return output_stream.str();
}

bool UserRating::is_valid_values(map<string, double> values){
	return all_of(values.begin(), values.end(), [](pair<string, double> value){ return (1 <= value.second && value.second <= 5); });
}

bool UserRating::add_rating(Hotel* hotel, map<string, double> ratings_items){
	if(!is_valid_values(ratings_items)){
		return false;
	}
	user_ratings_to_hotels[hotel] = ratings_items;
	if(user_ratings_to_hotels.size() >= LEAST_RATINGS_TO_USE_ESTIMATED_WEIGHTS){ update_estimated_weights(); }
	return true;
}

double UserRating::get_personal_rating(Hotel* hotel){
	auto rating_it = user_ratings_to_hotels.find(hotel);
	if(rating_it != user_ratings_to_hotels.end()){ return rating_it->second[RATINGS_ITEMS[Overall_rating]]; }

	vector<double> weights_values;
	if(manual_weights_state == ACTIVE_ORDER){
		weights_values = make_vector_of_map_values(manual_weights_of_rating_items, vector<string>(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1));
		return get_weighted_average(hotel->get_average_ratings_in_special_fields(), weights_values);
	}
	if(user_ratings_to_hotels.size() >= LEAST_RATINGS_TO_USE_ESTIMATED_WEIGHTS){
		weights_values = make_vector_of_map_values(estimated_weights, vector<string>(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1));
		return get_weighted_average(hotel->get_average_ratings_in_special_fields(), weights_values);
	}
	throw insufficient_ratings();
}

string UserRating::get_estimated_weights_in_text(){
	ostringstream output_stream;

	if(user_ratings_to_hotels.size() < LEAST_RATINGS_TO_USE_ESTIMATED_WEIGHTS){ throw insufficient_ratings(); }
	else{
		for_each(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1,
			[this, &output_stream](string key_value){
				output_stream << SPACE_CHAR << key_value;
				output_stream << SPACE_CHAR << fixed << setprecision(2);
				output_stream << (double)(((int)(this->estimated_weights[key_value] * 100)) / 100.0);
			});
		output_stream << SPACE_CHAR << NEW_LINE;
	}
	return output_stream.str();
}

double UserRating::calculate_error_function(vector<double>& rating_items_values, const vector<double>& estimated_weights_values){
	return pow((get_weighted_average(vector<double>(rating_items_values.begin(), rating_items_values.end() - 1), estimated_weights_values) - rating_items_values[Overall_rating]), 2);
}

double UserRating::get_derive_of_error_function(vector<double>& rating_items_values, vector<double> estimated_weights_values, int weight_item){
	double error_function_value = calculate_error_function(rating_items_values, estimated_weights_values);
	estimated_weights_values[weight_item] += EPSILON;
	return (calculate_error_function(rating_items_values, estimated_weights_values) - error_function_value) / EPSILON;
}

vector<double> UserRating::get_deriveds_values(vector<double>& estimated_weights_values){
	vector<double> deriveds(RATING_ITEMS - 1, 0);
	vector<double> rating_items_values;

	for_each(user_ratings_to_hotels.begin(), user_ratings_to_hotels.end(),
		[&](pair<Hotel*, map<string, double> > user_rating){
			rating_items_values = make_vector_of_map_values(user_rating.second, vector<string>(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end()));
			for(int weight_item_counter = 0; weight_item_counter < RATING_ITEMS - 1; weight_item_counter++){
				deriveds[weight_item_counter] += this->get_derive_of_error_function(rating_items_values, estimated_weights_values, weight_item_counter);
			}
		}
	);
	return deriveds;
}

void UserRating::update_estimated_weights(){
	vector<double> estimated_weights_values;
	vector<double> deriveds;

	estimated_weights_values = make_vector_of_map_values(estimated_weights, vector<string>(RATINGS_ITEMS.begin(), RATINGS_ITEMS.end() - 1));
	for(int counter = 0; counter < NUM_OF_ESTIMATE_WEIGHTS; counter++){
		int derived_index = 0;

		deriveds = get_deriveds_values(estimated_weights_values);
		for_each(estimated_weights_values.begin(), estimated_weights_values.end(),
			[&](double& value){
				value = get_closest_of_value_in_range((value - STEP_SIZE * deriveds[derived_index++]), FIRST_OF_RATING_VALUE_RANGE, END_OF_RATING_VALUE_RANGE); });
	}
	for(int i = 0; i < RATING_ITEMS - 1; i++){
		estimated_weights[RATINGS_ITEMS[i]] = estimated_weights_values[i];
	}
}
