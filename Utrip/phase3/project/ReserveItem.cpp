#include"ReserveItem.hpp"
#include"Hotel.hpp"
#include<sstream>
#include<algorithm>

using namespace std;


ReserveItem::ReserveItem(Hotel* hotel_, string rooms_type_, vector<string> rooms_id_, int reservation_cost_,
			TimePeriod reservation_time_period_) : hotel(hotel_), rooms_type(rooms_type_), rooms_id(rooms_id_),
			reservation_cost(reservation_cost_), reservation_time_period(reservation_time_period_)
{
	quantity_of_rooms = rooms_id.size();
}

double ReserveItem::cancel_reservation(){
	for(int index = 0; index < quantity_of_rooms; index++){
		hotel->cancel_reservation_of_room(rooms_type, rooms_id[index], reservation_time_period);
	}
	return (double)reservation_cost / 2.0;
}

string ReserveItem::get_reservation_info_text(int id){
	ostringstream output_info;
	
	output_info << "id: " << id << " hotel: " << hotel->get_id() << " room: " << rooms_type << " quantity: " << quantity_of_rooms;
	output_info << " cost: " << reservation_cost << " check_in " << reservation_time_period.get_starting_point();
	output_info << " check_out " << reservation_time_period.get_ending_point();
	return output_info.str();
}

string ReserveItem::get_booked_rooms_id_text(){
	ostringstream output;

	for_each(rooms_id.begin(), rooms_id.end(), [&](string room_id){ output << room_id << SPACE_CHAR; });
	return output.str();
}

pair<double, double> ReserveItem::get_price_info_per_night(){
	return {(double)quantity_of_rooms, (double)reservation_cost / (reservation_time_period.get_amount() * quantity_of_rooms)};
}
