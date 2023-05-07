#include<iostream>
#include<vector>
#include<string>
#define ZERO 0
#define ONE 1
#define ERROR -1

using namespace std;

vector<char> get_string(void){

	vector<char> input_string;
	char input_char;

	while(cin.get(input_char)){
		input_string.push_back(input_char);
	}

	return input_string;
}

void reverse_string(vector<char>& in_string, int starting_pos, int ending_pos){
    
     char temp;
     
     if(ending_pos < starting_pos)
     	return;

     temp = in_string[starting_pos];
     in_string[starting_pos] = in_string[ending_pos];
     in_string[ending_pos] = temp;

     reverse_string(in_string,starting_pos + ONE,ending_pos - ONE);
} 

void encrypt_string_recursively(vector<char>& input_string, int beginning_index, int ending_index){

     if(beginning_index == ending_index)
     	return;

     reverse_string(input_string, beginning_index, ending_index);

     int pos_of_mid_char_after_reverse = beginning_index + ending_index - (beginning_index + ending_index - ONE) / 2;

    encrypt_string_recursively(input_string , beginning_index , pos_of_mid_char_after_reverse - ONE);
     encrypt_string_recursively(input_string , pos_of_mid_char_after_reverse, ending_index);
}

int encrypt_string(vector<char>& string_to_encrypt){

if(string_to_encrypt.size()==ZERO)
  return ERROR;

encrypt_string_recursively(string_to_encrypt, ZERO ,string_to_encrypt.size() - ONE);
return ZERO;
}

void print_string(vector<char> string_to_print,int pos=0){

	if(pos==string_to_print.size())
		return;

    cout.put(string_to_print[pos]);

    print_string(string_to_print,pos+ONE);
}


int main(){

  vector<char> String;
  String=get_string();

  encrypt_string(String);
  print_string(String);
 
	
	return ZERO;
}