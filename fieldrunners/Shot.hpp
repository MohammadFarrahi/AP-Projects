#ifndef SHOT_HPP
#define SHOT_HPP "SHOT_HPP"

#include<string>
#include<utility>
#include<vector>
#include"Shape.hpp"
#include"Movement.hpp"
#include"Enemy.hpp"
#include"./src/rsdl.hpp"

#define GLUE_EFFECT_AREA_RADIUS 30
#define MISSILE_EFFECT_AREA_RADIUS 50


class Shot {
public:
	Shot(std::string type_, MyPoint starting_pos_, int speed_, std::pair<bool, Enemy*>& target_enemy_,level_t damage_level_, blood_t damage_power_ = 0);
	bool follow_target();
	virtual money_t damaging_process();
	void display(Window* win);

protected:
	std::string type;
	std::pair <bool, Enemy*>& target_enemy;
	blood_t damage_power;
	ShotMovement shot_movement;
	ShotShape shot_shape;
};

class MissileShot : public Shot {
public:
	MissileShot(std::string type_, MyPoint starting_pos_, int speed_, std::pair<bool, Enemy*>& target_enemy_, level_t damage_level,
				blood_t damage_power_, int effect_area_radius_ = MISSILE_EFFECT_AREA_RADIUS);
	money_t damaging_process(std::vector<std::pair<bool, Enemy*> >& enemys);

private:
	int effect_area_radius;
};

class GlueShot : public Shot {
public:
	GlueShot(std::string type_, MyPoint starting_pos_, int speed_, std::pair<bool, Enemy*>& target_enemy_, level_t damage_level_,
			int speed_decreaser_, long glue_affect_time_period_, int effect_area_radius_ = GLUE_EFFECT_AREA_RADIUS);
	void damaging_process(std::vector<std::pair<bool, Enemy*> >& enemys);

private:
	level_t damage_level;
	int speed_decreaser;
	long number_of_glue_affect_frames;
	int effect_area_radius;
};

std::vector<int> find_close_enemys(std::vector<std::pair<bool, Enemy*> >& enemys, MyPoint from_pos, int radius);

#endif