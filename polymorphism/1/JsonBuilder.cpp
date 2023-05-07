#include"JsonBuilder.hpp"
#include<iostream>

#define NUMBER_OF_TABS_AT_FIRST 0
#define MOTHER_OBJECT_INDEX 0

using namespace std;


JsonBuilder::JsonBuilder() : last_built_container_id(MOTHER_OBJECT_INDEX) {
	built_containers.push_back(new Object());
}

void JsonBuilder::addStringToObject(int parent_id, Key_t key, std::string value){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
		built_containers[parent_id]->add_string_with_key(value, key);
		return;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

void JsonBuilder::addIntegerToObject(int parent_id, Key_t key, int value){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
		built_containers[parent_id]->add_integer_with_key(value, key);
		return;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

int JsonBuilder::addContainerToObject(int parent_id, Key_t key, std::string type){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
	 	Container* new_container = built_containers[parent_id]->add_container_with_key(type, key, last_built_container_id + 1);
	 	built_containers.push_back(new_container);
	 	return ++last_built_container_id;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

void JsonBuilder::addStringToArray(int parent_id, std::string value){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
		built_containers[parent_id]->add_string(value);
		return;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

void JsonBuilder::addIntegerToArray(int parent_id, int value){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
		built_containers[parent_id]->add_integer(value);
		return;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

int JsonBuilder::addContainerToArray(int parent_id, std::string type){

	try{
		if(last_built_container_id < parent_id){
			throw InvalidId();
		}
	 	Container* new_container = built_containers[parent_id]->add_container(type, last_built_container_id + 1);
	 	built_containers.push_back(new_container);
	 	return ++last_built_container_id;
	}
	catch(...){
		built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
		delete built_containers[MOTHER_OBJECT_INDEX];
		throw;
	}
}

void JsonBuilder::print(int id){

	if(last_built_container_id >= id){
		cout << built_containers[id]->make_text_to_be_showed(NUMBER_OF_TABS_AT_FIRST, NONE) << endl;
		return;
	}
	built_containers[MOTHER_OBJECT_INDEX]->delete_included_data();
	delete built_containers[MOTHER_OBJECT_INDEX];
	throw InvalidId();
}
