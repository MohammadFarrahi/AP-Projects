#include"User.hpp"

#define EXIT 'q'
#define NO_REQUEST '0'

#define FONT_NAME "./Assets/FreeSansOblique-8j92.otf"
#define FONT_SIZE 25

using namespace std;


User::User(blood_t health_, money_t money_)
			: health(health_), money(money_) {}

void User::display_health_and_money(Window* window){

	window->show_text("Hearts : " + to_string(health), Point(50, 50), RED, FONT_NAME, FONT_SIZE);
	window->show_text("Gold : " + to_string(money), Point(300, 50), YELLOW, FONT_NAME, FONT_SIZE);
}

bool User::is_dead(){
	
	if(health <= 0){
	
		health = 0;
		return true;
	}
	return false;
}

void User::update_health(blood_t health_damage_amount){ health -= health_damage_amount; }

void User::update_money(money_t total_cost){ money -= total_cost; }

pair<money_t, pair<Point, char> > User::get_user_request(Window* window){

	char user_request_type = NO_REQUEST;
	while(window->has_pending_event()){

		Event event = window->poll_for_event();
		switch(event.get_type()){

			case Event::EventType::LCLICK :{
				last_mouse_position_when_L_click = event.get_mouse_position();
				break;
			}
			case Event::EventType::KEY_PRESS :{
				user_request_type = event.get_pressed_key();
				return {money, {last_mouse_position_when_L_click, user_request_type}};
			}
			case Event::EventType::QUIT :{
				user_request_type = EXIT;
				return {0, {last_mouse_position_when_L_click, user_request_type}};
			}
			default :
			break;
		}
	}
	if(user_request_type == NO_REQUEST){
		throw string("No Request till now.\n\n");
	}
}
