#ifndef UTRIP_HPP
#define UTRIP_HPP "UTRIP_HPP"

#include"Hotel.hpp"
#include"UsersManager.hpp"
#include"DataReader.hpp"
#include"HotelArrange.hpp"
#include"Filter.hpp"
#include"Const.hpp"
#include<map>
#include<string>
#include<vector>


class UTrip {
public:
	~UTrip();
	void load_data(std::string hotel_data_file_path, std::string ratings_data_file_path);
	std::string signup_new_user(std::string username, std::string password, std::string R_password, std::string email);
	std::string login_user(std::string email, std::string password);
	void logout_user(std::string session_id);
	bool has_user_logged_in(std::string session_id);
	void set_result_message(std::string message);
	std::string get_result_message();
	void detect_request_owner(std::string session_id);
	void offline_requset_owner();
	std::string get_user_name();
	double get_user_credit();
	void increase_user_credit(double amount);
	Hotel* find_hotel_by_id(std::string id);
	std::vector<Hotel*> get_hotels_to_be_showed_for_user();
	void set_stars_filter_condition_info(ProperConditionInfo filter_condition_info);
	ProperConditionInfo get_filter_condition_info();

private:
	HotelArrange hotel_arrange;
	std::vector<Hotel*> hotels;
	UsersManager users_manager;
	DataReader data_reader;
	std::string result_meesage;

	void reserve_rooms_for_user(const std::string& hotel_id, const std::string& room_type, int quantity, TimePeriod length_of_staying);
	void add_new_user_rating(std::map<std::string, std::string> ratings_info);
};

#endif
