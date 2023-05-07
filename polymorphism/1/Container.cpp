#include"Container.hpp"
#include<sstream>

using namespace std;


Container::Container(int id_) : id(id_) {}

void Container::add_integer_with_key(int data, Key_t key) { throw InvalidId(); }

void Container::add_string_with_key(string data, Key_t key) { throw InvalidId(); }

Container* Container::add_container_with_key(string type, Key_t key, int id) { throw InvalidId(); return NULL; }

void Container::add_integer(int data) { throw InvalidId(); }

void Container::add_string(string data) { throw InvalidId(); }

Container* Container::add_container(string type, int id) { throw InvalidId(); return NULL; }

Array::Array(int id_) : Container(id_) {}

string Array::make_text_to_be_showed(int number_of_tabs_of_line, string additional_info){

	ostringstream os;
	os << add_tabs_to_text(number_of_tabs_of_line) << additional_info << NOTATIONS[L_bracket];
	for(int index = 0; index < (int)included_data.size() - 1; index++){

		os << NOTATIONS[newline];
		os << included_data[index]->make_text_to_be_showed(number_of_tabs_of_line + 1, NONE) << NOTATIONS[comma];
	}
	if(included_data.size() != 0){

		os <<  NOTATIONS[newline];
		os << included_data[included_data.size() - 1]->make_text_to_be_showed(number_of_tabs_of_line + 1, NONE);
		os << NOTATIONS[newline] << add_tabs_to_text(number_of_tabs_of_line);
	}
	os << NOTATIONS[R_bracket];
	return os.str();
}

void Array::add_integer(int data){
	included_data.push_back(new Integer(data));
}

void Array::add_string(string data){
	included_data.push_back(new String(data));
}

Container* Array::add_container(string type, int id){
	
	Container* new_container = NULL;
	if(type == ARRAY_TYPE){
		new_container = new Array(id);
	}
	if(type == OBJECT_TYPE){
		new_container = new Object(id);
	}
	if(new_container != NULL){
		included_data.push_back(new_container);
		return new_container;
	}
	throw UndefinedType();
}

Object::Object(int id_) : Container(id_) {}

string Object::make_text_to_be_showed(int number_of_tabs_of_line, string additional_info){

	ostringstream os;
	string key_text = NONE;
	os << add_tabs_to_text(number_of_tabs_of_line) << additional_info << NOTATIONS[L_accolade];
	for(int index = 0; index < (int)included_data.size() - 1; index++){

		key_text = NOTATIONS[D_cote] + keys_related_to_included_data[index] + NOTATIONS[D_cote] + NOTATIONS[colon] + NOTATIONS[space];
		os << NOTATIONS[newline];
		os << included_data[index]->make_text_to_be_showed(number_of_tabs_of_line + 1, key_text);
		os << NOTATIONS[comma];
	}
	if(included_data.size() != 0){

		key_text = NOTATIONS[D_cote] + keys_related_to_included_data[included_data.size() - 1] + NOTATIONS[D_cote] + NOTATIONS[colon] + NOTATIONS[space];
		os <<  NOTATIONS[newline];
		os << included_data[included_data.size() - 1]->make_text_to_be_showed(number_of_tabs_of_line + 1, key_text);
		os << NOTATIONS[newline] << add_tabs_to_text(number_of_tabs_of_line);
	}
	os << NOTATIONS[R_accolade];
	return os.str();
}

void Object::add_integer_with_key(int data, Key_t key){
	
	if(is_new_key(key, keys_related_to_included_data)){
		included_data.push_back(new Integer(data));
		keys_related_to_included_data.push_back(key);
		return;
	}
	throw DuplicateKey();
}

void Object::add_string_with_key(string data, Key_t key){

	if(is_new_key(key, keys_related_to_included_data)){
		included_data.push_back(new String(data));
		keys_related_to_included_data.push_back(key);
		return;
	}
	throw DuplicateKey();
}

Container* Object::add_container_with_key(string type, Key_t key, int id){

	if(is_new_key(key, keys_related_to_included_data)){
		
		Container* new_container = NULL;
		if(type == ARRAY_TYPE){
			new_container = new Array(id);
		}
		if(type == OBJECT_TYPE){
			new_container = new Object(id);
		}
		if(new_container != NULL){
			included_data.push_back(new_container);
			keys_related_to_included_data.push_back(key);
			return new_container;
		}
		throw UndefinedType();
	}
	throw DuplicateKey();
}

void Container::delete_included_data(){

	for(Data* data_to_be_deleted : included_data){

		data_to_be_deleted->delete_included_data();
		delete data_to_be_deleted;
	}
}

bool is_new_key(const Key_t& new_key, const std::vector<Key_t>& keys){

	for(Key_t existing_key : keys){

		if(new_key == existing_key){
			return false;
		}
	}
	return true;
}
