#ifndef CONTAINER_HPP
#define CONTAINER_HPP "CONTAINER_HPP"

#include<vector>
#include<string>
#include<utility>
#include"Exception.hpp"
#include"Data.hpp"

#define ARRAY_TYPE "array"
#define OBJECT_TYPE "object"

typedef std::string Key_t;


class Container : public Data {
public:
	Container(int id_);
	virtual std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info) = 0;
	virtual void add_integer_with_key(int data, Key_t key);
	virtual void add_string_with_key(std::string data, Key_t key);
	virtual Container* add_container_with_key(std::string type, Key_t key, int id);
	virtual void add_integer(int data);
	virtual void add_string(std::string data);
	virtual Container* add_container(std::string type, int id);
	void delete_included_data();

protected:
	int id;
	std::vector<Data*> included_data;
	
};

class Array : public Container {
public:
	Array(int id_);
	std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info);
	void add_integer(int data);
	void add_string(std::string data);
	Container* add_container(std::string type, int id);
};

class Object : public Container {
public:
	Object(int id_ = 0);
	std::string make_text_to_be_showed(int number_of_tabs_of_line, std::string additional_info);
	void add_integer_with_key(int data, Key_t key);
	void add_string_with_key(std::string data, Key_t key);
	Container* add_container_with_key(std::string type, Key_t key, int id);

private:
	std::vector<Key_t> keys_related_to_included_data;

};

bool is_new_key(const Key_t& new_key, const std::vector<Key_t>& keys);

#endif
