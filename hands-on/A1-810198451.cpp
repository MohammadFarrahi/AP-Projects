#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#define ENCRYPT_command "encrypt"
#define DECRYPT_command "decrypt"
#define SIMPLEMODE "simple"
#define COMPLICATEDMODE "complicated"
#define ZERO 0
#define RandomNumberRange 11
#define ERROR -1
using namespace std;

void get_inputs(string& command,string& mode,vector<char>& key,string& input_file_a,string& output_file_a){
	
	string input_key;

	cin>>command;
	cin>>mode;
	cin.ignore();
    getline(cin,input_key);
    
    key.resize(input_key.length());
    copy(input_key.begin(),input_key.end(),key.begin());

    getline(cin,input_file_a);
    getline(cin,output_file_a);
}   

void encrypt_simple_mode(vector<char>& ItemsToBeEncrypted,vector<int>& encrypted_digits,vector<char> key){
     
     long unsigned int counter=0;

     for(counter=0;counter<ItemsToBeEncrypted.size();counter++)
         encrypted_digits.push_back(ItemsToBeEncrypted[counter]+key[counter%key.size()]);

         ItemsToBeEncrypted.resize(ZERO);
}

void decrypt_simple_mode(vector<int>& encrypted_digits,vector<char>& ItemsToBeDecrypted,vector<char> key){

	long unsigned int counter;

	for(counter=0;counter<encrypted_digits.size();counter++)
		ItemsToBeDecrypted.push_back(encrypted_digits[counter]-key[counter%key.size()]);
	
	    encrypted_digits.resize(ZERO);
}

void encrypt_comp_mode(vector<char>& ItemsToBeEncrypted,vector<int>& encrypted_digits,vector<char> key){

	int counter=0;
	int seed_maker=0;

	for(counter=0;counter<key.size();counter++)
		seed_maker+=key[counter];

    srand(seed_maker);
    for(counter=0;counter<ItemsToBeEncrypted.size();counter++){

    	encrypted_digits.push_back(rand()%RandomNumberRange);
    	encrypted_digits[counter]+=ItemsToBeEncrypted[counter];
    }

    ItemsToBeEncrypted.resize(ZERO);
}

void decrypt_comp_mode(vector<int>& encrypted_digits,vector<char>& ItemsToBeDecrypted,vector<char> key){

     int counter;
     int seed_maker=0;

    for(counter=0;counter<key.size();counter++)
    	seed_maker+=key[counter];

     srand(seed_maker);
     for(counter=0;counter<encrypted_digits.size();counter++){
      
      ItemsToBeDecrypted.push_back((char)(rand()%RandomNumberRange));
      ItemsToBeDecrypted[counter]=(char)encrypted_digits[counter]-ItemsToBeDecrypted[counter];
     }

     encrypted_digits.resize(ZERO);
}

void open_file_to_decrypt(vector<int>& file_content,string in_FileName){

     fstream input_file_S(in_FileName,ios::in);
     int input_digit;

     while(input_file_S>>input_digit)
          file_content.push_back(input_digit);
     
    input_file_S.close();
}

void open_file_to_encrypt(vector<char>& file_content,string in_FileName){

	fstream input_file_S(in_FileName,ios::in);
	char input_char;

	while(input_file_S.get(input_char))
         file_content.push_back(input_char);

     input_file_S.close();
}

int save_EncryptedInfo_to_file(vector<int>& EncryptedInfo,string out_FileName){

     fstream output_file_S(out_FileName,ios::out);

     if(!output_file_S)
     	return ERROR;

     for(int counter=0;counter<EncryptedInfo.size();counter++)
     	output_file_S<<EncryptedInfo[counter]<<endl;

     output_file_S.close();
    EncryptedInfo.resize(ZERO);

    return ZERO;
}

int save_DecryptedInfo_to_file(vector<char>& DecryptedInfo,string out_FileName){

    fstream output_file_S(out_FileName,ios::out);

    if(!output_file_S){
     	return ERROR;
    }

   for(int counter=0;counter<DecryptedInfo.size();counter++)
   	  output_file_S.put(DecryptedInfo[counter]);

   	output_file_S.close();
    DecryptedInfo.resize(ZERO);

     return ZERO;
}

int Encrypt_file(string mode,string input_file_name,string output_file_name,vector<char> key ){

     vector<char> characters_of_file;
     vector<int> coded_unmbers;
     int is_saved;

     open_file_to_encrypt(characters_of_file,input_file_name);

     if(mode==SIMPLEMODE)
        encrypt_simple_mode(characters_of_file,coded_unmbers,key);
     
     else if(mode==COMPLICATEDMODE)
         encrypt_comp_mode(characters_of_file,coded_unmbers,key);

     else{
     	cout<<"\n\nERROR:The mode is undifined.Program is ending...\n";
         return ERROR;
     }

     is_saved=save_EncryptedInfo_to_file(coded_unmbers,output_file_name);
     if(is_saved=ERROR){
       coded_unmbers.resize(ZERO);
       return ERROR;
     }

     return ZERO;
}

int Decrypt_file(string mode,string input_file_name,string output_file_name,vector<char> key){

     vector<char> characters_of_OutputFile;
     vector<int> coded_unmbers_of_InputFile;
     int is_saved;

     open_file_to_decrypt(coded_unmbers_of_InputFile,input_file_name);

     if(mode==SIMPLEMODE)
     	decrypt_simple_mode(coded_unmbers_of_InputFile,characters_of_OutputFile,key);

     else if(mode==COMPLICATEDMODE)
         decrypt_comp_mode(coded_unmbers_of_InputFile,characters_of_OutputFile,key);

     else{
         cout<<"\n\nERROR:The mode is undifined.Program is ending...\n";
         return ERROR;
     }

     is_saved=save_DecryptedInfo_to_file(characters_of_OutputFile,output_file_name);

       if(is_saved==ERROR){
        characters_of_OutputFile.resize(ZERO);
        return ERROR;
     }

	return ZERO;
}

int do_command(string in_command,string in_mode,vector<char> in_key,string input_file,string output_file){

 int status;

 if(in_command==ENCRYPT_command)
   status=Encrypt_file(in_mode,input_file,output_file,in_key);
 
 else if(in_command==DECRYPT_command)
   status=Decrypt_file(in_mode,input_file,output_file,in_key);
/////////////////
else{
	cout<<"\n\nERROR:The command is undifined.Program is ending...\n";
         return ERROR;
}

return status;
}

int main(){

int is_error;
vector<char> Key;
string Command,Command_Mode,InFile,OutFile;

get_inputs(Command,Command_Mode,Key,InFile,OutFile);
is_error=do_command(Command,Command_Mode,Key,InFile,OutFile);

Key.resize(ZERO);

if(is_error==ERROR)
	return is_error;

return ZERO;
}