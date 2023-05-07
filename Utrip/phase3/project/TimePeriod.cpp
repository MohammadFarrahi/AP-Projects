#include"Exception.hpp"
#include"TimePeriod.hpp"

using namespace std;


TimePeriod::TimePeriod(int starting_, int ending_){
	if(!(0 < starting_ && starting_ <= ending_)){
		throw bad_request();
	}
	starting_point = starting_;
	ending_point = ending_;
}

int TimePeriod::get_amount() const{
	return ending_point - starting_point + 1;
}

bool TimePeriod::operator==(const TimePeriod& time_period) const{
	return ((this->starting_point == time_period.starting_point) && (this->ending_point == time_period.ending_point));
}

bool TimePeriod::has_overlap(const TimePeriod& time_period) const{
	if((this->starting_point <= time_period.starting_point && time_period.starting_point <= this-> ending_point) ||
		(this->starting_point <= time_period.ending_point && time_period.ending_point <= this->ending_point) ||
		(time_period.starting_point <= this->starting_point && this->starting_point <= time_period.ending_point))
	{
		return true;
	}
	return false;
}

TimePeriod& TimePeriod::operator=(const TimePeriod& time_period){
	starting_point = time_period.starting_point;
	ending_point = time_period.ending_point;
	return (*this);
}
