#include"Shot.hpp"

using namespace std;


Shot::Shot(string type_, MyPoint starting_pos_, int speed_, pair<bool, Enemy*>& target_enemy_, level_t damage_level_,
	blood_t damage_power_)	: shot_movement(starting_pos_, target_enemy_.second->get_position(), speed_), type(type_),
		target_enemy(target_enemy_), damage_power(damage_power_), shot_shape(type_, damage_level_) {}

void Shot::display(Window* win){
	shot_shape.display(win, shot_movement.get_curr_position());
}

bool Shot::follow_target(){

	if(shot_movement.is_arived()){
		return true;
	}
	if(target_enemy.first == AVAILABLE){
		
		shot_movement.set_destination(target_enemy.second->get_position());
		shot_movement.set_direction();
	}
	shot_movement.move();
	if(shot_movement.is_arived()){
		return true;
	}
	return false;
}

money_t Shot::damaging_process(){

	money_t kill_price = 0;
	if(target_enemy.first == NOT_AVAILABLE){
		return kill_price;
	}
	kill_price = target_enemy.second->get_shot_damage_effect(damage_power);
	if(kill_price != 0){
		
		target_enemy.first = NOT_AVAILABLE;
		delete target_enemy.second;
	}
	return kill_price;
}

MissileShot::MissileShot(string type_, MyPoint starting_pos_, int speed_, pair<bool, Enemy*>& target_enemy_, level_t damage_level_,
						blood_t damage_power_, int effect_area_radius_)
			: Shot(type_, starting_pos_, speed_, target_enemy_, damage_level_, damage_power_), effect_area_radius(effect_area_radius_) {}

GlueShot::GlueShot(string type_, MyPoint starting_pos_, int speed_, pair<bool, Enemy*>& target_enemy_,
					level_t damage_level_, int speed_decreaser_, long glue_affect_time_period_, int effect_area_radius_)
		: Shot(type_, starting_pos_, speed_, target_enemy_, damage_level_), speed_decreaser(speed_decreaser_), effect_area_radius(effect_area_radius_)
{
	number_of_glue_affect_frames = (double)glue_affect_time_period_ / (FRAME_DELAY + AVRAGE_EXECUTION_TIME);
	damage_level = damage_level_;
}

vector<int> find_close_enemys(vector<pair<bool, Enemy*> >& enemys, MyPoint from_pos, int radius){

	vector<int> close_enemys_index;
	for(int i = 0; i < enemys.size(); i++){

		if(enemys[i].first == AVAILABLE){

			if(distance(from_pos, enemys[i].second->get_position()) <= radius){
				close_enemys_index.push_back(i);
			}
		}
	}
	return close_enemys_index;
}

money_t MissileShot::damaging_process(vector<pair<bool, Enemy*> >& enemys){

	money_t total_kill_price = 0;
	vector<int> enemys_index = find_close_enemys(enemys, shot_movement.get_curr_position(), effect_area_radius);
	for(int i = 0; i < enemys_index.size(); i++){

		money_t kill_price = 0;
		kill_price = enemys[enemys_index[i]].second->get_shot_damage_effect(damage_power);
		if(kill_price != 0){
		
			enemys[enemys_index[i]].first = NOT_AVAILABLE;
			delete enemys[enemys_index[i]].second;
			total_kill_price += kill_price;
		}
	}
	return total_kill_price;
}

void GlueShot::damaging_process(vector<pair<bool, Enemy*> >& enemys){

	vector<int> enemys_index = find_close_enemys(enemys, shot_movement.get_curr_position(), effect_area_radius);
	for(int i = 0; i < enemys_index.size(); i++){
		
		GlueShotInfo glue_shot_info = enemys[enemys_index[i]].second->get_glue_shot_info();
		if(glue_shot_info.frame_counter <= 0){

			if(glue_shot_info.shot_level < damage_level){

				glue_shot_info.shot_level = damage_level;
				glue_shot_info.speed_decreaser = speed_decreaser;
				glue_shot_info.number_of_glue_affect_frames = number_of_glue_affect_frames;
				glue_shot_info.frame_counter = START;
				enemys[enemys_index[i]].second->set_glue_shot_info(glue_shot_info);
			}
		}
	}
}
