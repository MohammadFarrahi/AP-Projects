#include"Tools.hpp"
#include"Exception.hpp"
#include<sstream>
#include<cmath>
#include<numeric>
#include<random>
#include<cfloat>
#include<algorithm>

using namespace std;


map<string, string> extract_arguments_values(string request_info, vector<string> arguments){
	if(parse_word_from_first(request_info) != ARGUMENT_SPECIFIER){
		throw bad_request();
	}
	bool is_invalid_argument = true;
	int num_of_arguments = arguments.size();
	map<string, string> extracted_values;
	string argument, argument_value;

	for(int argument_counter = 0; argument_counter < num_of_arguments; argument_counter++){
		argument = parse_word_from_first(request_info);

		for(int i = 0; i < arguments.size(); i++){
			if(argument == arguments[i]){
				is_invalid_argument = false;
				if((argument_value = parse_word_from_first(request_info)) != EMPTY){
					extracted_values[arguments[i]] = argument_value;
					arguments.erase(arguments.begin() + i);
					break;
				}
				else{
					throw bad_request();
				}
			}
		}
		if(is_invalid_argument){
			throw bad_request();
		}
		is_invalid_argument = true;
	}
	if(parse_word_from_first(request_info) != EMPTY){
		throw bad_request();
	}
	return extracted_values;
}

string parse_word_from_first(string& line){
	string word;
	char next_char;
	bool is_empty = true;
	istringstream line_stream(line);

	line_stream >> word;
	while(line_stream.get(next_char)){
		if(next_char != SPACE_CHAR){
			is_empty = false;
			line_stream.unget();
			getline(line_stream, line);
			break;
		}
	}
	if(is_empty){
		line = EMPTY;
	}
	return word;
}

double get_weighted_average(vector<Sample_t> samples){
	Sample_t sum_of_samples;

	sum_of_samples = accumulate(samples.begin(), samples.end(), sum_of_samples,
				[](Sample_t r, Sample_t s) ->Sample_t{ return {r.first + s.first, r.second + s.first * s.second}; });

	return sum_of_samples.second / sum_of_samples.first;
}

double get_standard_deviation(vector<Sample_t> samples, double weighted_average){
	Sample_t result;

	result = accumulate(samples.begin(), samples.end(), result,
		[&](Sample_t r, Sample_t s) ->Sample_t{ return {r.first + s.first, r.second + pow((weighted_average - s.second), 2) * s.first}; });

	if(result.first - 1 == 0){ return 0; }
	return sqrt(result.second / (result.first - 1));
}

double get_weighted_average(vector<double> items, const vector<double>& weights){
	vector<Sample_t> samples;
	int counter = 0;

	transform(items.begin(), items.end(), back_inserter(samples), [&counter, &weights](double item) ->Sample_t{ return {weights[counter++], item}; });
	return get_weighted_average(samples);
}

double get_closest_of_value_in_range(double value, double start_of_range, double end_of_range){
	if(start_of_range > end_of_range){ throw bad_request(); }
	if(start_of_range <= value && value <= end_of_range){ return value; }
	return fabs(value - start_of_range) <= fabs(value - end_of_range) ? start_of_range : end_of_range;
}

double get_random_number_in_range(double start, double end){
	if(start > end){ throw bad_request(); }
	
	random_device seed_maker;
	mt19937 generator(seed_maker());
	uniform_real_distribution<double> dis(start, nextafter(end, DBL_MAX));

	return dis(generator);
}
