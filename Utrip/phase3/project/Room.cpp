#include"TimePeriod.hpp"
#include"Hotel.hpp"
#include"Room.hpp"

using namespace std;

bool Hotel::Room::is_empty_this_time(const TimePeriod& time){
	for(auto renting_period : renting_schedule){
		if(renting_period.has_overlap(time)){
			return false;
		}
	}
	return true;
}

void Hotel::Room::get_reserved(TimePeriod renting_period){
	renting_schedule.push_back(renting_period);
}

void Hotel::Room::cancel_renting(const TimePeriod& renting_info){
	for(int index = 0; index < renting_schedule.size(); index++){
		if(renting_schedule[index] == renting_info){
			renting_schedule.erase(renting_schedule.begin() + index);
			break;
		}
	}
}
