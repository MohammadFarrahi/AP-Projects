#ifndef FILTER_HPP
#define FILTER_HPP "FILTER_HPP"

#include"Const.hpp"
#include"TimePeriod.hpp"


class Hotel;
struct ProperConditionInfo{
	std::string city;
	unsigned min_stars;
	unsigned max_stars;
	double min_average_price;
	double max_average_price;
	TimePeriod check_in_check_out_time;
	std::string room_type;
	int quantity;
	double average_user_budget;
	double standard_deviation;
};

const ProperConditionInfo DEFAULT_CONDITION_INFO = {"", 0, 0, 0, 0, TimePeriod(1,1), "", 0, 0, 0};

class Filter {
public:
	Filter(bool state_ = DISABLE) : state(state_) {}
	virtual std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects) = 0;
	virtual void disable_filtering();
	virtual void set_proper_condition(const ProperConditionInfo& condition_info) = 0;
	virtual bool active_filtering();
	virtual void set_user_order(std::string activation_order = ACTIVE_ORDER);
	bool is_active();

protected:
	bool state;
};

class FilterCity : public Filter {
public:
	std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects);
	void disable_filtering();
	void set_proper_condition(const ProperConditionInfo& condition_info);
	static bool is_valid_condition(std::string city);

private:
	std::string proper_city;
};

class FilterStars : public Filter {
public:
	std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects);
	void disable_filtering();
	void set_proper_condition(const ProperConditionInfo& condition_info);
	static bool is_valid_condition(int min_stars, int max_stars);

private:
	unsigned min_stars;
	unsigned max_stars;
};

class FilterPrice : public Filter {
public:
	std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects);
	void disable_filtering();
	void set_proper_condition(const ProperConditionInfo& condition_info);
	static bool is_valid_condition(double min_average_price, double max_average_price);

private:
	double min_average_price;
	double max_average_price;
};

class FilterProperRooms : public Filter {
public:
	std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects);
	void disable_filtering();
	void set_proper_condition(const ProperConditionInfo& condition_info);
	static bool is_valid_condition(std::string room_type, int quantity);

private:
	TimePeriod check_in_check_out_time;
	std::string room_type;
	int quantity;
};

class BudgetBaseFilter : public Filter {
public:
	BudgetBaseFilter() : user_order(ACTIVE_ORDER) {}
	std::vector<Hotel*> filter_objects(std::vector<Hotel*> objects);
	void disable_filtering();
	void set_proper_condition(const ProperConditionInfo& condition_info);
	bool active_filtering();
	void set_user_order(std::string activation_order = ACTIVE_ORDER);
	static bool is_valid_order(std::string order);

private:
	double average_user_budget;
	double standard_deviation;
	std::string user_order;
};

#endif
