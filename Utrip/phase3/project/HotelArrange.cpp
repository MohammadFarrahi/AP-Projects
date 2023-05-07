#include"HotelArrange.hpp"
#include"Hotel.hpp"
#include"Exception.hpp"
#include"User.hpp"
#include<algorithm>


using namespace std;

HotelArrange::HotelArrange() : property(DEFAULT_PROPERTY), order(DEFAULT_ORDER), current_logged_in_user(NULL){
	arrange_bases[PROPERTIES[P_id]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->id < h2->id : h1->id > h2->id; };

	arrange_bases[PROPERTIES[P_name]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->name < h2->name : h1->name > h2->name; };

	arrange_bases[PROPERTIES[P_stars]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->stars < h2->stars : h1->stars > h2->stars; };

	arrange_bases[PROPERTIES[P_city]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->city < h2->city : h1->city > h2->city; };

	arrange_bases[PROPERTIES[P_standard_price]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->rooms[ROOM_TYPES[Standard]].first < h2->rooms[ROOM_TYPES[Standard]].first
																	: h1->rooms[ROOM_TYPES[Standard]].first > h2->rooms[ROOM_TYPES[Standard]].first; };

	arrange_bases[PROPERTIES[P_deluxe_price]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->rooms[ROOM_TYPES[Deluxe]].first < h2->rooms[ROOM_TYPES[Deluxe]].first
																	: h1->rooms[ROOM_TYPES[Deluxe]].first > h2->rooms[ROOM_TYPES[Deluxe]].first; };

	arrange_bases[PROPERTIES[P_luxury_price]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->rooms[ROOM_TYPES[Luxury]].first < h2->rooms[ROOM_TYPES[Luxury]].first
																	: h1->rooms[ROOM_TYPES[Luxury]].first > h2->rooms[ROOM_TYPES[Luxury]].first; };

	arrange_bases[PROPERTIES[P_premium_price]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->rooms[ROOM_TYPES[Permium]].first < h2->rooms[ROOM_TYPES[Permium]].first
																	: h1->rooms[ROOM_TYPES[Permium]].first > h2->rooms[ROOM_TYPES[Permium]].first; };

	arrange_bases[PROPERTIES[P_average_price]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->get_average_room_price() < h2->get_average_room_price()
																	: h1->get_average_room_price() > h2->get_average_room_price(); };

	arrange_bases[PROPERTIES[P_rating_overall]] = [](Hotel* h1, Hotel* h2, string order)
									{ return order == ASCENDING_ORDER ? h1->average_rating_items[Overall_rating] < h2->average_rating_items[Overall_rating]
																	: h1->average_rating_items[Overall_rating] > h2->average_rating_items[Overall_rating]; };
}

void HotelArrange::reset_arrange_order(){ property = DEFAULT_PROPERTY; order = DEFAULT_ORDER; current_logged_in_user = NULL; }

void HotelArrange::default_sort(vector<Hotel*>& hotels_list){
	sort(hotels_list.begin(), hotels_list.end(), HotelArrange::OrderSpecifier(DEFAULT_ORDER, arrange_bases[DEFAULT_PROPERTY]));
}

void HotelArrange::sort_list(vector<Hotel*>& hotels_list){
	if(!(property == DEFAULT_PROPERTY && order == DEFAULT_ORDER) && property != PROPERTIES[P_rating_personal]){
		stable_sort(hotels_list.begin(), hotels_list.end(), HotelArrange::OrderSpecifier(order, arrange_bases[property]));
	}
	if(property == PROPERTIES[P_rating_personal]){
		hotels_list = sort_based_personal_rating(hotels_list);
	}
}

vector<Hotel*> HotelArrange::sort_based_personal_rating(std::vector<Hotel*> hotels_list){
	vector<pair<Hotel*, double> > personal_rated_hotels;

	transform(hotels_list.begin(), hotels_list.end(), back_inserter(personal_rated_hotels),
		[this](Hotel* h) ->pair<Hotel*, double>{ return {h, this->current_logged_in_user->get_personal_rating(h)}; });

	stable_sort(personal_rated_hotels.begin(), personal_rated_hotels.end(),
		[this](pair<Hotel*, double> p1, pair<Hotel*, double> p2){ return (this->order == ASCENDING_ORDER ? p1.second < p2.second : p1.second > p2.second); });

	transform(personal_rated_hotels.begin(), personal_rated_hotels.end(), hotels_list.begin(), [](pair<Hotel*, double> p){ return p.first; });
	return hotels_list;
}

bool HotelArrange::is_valid_arrange_base(string property, string order){
	return ((find(PROPERTIES.begin(), PROPERTIES.end(), property) != PROPERTIES.end()) &&
			(order == ASCENDING_ORDER || order == DESCENDING_ORDER));
}

void HotelArrange::set_hotel_arrange_property(string property_, string order_){
	if(!is_valid_arrange_base(property_, order_)){ throw bad_request(); }
	property = property_; order = order_;
}

bool HotelArrange::OrderSpecifier::operator()(Hotel* h1, Hotel* h2){
	return arrange_base(h1, h2, order);
}

void HotelArrange::set_logged_in_user(UsersManager::User* user_){ current_logged_in_user = user_; }

HotelArrange::OrderSpecifier::OrderSpecifier(string order_, ArrangeBase arrange_base_) : order(order_), arrange_base(arrange_base_) {}
