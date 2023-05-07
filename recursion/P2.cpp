#include<iostream>
#include<vector>
#define ZERO 0
#define ONE 1

using namespace std;


vector<int> get_numbers(void){

	vector<int> Numbers;
	int in_number;

	while(cin>>in_number){
		Numbers.push_back(in_number);
	}

	return Numbers;
}

int calculate_on_numbers(vector<int>& input_numbers,int position_index=ZERO,int offset=ONE){

int calculated_value=ONE;

	if(position_index-offset<ZERO && position_index+offset>=input_numbers.size()){
		if(position_index<input_numbers.size()-ONE)
			calculate_on_numbers(input_numbers,position_index+ONE);

		return ONE;
	}

     if(position_index-offset>=ZERO)
        calculated_value*=input_numbers[position_index-offset];

    if(position_index+offset<input_numbers.size())
    	calculated_value*=input_numbers[position_index+offset];

    calculated_value*=calculate_on_numbers(input_numbers,position_index,offset+ONE);

    if(offset==ONE)
      input_numbers[position_index]=calculated_value;
   else
   	return calculated_value;

}

void print_new_numbers(vector<int> numbers_to_print,int pos=0){

	if(pos==numbers_to_print.size())
		return;

   cout<<numbers_to_print[pos];
   if(pos!=numbers_to_print.size()-ONE)
   cout<<' ';

    print_new_numbers(numbers_to_print,pos+ONE);
}

int main(){

vector<int> Numebrs_to_be_calculated;
Numebrs_to_be_calculated=get_numbers();

calculate_on_numbers(Numebrs_to_be_calculated);
print_new_numbers(Numebrs_to_be_calculated);

	return ZERO;
}