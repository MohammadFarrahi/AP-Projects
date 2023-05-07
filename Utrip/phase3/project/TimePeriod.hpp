#ifndef TIME_HPP
#define TIME_HPP "TIME_HPP"


class TimePeriod {
public:
	TimePeriod(int starting_ = 1, int ending_ = 1);
	bool has_overlap(const TimePeriod& time_period) const;
	bool operator==(const TimePeriod& time_period) const;
	TimePeriod& operator=(const TimePeriod& time_period);	
	int get_amount() const;
	int get_starting_point() const{ return starting_point; }
	int get_ending_point() const{ return ending_point; }

private:
	int starting_point;
	int ending_point;
};

#endif
