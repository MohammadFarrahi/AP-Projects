#ifndef TOWER_HPP
#define TOWER_HPP "TOWER_HPP"

#include"./src/rsdl.hpp"
#include"Movement.hpp"
#include"Shape.hpp"
#include"Enemy.hpp"
#include"Shot.hpp"
#include<vector>
#include<utility>
#include<string>

#define ONE_SECOND 1000
#define AVRAGE_EXECUTION_TIME 0
#define FRAME_DELAY 10
#define START 0
#define FINISHED -1

#define LEVEL_ONE 0
#define LEVEL_TWO 1
#define LEVEL_THREE 2
#define ATTACK_RADIUS 150
#define NONE -1

#define GLUE_BASE_DAMAGE_PERCENTAGE 40
#define GLUE_BASE_DAMAGE_TIME 2500
#define UPGRADED_GLUE_DAMAGE_PERCENTAGE_INCREASE 10
#define UPGRADED_GLUE_DAMAGE_TIME_INCREASE 500

const std::vector<money_t> towers_build_cost = {55, 70, 120, 60};
const std::vector<money_t> towers_upgrade_cost = {40, 60, 100, 45};
const std::vector<long> shot_timer_of_towers = {1000, 3000, 1500, 2000};
const std::vector<blood_t> towers_base_damage = {35, 75, 700, 0};
const std::vector<blood_t> upgraded_towers_damage_increase = {35, 75, 1000};
const std::vector<int> towers_shot_speed = {120, 140, 120, 140};


class Tower {
public:
	Tower(std::string type_, money_t build_cost_, money_t upgrade_cost, blood_t base_damage_amount_, int shot_speed_,
			long timespan_of_shot_making_, MyPoint position_, int current_target_enemy_index_ = NONE,
			level_t damage_level_ = LEVEL_ONE, int attack_radius_ = ATTACK_RADIUS, int frame_counter_ = FINISHED);
	bool upgrade();
	money_t get_upgrade_cost();
	virtual Shot* shooting_process(std::vector<std::pair<bool, Enemy*> >& enemys);
	bool is_able_to_shoot();
	MyPoint get_position();
	void display(Window* win);

protected:
	std::string type;
	money_t build_cost;
	money_t upgrade_cost;
	level_t damage_level;
	blood_t damage_amount;
	long number_of_frames_for_shot_making;
	int frame_counter;
	MyPoint position;
	int radius_of_attack_area;
	int shot_speed;
	int current_target_enemy_index;
	TowerShape tower_shape;

	int find_closest_enemy(const std::vector<std::pair<bool, Enemy*> >& enemys);
	
private:
	virtual bool can_shoot_this_enemy(std::string);
	virtual void set_damage_and_type() = 0;
};

class Gatling : public Tower {
public:
	Gatling(MyPoint position_, std::string type_ = towers_type[gatling][LEVEL_ONE], money_t build_cost_ = towers_build_cost[gatling],
			money_t upgrade_cost = towers_upgrade_cost[gatling], blood_t base_damage_amount_ = towers_base_damage[gatling],
			long timespan_of_shot_making_ = shot_timer_of_towers [gatling], int shot_speed_ = towers_shot_speed[gatling]);

private:
	void set_damage_and_type();
	virtual bool can_shoot_this_enemy(std::string);
};

class Missile : public Tower {
public:
	Missile(MyPoint position_, std::string type_ = towers_type[missile][LEVEL_ONE], money_t build_cost_ = towers_build_cost[missile],
			money_t upgrade_cost = towers_upgrade_cost[missile], blood_t base_damage_amount_ = towers_base_damage[missile],
			long timespan_of_shot_making_ = shot_timer_of_towers [missile], int shot_speed_ = towers_shot_speed[missile]);
	
	
private:
	void set_damage_and_type();
};

class Tesla : public Tower {
public:
	Tesla(MyPoint position_, std::string type_ = towers_type[tesla][LEVEL_ONE], money_t build_cost_ = towers_build_cost[tesla],
		money_t upgrade_cost = towers_upgrade_cost[tesla], blood_t base_damage_amount_ = towers_base_damage[tesla],
		long timespan_of_shot_making_ = shot_timer_of_towers [tesla], int shot_speed_ = towers_shot_speed[tesla]);

private:
	void set_damage_and_type();
};

class Glue : public Tower {
public:
	Glue(MyPoint position_, std::pair<int, long> damage_info_ = {GLUE_BASE_DAMAGE_PERCENTAGE, GLUE_BASE_DAMAGE_TIME},
		std::string type_ = towers_type[glue][LEVEL_ONE], money_t build_cost_ = towers_build_cost[glue],
		money_t upgrade_cost = towers_upgrade_cost[glue], blood_t base_damage_amount_ = towers_base_damage[glue],
		long timespan_of_shot_making_ = shot_timer_of_towers [glue], int shot_speed_ = towers_shot_speed[glue]);
	Shot* shooting_process(std::vector<std::pair<bool, Enemy*> >& enemys);

private:
	std::pair<int, long> damage_info;

	void set_damage_and_type();
	virtual bool can_shoot_this_enemy(std::string);
};

#endif
