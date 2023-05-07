#ifndef RESERVE_HPP
#define RESERVE_HPP "RESERVE_HPP"

#include<vector>
#include<string>
#include"TimePeriod.hpp"

class Hotel;

class ReserveItem {
public:
	ReserveItem(Hotel* hotel_, std::string rooms_type_, std::vector<std::string> rooms_id_, int reservation_cost_,
				TimePeriod reservation_time_period_);
	double cancel_reservation();
	std::string get_reservation_info_text(int id);
	int get_reservation_cost() { return reservation_cost; }
	std::string get_booked_rooms_id_text();
	std::pair<double, double> get_price_info_per_night();

private:
	Hotel* hotel;
	std::string rooms_type;
	int quantity_of_rooms;
	TimePeriod reservation_time_period;
	int reservation_cost;
	std::vector<std::string> rooms_id;
};

#endif
