#include<iostream>
#include<vector>
#include <functional>
#include <string>

using namespace std;

#define ZERO 0
#define ONE 1
#define FAILURE "NOT_FOUND"

struct Input_Info {

	int number_of_PasswordChars;
	vector<char> possible_chars_in_password;
	unsigned long int Hash;
};



unsigned long int generatePasswordHash ( std :: string password )
{
return std :: hash < std :: string >()(password);
}

int get_number_of_Password_C(void){
    
    int input_number;

	cin>>input_number;
	return input_number;
}

vector<char> get_possible_chars_in_password(void){

string str_of_possible_chars;

cin>>str_of_possible_chars;
vector<char> possible_chars(str_of_possible_chars.begin(),str_of_possible_chars.end());

return possible_chars;
}

unsigned long int get_Hash(void){

	unsigned long int input_hash;
     
    cin>>input_hash;
    return input_hash;
}

Input_Info get_inputs(void){

	Input_Info input_information;

    input_information.number_of_PasswordChars=get_number_of_Password_C();
    input_information.possible_chars_in_password=get_possible_chars_in_password();
    input_information.Hash=get_Hash();

    return input_information;
}

string string_of_vectorC(vector<char> vec){

	string generated_str(vec.begin(),vec.end());
	return generated_str;
}

  vector<int> find_password(const vector<char>& possible_chars_in_password, unsigned long int Hash, int number_of_PasswordChars, vector<char> random_password_chars,int index_in_RandomPassChar_vec=ZERO){

    vector<int> password_maker;

   if(index_in_RandomPassChar_vec==number_of_PasswordChars){
     if(Hash== generatePasswordHash(string_of_vectorC(random_password_chars)))
         password_maker.resize(number_of_PasswordChars);
        
         return password_maker;
   }

else{

  for(int index=ZERO;index<possible_chars_in_password.size();index++){

     random_password_chars[index_in_RandomPassChar_vec]=possible_chars_in_password[index];
    password_maker=find_password(possible_chars_in_password,Hash, number_of_PasswordChars, random_password_chars,index_in_RandomPassChar_vec + ONE);

    if(password_maker.size()==number_of_PasswordChars){

    	password_maker[index_in_RandomPassChar_vec]=index;
    	break;
    }
  }
}
return password_maker;
  }

string  extract_password(vector<int> password_maker, const vector<char>& possible_chars_in_password){

  string password;

  if(password_maker.size()==ZERO)
  return FAILURE;

for(int index=ZERO;index<password_maker.size();index++)

	password+=possible_chars_in_password[password_maker[index]];

return password;
}

vector<char> RandomPassChars_vector(int number_of_PasswordChars){

	vector<char> vec(number_of_PasswordChars);
	return vec;
}

int main(){

Input_Info pass_info;
vector<int>password_maker;
string password;

pass_info=get_inputs();
password_maker=find_password(pass_info.possible_chars_in_password,pass_info.Hash,pass_info.number_of_PasswordChars,RandomPassChars_vector(pass_info.number_of_PasswordChars));
password=extract_password(password_maker,pass_info.possible_chars_in_password);

cout<<password;
return ZERO;
}