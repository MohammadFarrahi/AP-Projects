#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include<map>
#include<utility>
#include"Const.hpp"
#include"UserRating.hpp"


struct ProperConditionInfo;
class ReserveItem;
class Filter;
class Hotel;
class UsersManager;

class UsersManager::User {
public:
	User(std::string username_, std::string email_, std::string password_, double money_ = 0, unsigned last_reservation_id = 0);
	~User();
	std::string get_username() { return username; }
	double get_money() { return money; }
	std::string add_reservation(ReserveItem* reservation);
	void cancel_reservation(unsigned id);
	std::string show_reservations_info();
	void increase_money(double amount);
	std::string show_recent_transactions(int count);
	std::vector<Hotel*> apply_filters(std::vector<Hotel*> hotels, std::string& output_message);
	void set_filter(const std::pair<FilterType, ProperConditionInfo>& condition_info);
	void disable_filters();
	void prepare_logout();
	std::string get_manual_weights_in_text();
	std::string get_estimated_weights_in_text();
	void add_rating(Hotel* hotel, std::map<std::string, double> ratings_items);
	double get_personal_rating(Hotel* hotel);

private:
	UserRating user_rating;
	std::string username;
	std::string email;
	size_t password;
	double money;
	std::vector<double> transactions;
	unsigned last_reservation_id;
	std::map<unsigned, ReserveItem*> reservations;
	std::vector<Filter*> user_filters;

	std::string avtive_buget_filter();
	void update_buget_filter();

	friend class UsersManager;
};

#endif
