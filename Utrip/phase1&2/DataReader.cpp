#include"DataReader.hpp"
#include"Hotel.hpp"
#include<sstream>
#include<fstream>
#include<algorithm>

using namespace std;


Hotel* DataReader::build_rooms_of_hotel(const vector<string>& hotel_fields, Hotel* hotel){
	 for(int room_kind_index = 0; room_kind_index < NUMBER_OF_ROOM_TYPES; room_kind_index++){
	 	
	 	hotel->set_room_price(ROOM_TYPES[room_kind_index], stoi(hotel_fields[H_price_of_rooms + room_kind_index]));
	 	for(int room_index = 0; room_index < stoi(hotel_fields[H_num_of_rooms + room_kind_index]); room_index++){
	 		hotel->add_room(ROOM_TYPES[room_kind_index]);
	 	}
	 }
	return hotel;
}

Hotel* DataReader::build_hotel_based_info(string hotel_info){
	vector<string> hotel_fields = parse_line_fields_based_delimiter(hotel_info, DELIMITER1);
	
	Hotel* new_hotel = new Hotel(hotel_fields[H_id], hotel_fields[H_name], stoi(hotel_fields[H_stars]), hotel_fields[H_overview],
							hotel_fields[H_amenities], hotel_fields[H_city], {stod(hotel_fields[H_latitude]), stod(hotel_fields[H_longitude])},
							hotel_fields[H_image_url]);
	new_hotel = build_rooms_of_hotel(hotel_fields, new_hotel);
	return new_hotel;
}

vector<Hotel*> DataReader::extract_hotels_data(string file_path){
	ifstream file_stream(file_path);
	string line;
	vector<Hotel*> hotels;

	getline(file_stream, line, NEW_LINE);
	while(getline(file_stream, line, NEW_LINE)){
		hotels.push_back(build_hotel_based_info(line));
	}
	return hotels;
}

void DataReader::add_ratings_items_to_hotel(Hotel* hotel, const vector<string>& ratings_items){
	vector<double> ratings;

	transform(ratings_items.begin() + 1, ratings_items.end(), back_inserter(ratings), [](string item){ return stod(item); });
	hotel->set_average_ratings(ratings);
}

vector<Hotel*> DataReader::extract_ratings_data(vector<Hotel*> hotels, string file_path){
	ifstream file_stream(file_path);
	vector<string> ratings_items;
	string line;

	getline(file_stream, line, NEW_LINE);
	while(getline(file_stream, line, NEW_LINE)){
		ratings_items = parse_line_fields_based_delimiter(line, DELIMITER1);
		auto hotel_it = find_if(hotels.begin(), hotels.end(), [&](Hotel* h){ return h->get_id() == ratings_items[H_id]; });
		if(hotel_it != hotels.end()){
			add_ratings_items_to_hotel(*hotel_it, ratings_items);
		}
	}
	return hotels;
}

vector<string> DataReader::parse_line_fields_based_delimiter(string line, char delimiter){

	string subline;
	stringstream line_stream(line);
	vector<string> extracted_sublines_in_string;

	while(getline(line_stream, subline, delimiter)){
		extracted_sublines_in_string.push_back(subline);
	}
	return extracted_sublines_in_string;
}
