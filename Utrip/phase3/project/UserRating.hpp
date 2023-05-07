#ifndef RATING_HPP
#define RATING_HPP "RATING_HPP"

#include"Const.hpp"
#include"UsersManager.hpp"
#include<map>


class Hotel;

class UserRating {
public:
	static bool is_valid_values(std::map<std::string, double> values);
	bool set_manual_weights(std::map<std::string, double> weights);
	void set_manual_weights_state(std::string state_ = DISABLE_ORDER);

private:
	UserRating();
	std::string get_manual_weights_in_text();
	bool add_rating(Hotel* hotel, std::map<std::string, double> ratings_items);
	double get_personal_rating(Hotel* hotel);
	std::string get_estimated_weights_in_text();

	std::map<std::string, double> manual_weights_of_rating_items;
	std::string manual_weights_state;
	std::map<Hotel*, std::map<std::string, double> > user_ratings_to_hotels;
	std::map<std::string, double> estimated_weights;

	double calculate_error_function(std::vector<double>& rating_items_values, const std::vector<double>& estimated_weights_values);
	double get_derive_of_error_function(std::vector<double>& rating_items_values, std::vector<double> estimated_weights_values, int weight_item);
	std::vector<double> get_deriveds_values(std::vector<double>& estimated_weights_values);
	void update_estimated_weights();

	friend class UsersManager::User;
};

#endif