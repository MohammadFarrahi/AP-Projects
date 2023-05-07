#ifndef HOTEL_HPP
#define HOTEL_HPP "HOTEL_HPP"

#include"Const.hpp"
#include<utility>
#include<map>


class ReserveItem;
class TimePeriod;
class HotelArrange;

class Hotel {
public:
	Hotel(const std::string& id_, const std::string& name_, const unsigned& stars_, const std::string& overview_, const std::string& amenities_,
			const std::string& city_, const std::pair<double, double>& cordinate_, const std::string& url_);
	~Hotel();
	void set_room_price(std::string type, int price_);
	void add_room(std::string type);
	unsigned get_stars() const{ return stars; }
	std::string get_id() { return id; }
	bool is_in_this_city(std::string city_) const;
	static bool is_valid_room_type(const std::string& room_type);
	void set_average_ratings(const std::vector<double>& ratings);
	void add_user_comment(const std::string& username, const std::string comment);
	std::string show_average_users_rating_text();
	std::string show_users_comments_text();
	std::string show_general_hotel_info_text();
	std::string show_total_hotel_info_text();
	bool has_enough_rooms(std::string room_type, int quantity, const TimePeriod& in_out_time);
	ReserveItem* make_reservation(const std::string& room_type, const int& quantity, const TimePeriod& reservatiion_time_period, const double& credit);
	void cancel_reservation_of_room(std::string room_type, std::string room_id, const TimePeriod& renting_info);
	double get_average_room_price() const;
	std::vector<double> get_average_ratings_in_special_fields();

private:
	class Room;
	std::string id;
	std::string name;
	unsigned stars;
	std::string hotel_overview;
	std::string property_amenities;
	std::string city;
	std::pair<double, double> cordinate;
	std::string image_url;
	std::map<std::string, std::pair<int, std::map<std::string, Room*> > > rooms;
	std::vector<double> average_rating_items;
	std::vector<std::pair<std::string, std::string> > users_comments;

	int get_total_price_of_reservation(const std::string& room_type, int quantity, int days_of_staying);
	std::pair<bool, std::vector<std::string> > get_proper_rooms_id(std::string room_type, int quantity, const TimePeriod& in_out_time);
	static bool sort_rooms_based_id(const std::string& s1, const std::string& s2);

	friend class HotelArrange;
};

#endif
