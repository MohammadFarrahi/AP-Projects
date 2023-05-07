#ifndef JSON_BUILDER_HPP
#define JSON_BUILDER_HPP "JSON_BUILDER_HPP"

#include<string>
#include<vector>
#include"Exception.hpp"
#include"Data.hpp"
#include"Container.hpp"


class JsonBuilder{
public:
	JsonBuilder();
    void addStringToObject(int parent_id, Key_t key, std::string value);
    void addIntegerToObject(int parent_id, Key_t key, int value);
    int addContainerToObject(int parent_id, Key_t key, std::string type);
    void addStringToArray(int parent_id, std::string value);
    void addIntegerToArray(int parent_id, int value);
    int addContainerToArray(int parent_id, std::string type);
    void print(int id);

private:
	std::vector<Container*> built_containers;
	int last_built_container_id;
};

#endif 