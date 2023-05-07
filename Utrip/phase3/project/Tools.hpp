#ifndef TOOL_HPP
#define TOOL_HPP "TOOL_HPP"

#include<map>
#include<utility>
#include"Const.hpp"

typedef std::pair<double, double> Sample_t;


std::map<std::string, std::string> extract_arguments_values(std::string request_info, std::vector<std::string> arguments);
std::string parse_word_from_first(std::string& line);
double get_weighted_average(std::vector<Sample_t> samples);
double get_weighted_average(std::vector<double> items, const std::vector<double>& weights);
double get_standard_deviation(std::vector<Sample_t>, double weighted_average);
double get_closest_of_value_in_range(double value, double start_of_range, double end_of_range);
double get_random_number_in_range(double start, double end);

template<typename K, typename V>
std::vector<V> make_vector_of_map_values(const std::map<K, V>& mapped_data, const std::vector<K> keys_arrangement = {}){
	std::vector<V> vector_of_values;

	if(keys_arrangement.size() == 0){
		transform(mapped_data.begin(), mapped_data.end(), std::back_inserter(vector_of_values), [](std::pair<K, V> p){ return p.second; });
		return vector_of_values;
	}
	for_each(keys_arrangement.begin(), keys_arrangement.end(), [&](K Key){ vector_of_values.push_back(mapped_data.at(Key)); });
	return vector_of_values;
}

#endif
