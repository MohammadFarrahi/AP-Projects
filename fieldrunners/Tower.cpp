#include"Tower.hpp"

using namespace std;


Tower::Tower(string type_, money_t build_cost_, money_t upgrade_cost_, blood_t base_damage_amount_,
			int shot_speed_, long timespan_of_shot_making_, MyPoint position_,int current_target_enemy_index_,
			level_t damage_level_, int attack_radius_, int frame_counter_)
			: type(type_), build_cost(build_cost_), upgrade_cost(upgrade_cost_), damage_amount(base_damage_amount_),
			damage_level(damage_level_), radius_of_attack_area(attack_radius_), shot_speed(shot_speed_),
			current_target_enemy_index(current_target_enemy_index_), frame_counter(frame_counter_), tower_shape(type_)
{
	number_of_frames_for_shot_making = timespan_of_shot_making_ / (FRAME_DELAY + AVRAGE_EXECUTION_TIME);
	position = position_;
}

Gatling::Gatling(MyPoint position_, string type_, money_t build_cost_, money_t upgrade_cost_, blood_t base_damage_amount_,
		long timespan_of_shot_making_, int shot_speed_) : Tower(type_, build_cost_, upgrade_cost_, base_damage_amount_,
		shot_speed_, timespan_of_shot_making_, position_) {}

Missile::Missile(MyPoint position_, string type_, money_t build_cost_, money_t upgrade_cost_, blood_t base_damage_amount_,
		long timespan_of_shot_making_, int shot_speed_) : Tower(type_, build_cost_, upgrade_cost_, base_damage_amount_,
		shot_speed_, timespan_of_shot_making_, position_) {}

Tesla::Tesla(MyPoint position_, string type_, money_t build_cost_, money_t upgrade_cost_, blood_t base_damage_amount_,
		long timespan_of_shot_making_, int shot_speed_) : Tower(type_, build_cost_, upgrade_cost_, base_damage_amount_,
		shot_speed_, timespan_of_shot_making_, position_) {}

Glue::Glue(MyPoint position_, pair<int, long> damage_info_, string type_, money_t build_cost_, money_t upgrade_cost_, blood_t base_damage_amount_,
		long timespan_of_shot_making_, int shot_speed_) : Tower(type_, build_cost_, upgrade_cost_, base_damage_amount_,
		shot_speed_, timespan_of_shot_making_, position_)
{
	damage_info = damage_info_;
}

void Tower::display(Window* win){
	tower_shape.display(win, position);
}

money_t Tower::get_upgrade_cost(){ return upgrade_cost; }

bool Tower::upgrade(){

	if(damage_level < LEVEL_THREE){
		damage_level++;
		set_damage_and_type();
		tower_shape.set_owner_type(type);
		return false;
	}
	else{
		return true;
	}
}

MyPoint Tower::get_position(){ return position; }

int Tower::find_closest_enemy(const vector<pair<bool, Enemy*> >& enemys){

	int closest_enemy_index = NONE;
	double distane_to_closest_enemy = ATTACK_RADIUS + 1;
	for(int index = 0; index < enemys.size(); index++){

		if(enemys[index].first == AVAILABLE){

			double distance_to_enemy = distance(position, enemys[index].second->get_position());
			if(distance_to_enemy < distane_to_closest_enemy){

				distane_to_closest_enemy = distance_to_enemy;
				closest_enemy_index = index;
			}
			if(distance_to_enemy == distane_to_closest_enemy){
				closest_enemy_index = enemys[index].second->get_position().x > enemys[closest_enemy_index].second->get_position().x ? index : closest_enemy_index;
			}
		}
	}
	return closest_enemy_index;
}

bool Tower::can_shoot_this_enemy(string enemy_type){ return true; }

bool Gatling::can_shoot_this_enemy(string enemy_type){

	if((enemy_type == enemys_type[stubborn_runner]) && ((type == towers_type[gatling][0]) ||
		(type == towers_type[gatling][1]) || (type == towers_type[gatling][2])))
	{
		return false;
	}
	return true;
}

bool Glue::can_shoot_this_enemy(string enemy_type){

	if((enemy_type == enemys_type[stubborn_runner]) && ((type == towers_type[glue][0]) ||
		(type == towers_type[glue][1]) || (type == towers_type[glue][2])))
	{
		return false;
	}
	return true;
}

void Gatling::set_damage_and_type(){

	type = towers_type[gatling][damage_level];
	damage_amount += damage_level * upgraded_towers_damage_increase[gatling];
}

void Missile::set_damage_and_type(){

	type = towers_type[missile][damage_level];
	damage_amount += damage_level * upgraded_towers_damage_increase[missile];
}

void Tesla::set_damage_and_type(){

	type = towers_type[tesla][damage_level];
	damage_amount += damage_level * upgraded_towers_damage_increase[tesla];
}

void Glue::set_damage_and_type(){

	type = towers_type[glue][damage_level];
	damage_info = make_pair(damage_info.first + damage_level * UPGRADED_GLUE_DAMAGE_PERCENTAGE_INCREASE,
							damage_info.second + damage_level * UPGRADED_GLUE_DAMAGE_TIME_INCREASE);
}

Shot* Tower::shooting_process(vector<pair<bool, Enemy*> >& enemys){

	if(current_target_enemy_index == NONE || enemys[current_target_enemy_index].first == NOT_AVAILABLE ||
		distance(position, enemys[current_target_enemy_index].second->get_position()) > ATTACK_RADIUS)
	{
		current_target_enemy_index = find_closest_enemy(enemys);
		if(current_target_enemy_index != NONE){
			if(!can_shoot_this_enemy(enemys[current_target_enemy_index].second->get_type())){
				current_target_enemy_index = NONE;
				return NULL;
			}
		}
		else{
		return NULL;
		}
	}
	frame_counter = START;
	tower_shape.set_image_name(enemys[current_target_enemy_index].second->get_position(), position);
	return new Shot(type, position, shot_speed, enemys[current_target_enemy_index], damage_level, damage_amount);
}

Shot* Glue::shooting_process(std::vector<std::pair<bool, Enemy*> >& enemys){
	
		if(current_target_enemy_index == NONE || enemys[current_target_enemy_index].first == NOT_AVAILABLE ||
		distance(position, enemys[current_target_enemy_index].second->get_position()) > ATTACK_RADIUS)
	{
		current_target_enemy_index = find_closest_enemy(enemys);
		if(current_target_enemy_index != NONE){
			if(!can_shoot_this_enemy(enemys[current_target_enemy_index].second->get_type())){
				current_target_enemy_index = NONE;
				return NULL;
			}
		}
		else{
		return NULL;
		}
	}
	frame_counter = START;
	tower_shape.set_image_name(enemys[current_target_enemy_index].second->get_position(), position);
	return new GlueShot(type, position, shot_speed, enemys[current_target_enemy_index], damage_level,
							damage_info.first, damage_info.second);
}

bool Tower::is_able_to_shoot(){
	return !(is_in_time_period(frame_counter, number_of_frames_for_shot_making));
}
