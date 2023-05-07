#ifndef UTRIP_HPP
#define UTRIP_HPP "UTRIP_HPP"

#include"Hotel.hpp"
#include"UsersManager.hpp"
#include"DataReader.hpp"
#include"HotelArrange.hpp"
#include"Const.hpp"
#include<map>
#include<string>
#include<vector>


class UTrip {
public:
	~UTrip();
	void process_request(std::string input_request);
	std::string get_output_message();
	void load_data(std::string hotel_data_file_path, std::string ratings_data_file_path);

private:
	HotelArrange hotel_arrange;
	std::vector<Hotel*> hotels;
	UsersManager users_manager;
	DataReader data_reader;
	std::string output_message;

	void process_get_type_requests(std::string input_request);
	void process_post_type_requests_for_logged_in_users(std::string request, std::string arguments_info);
	void process_post_type_requests(std::string input_request);
	void process_delete_type_requests(std::string input_request);
	
	void get_hotel_info(std::string arguments_info);
	void get_general_hotels_info();
	void reserve_rooms_for_user(const std::string& hotel_id, const std::string& room_type, int quantity, TimePeriod length_of_staying);
	void add_new_user_rating(std::map<std::string, std::string> ratings_info);
	Hotel* find_hotel_by_id(std::string id);
	bool has_user_logged_in();
};

#endif
