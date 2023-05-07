#ifndef SHAPE_HPP
#define SHAPE_HPP "SHAPE_HPP"

#include<string>
#include<utility>
#include<vector>
#include"Movement.hpp"
#include"./src/rsdl.hpp"

#define GRAY 192

#define HORIZONTAL 'H'
#define VERTICAL 'V'

#define PATH "./Assets/"
#define SUFFIX ".png"

typedef int blood_t;
typedef int money_t;
typedef int level_t;

enum TowerType { gatling, missile, tesla, glue };
enum MoveDirectionIndex { Up, Down, Left, Right };

const std::vector<std::string> move_direction_names = {"up", "down", "left", "right"};

const std::vector<std::vector<std::string> > towers_type = { {"g-1", "g-2", "g-3"}, {"m-1", "m-2", "m-3"},
															{"t-1", "t-2", "t-3"}, {"l-1", "l-2", "l-3"} };


class Shape {
public:
	Shape(std::string owner_type_);
	virtual void set_owner_type(std::string new_type);
	virtual void display(Window* win, MyPoint position);

protected:
	std::string image_name;
	std::string owner_type;
};

class TowerShape : public Shape {
public:
	TowerShape(std::string owner_type_);
	void set_image_name(const MyPoint& enemy_position, const MyPoint& tower_position);
	void display(Window* win, const MyPoint& position);
	void set_owner_type(std::string new_type);

private:
	bool flip_horizontal;
};

class EnemyShape : public Shape {
public:
	EnemyShape(std::string owner_type_, std::pair<int, char> direction);
	void set_image_name(std::pair<int, char> direction);
	void display(Window* win, MyPoint position, blood_t current_health);
	void reset_shape_mood_counter();
	void change_shape_mood();
	void set_full_amount_of_enemy_health(blood_t health);

private:
	bool flip_horizontal;
	double shape_mood_counter;
	blood_t full_amount_of_enemy_health;

	void show_health_amount(Window* win, const MyPoint& position, const blood_t& current_health);
};

class ShotShape : public Shape {
public:
	ShotShape(std::string owner_type_, level_t owner_level_);
	void set_color_of_shot();
	void display(Window* win, MyPoint position);

private:
	level_t owner_level;
	int R, G, B;
};

#endif
