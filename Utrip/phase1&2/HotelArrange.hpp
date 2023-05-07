#ifndef HOTEL_ARRANGE_HPP
#define HOTEL_ARRANGE_HPP "HOTEL_ARRANGE_HPP"

#include"Const.hpp"
#include<map>
#include"UsersManager.hpp"
#include<functional>


class Hotel;

typedef std::function<bool (Hotel*, Hotel*, std::string)> ArrangeBase;

class HotelArrange {
public:
	HotelArrange();
	void sort_list(std::vector<Hotel*>& hotels_list);
	void set_hotel_arrange_property(std::string property_, std::string order_);
	static bool is_valid_arrange_base(std::string property, std::string order);
	void default_sort(std::vector<Hotel*>& hotels_list);
	void reset_arrange_order();
	void set_logged_in_user(UsersManager::User* user_);
	
private:
	struct OrderSpecifier;
	std::map<std::string, ArrangeBase> arrange_bases;
	std::string property;
	std::string order;
	UsersManager::User* current_logged_in_user;

	std::vector<Hotel*> sort_based_personal_rating(std::vector<Hotel*> hotels_list);
};

struct HotelArrange::OrderSpecifier {
	std::string order;
	ArrangeBase arrange_base;
	bool operator()(Hotel* h1, Hotel* h2);
	OrderSpecifier(std::string order_, ArrangeBase arrange_base_);
};

#endif
