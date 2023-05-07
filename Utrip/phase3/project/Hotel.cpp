#include"Hotel.hpp"
#include"Room.hpp"
#include"ReserveItem.hpp"
#include"Exception.hpp"
#include"DataReader.hpp"
#include<sstream>
#include<iomanip>
#include<algorithm>

using namespace std;


Hotel::Hotel(const string& id_, const string& name_, const unsigned& stars_, const string& overview_, const string& amenities_,
			const string& city_, const pair<double, double>& cordinate_, const string& url_) : id(id_), name(name_), stars(stars_),
			property_amenities(amenities_), cordinate(cordinate_), image_url(url_), city(city_)
{
	hotel_overview = overview_;
}

Hotel::~Hotel(){
	for(auto& room_kind : rooms){
		for(auto& room : room_kind.second.second){
			delete room.second;
		}
	}
}

vector<string> Hotel::get_amenities(){
	return DataReader::parse_line_fields_based_delimiter(property_amenities, POP_DELIMITER);
}

map<string, pair<int, int> > Hotel::get_rooms_info(){
	map<string, pair<int, int> > rooms_info;
	for_each(ROOM_TYPES.begin(), ROOM_TYPES.end(), [&rooms_info, this](string type)
		{ rooms_info[type] = {this->rooms[type].first, this->rooms[type].second.size()}; });
	return rooms_info;
}

bool Hotel::has_enough_rooms(string room_type, int quantity, const TimePeriod& in_out_time){
	return get_proper_rooms_id(room_type, quantity, in_out_time).first;
}

int Hotel::get_total_price_of_reservation(const string& room_type, int quantity, int days_of_staying){
	return rooms[room_type].first * quantity * days_of_staying;
}

ReserveItem* Hotel::make_reservation(const string& room_type, const int& quantity, const TimePeriod& reservatiion_time_period, const double& credit){
	if(!Hotel::is_valid_room_type(room_type) || quantity <= 0){
		throw bad_request();
	}
	pair<bool, vector<string> > proper_rooms = get_proper_rooms_id(room_type, quantity, reservatiion_time_period);
	int total_price = get_total_price_of_reservation(room_type, quantity, reservatiion_time_period.get_amount());
	if(proper_rooms.first != ENOUGH){
		throw lack_of_room();
	}
	if(credit < (double)total_price){
		throw lack_of_money();
	}

	vector<string> booked_rooms_id;
	for(int booked_rooms_counter = 0; booked_rooms_counter < quantity; booked_rooms_counter++){
		booked_rooms_id.push_back(proper_rooms.second[booked_rooms_counter]);
		rooms[room_type].second[proper_rooms.second[booked_rooms_counter]]->get_reserved(reservatiion_time_period);
	}
	return new ReserveItem(this, room_type, booked_rooms_id, total_price, reservatiion_time_period);
}

void Hotel::cancel_reservation_of_room(string room_type, string room_id, const TimePeriod& renting_info){
	rooms[room_type].second[room_id]->cancel_renting(renting_info);
}

void Hotel::set_room_price(string type, int price_){
	rooms[type].first = price_;
}

void Hotel::add_room(string type){
	string new_id = type.front() + to_string(rooms[type].second.size() + 1);
	rooms[type].second.insert(pair<string, Hotel::Room*>(new_id, new Hotel::Room(new_id)));
}

bool Hotel::is_in_this_city(string city_) const{ return (city_ == city); }

double Hotel::get_average_room_price() const{
	double sum_of_prices = 0;
	int number_of_existing_room_kind = 0;
	
	for(auto& room_kind : rooms){
		if(room_kind.second.first != 0){
			sum_of_prices += room_kind.second.first;
			number_of_existing_room_kind++;
		}
	}
	if(number_of_existing_room_kind == 0){
		return 0;
	}
	return sum_of_prices / (double)number_of_existing_room_kind; 
}

bool Hotel::is_valid_room_type(const string& room_type){
	for(const auto& room : ROOM_TYPES){
		if(room == room_type){
			return true;
		}
	}
	return false;
}

