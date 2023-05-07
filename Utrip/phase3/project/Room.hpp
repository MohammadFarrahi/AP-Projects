#ifndef ROOM_HPP
#define ROOM_HPP "ROOM_HPP"

#include<string>
#include<vector>
#include<utility>


class TimePeriod;
class Hotel;

class Hotel::Room {
public:
	Room(std::string id_) : id(id_) {}
	std::string id;
	std::vector<TimePeriod> renting_schedule;

	bool is_empty_this_time(const TimePeriod& time);
	void get_reserved(TimePeriod renting_period);
	void cancel_renting(const TimePeriod& renting_info);
};

#endif
