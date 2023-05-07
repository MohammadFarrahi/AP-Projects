#ifndef DATA_HPP
#define DATA_HPP "DATA_HPP"

#include"Const.hpp"

class Hotel;

class DataReader {
public:
	std::vector<Hotel*> extract_hotels_data(std::string file_path);
	std::vector<Hotel*> extract_ratings_data(std::vector<Hotel*> hotels, std::string file_path);
	
private:
	std::vector<std::string> parse_line_fields_based_delimiter(std::string line, char delimiter);
	Hotel* build_rooms_of_hotel(const std::vector<std::string>& hotel_fields, Hotel* hotel);
	Hotel* build_hotel_based_info(std::string hotel_info);
	void add_ratings_items_to_hotel(Hotel* hotel, const std::vector<std::string>& ratings_items);
};

#endif
