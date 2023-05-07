#ifndef ENEMY_HPP
#define ENEMY_HPP "ENEMY_HPP"

#include"Shape.hpp"
#include"Movement.hpp"
#include"./src/rsdl.hpp"
#include<string>
#include<utility>
#include<vector>

#define NOT_AVAILABLE false
#define AVAILABLE true
#define NUMBER_OF_ENEMY_TYPES 4

enum EnemyType { runner, stubborn_runner, super_trooper, scrambler };

struct GlueShotInfo {
level_t shot_level;
int speed_decreaser;
long number_of_glue_affect_frames;
long frame_counter;
};

const GlueShotInfo default_glue_shot_info = {-1, 0, 0, -1};
const std::vector<blood_t> enemys_base_health = {250, 400, 500, 100};
const std::vector<blood_t> enemys_damage = {1, 4, 4, 2};
const std::vector<int> enemys_speed = {50, 30, 25, 90};
const std::vector<money_t> enemys_kill_price = {6, 10, 8, 4};
const std::vector<std::string> enemys_type = {"runner", "stubbornrunner", "supertrooper", "scrambler"};


class Enemy {
public:
	Enemy (MyPoint starting_position_, std::pair<std::pair<int, char>, MyPoint> move_order_, std::string type_, int speed_,
			 money_t kill_price_, blood_t damage_to_user_, GlueShotInfo glue_shot_info_ = default_glue_shot_info);
	bool is_arived_destination();
	virtual void set_glue_shot_info(GlueShotInfo shot_info_);
	GlueShotInfo get_glue_shot_info();
	money_t get_shot_damage_effect(blood_t shot_damage);
	MyPoint get_position() const;
	int get_last_move_order_index();
	void set_move_order(std::pair<std::pair<int, char>, MyPoint> move_order);
	std::string get_type();
	blood_t get_user_damage_amount();
	void display(Window* win);

protected:
	std::string type;
	blood_t enemy_health;
	EnemyMovement enemy_movement;
	money_t kill_price;
	blood_t damage_to_user;
	GlueShotInfo glue_shot_info;
	EnemyShape enemy_shape;

private:
	virtual void set_health(int wave_number) = 0;
	void set_enemy_speed_based_glue_shot_info();
};

class Runner : public Enemy {
public:
	Runner(MyPoint position_, std::pair<std::pair<int, char>, MyPoint> move_order_, int health_maker_, std::string type_ = enemys_type[runner],
			int speed_ = enemys_speed[runner], money_t kill_price_ = enemys_kill_price[runner], blood_t damage_to_user_ = enemys_damage[runner]);

private:
	void set_health(int wave_number);
};

class StubbornRunner : public Enemy {
public:
	StubbornRunner(MyPoint position_, std::pair<std::pair<int, char>, MyPoint> move_order_, int health_maker_, std::string type_ = enemys_type[stubborn_runner],
					int speed_ = enemys_speed[stubborn_runner], money_t kill_price_ = enemys_kill_price[stubborn_runner], blood_t damage_to_user_ = enemys_damage[stubborn_runner]);
	void set_glue_shot_info(GlueShotInfo shot_info_);

private:
	void set_health(int wave_number);
};

class SuperTrooper : public Enemy {
public:
	SuperTrooper(MyPoint position_, std::pair<std::pair<int, char>, MyPoint> move_order_, int health_maker_, std::string type_ = enemys_type[super_trooper],
				int speed_ = enemys_speed[super_trooper], money_t kill_price_ = enemys_kill_price[super_trooper], blood_t damage_to_user_ = enemys_damage[super_trooper]);

private:
	void set_health(int wave_number);
};

class Scrambler : public Enemy {
public:
	Scrambler(MyPoint position_, std::pair<std::pair<int, char>, MyPoint> move_order_, int health_maker_, std::string type_ = enemys_type[scrambler],
			int speed_ = enemys_speed[scrambler], money_t kill_price_ = enemys_kill_price[scrambler], blood_t damage_to_user_ = enemys_damage[scrambler]);

private:
	void set_health(int wave_number);
};

#endif