pair<bool, vector<string> > Hotel::get_proper_rooms_id(string room_type, int quantity, const TimePeriod& in_out_time){
	int room_counter = 0;
	bool is_enough = false;
	vector<string> proper_rooms_id;

	for(map<string, Hotel::Room*>::iterator it = rooms[room_type].second.begin();
		it != rooms[room_type].second.end(); it++)
	{
		if(it->second->is_empty_this_time(in_out_time)){
			room_counter++;
			proper_rooms_id.push_back(it->first);
		}
	}
	if(room_counter >= quantity){
		is_enough = true;
	}
	sort(proper_rooms_id.begin(), proper_rooms_id.end(), sort_rooms_based_id);
	return {is_enough, proper_rooms_id};
}

string Hotel::show_average_users_rating_text(){
	if(average_rating_items.size() == 0){
		return "No Rating\n";
	}
	ostringstream output;
	output << fixed;
	output << "location: " << setprecision(2) << average_rating_items[Location] << endl;
	output << "cleanliness: " << setprecision(2) << average_rating_items[Cleanliness] << endl;
	output << "staff: " << setprecision(2) << average_rating_items[Staff] << endl;
	output << "facilities: " << setprecision(2) << average_rating_items[Facilities] << endl;
	output << "value_for_money: " << setprecision(2) << average_rating_items[Value_for_money] << endl;
	output << "overall_rating: " << setprecision(2) << average_rating_items[Overall_rating] << endl;

	return output.str();
}
string Hotel::show_users_comments_text(){
	ostringstream output;
	
	for(int index = (int)users_comments.size() - 1; index >= 0; index--){
		output << users_comments[index].first << ": " << users_comments[index].second << endl;
	}
	return output.str();
}

void Hotel::set_average_ratings(const vector<double>& ratings){
	average_rating_items = ratings;
}

void Hotel::add_user_comment(const string& username, const string comment){
	if(comment.length() == 0){
		throw bad_request();
	}
	users_comments.push_back({username, comment});
}

string Hotel::show_general_hotel_info_text(){
	ostringstream output;
	int number_of_rooms = 0;
	
	output << id << SPACE_CHAR << name << SPACE_CHAR << stars << SPACE_CHAR << city << SPACE_CHAR;
	for(auto& room_kind : rooms){
		number_of_rooms += room_kind.second.second.size();
	}
	output << number_of_rooms << SPACE_CHAR << fixed << setprecision(2) << get_average_room_price() << SPACE_CHAR << endl;
	return output.str();
}

string Hotel::show_total_hotel_info_text(){
	ostringstream output;

	output << id << '\n' << name << endl;
	output << "star: " << stars << endl;
	output << "overview: " << hotel_overview << endl;
	output << "amenities: " << property_amenities << endl;
	output << "city: " << city << endl;
	output << "latitude: " << fixed << setprecision(2) << cordinate.first << endl;
	output << "longitude: " << setprecision(2) << cordinate.second << endl;
	output << "#rooms: " << rooms[ROOM_TYPES[Standard]].second.size() << SPACE_CHAR << rooms[ROOM_TYPES[Deluxe]].second.size();
	output << SPACE_CHAR << rooms[ROOM_TYPES[Luxury]].second.size() << SPACE_CHAR << rooms[ROOM_TYPES[Permium]].second.size() << endl;
	output << "price: " << rooms[ROOM_TYPES[Standard]].first << SPACE_CHAR << rooms[ROOM_TYPES[Deluxe]].first << SPACE_CHAR;
	output << rooms[ROOM_TYPES[Luxury]].first << SPACE_CHAR << rooms[ROOM_TYPES[Permium]].first << endl;

	return output.str();
}

vector<double> Hotel::get_average_ratings_in_special_fields(){ return vector<double>(average_rating_items.begin(), average_rating_items.end() - 1); }

bool Hotel::sort_rooms_based_id(const string& s1, const string& s2){
	return (stoi(s1.substr(FIRST_CHAR)) < stoi(s2.substr(FIRST_CHAR)));
}
