#ifndef USER_HPP
#define USER_HPP "USER_HPP"

#include"./src/rsdl.hpp"
#include<utility>

#define USER_BASE_HEALTH 20
#define USER_BASE_MONEY 200

typedef int money_t;
typedef int blood_t;

class User {
public:
	User(blood_t health_ = USER_BASE_HEALTH, money_t money_ = USER_BASE_MONEY);
	bool is_dead();
	void update_health(blood_t health_damage_amount);
	void update_money(money_t total_cost);
	std::pair<money_t, std::pair<Point, char> > get_user_request(Window* window);
	void display_health_and_money(Window* window);

private:
	blood_t health;
	money_t money;
	Point last_mouse_position_when_L_click;
};

#endif
