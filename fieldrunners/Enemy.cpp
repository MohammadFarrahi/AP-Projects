#include"Enemy.hpp"

using namespace std;


blood_t Enemy::get_user_damage_amount(){ return damage_to_user; }

string Enemy::get_type(){ return type; }

Enemy::Enemy (MyPoint starting_position_, pair<pair<int, char>, MyPoint> move_order_, string type_,
				int speed_, money_t kill_price_, blood_t damage_to_user_, GlueShotInfo glue_shot_info_)
		: enemy_movement(starting_position_, move_order_.second, speed_, move_order_.first), type(type_),
		kill_price(kill_price_), damage_to_user(damage_to_user_), glue_shot_info(glue_shot_info_), enemy_shape(type_, move_order_.first){}

void Enemy::display(Window* win){
	enemy_shape.display(win, enemy_movement.get_curr_position(), enemy_health);
}

void Enemy::set_enemy_speed_based_glue_shot_info(){

	int speed_decreaser_percentage = 0;
	int frame_counter_temp = glue_shot_info.frame_counter;
	if(is_in_time_period(frame_counter_temp, glue_shot_info.number_of_glue_affect_frames)){
		speed_decreaser_percentage =  (-glue_shot_info.speed_decreaser);
	}
	else{
		glue_shot_info = default_glue_shot_info;
	}
	enemy_movement.change_speed_by_percentage(speed_decreaser_percentage);
	glue_shot_info.frame_counter = frame_counter_temp;
}

void StubbornRunner::set_glue_shot_info(GlueShotInfo shot_info_){}

bool Enemy::is_arived_destination(){

	set_enemy_speed_based_glue_shot_info();
	enemy_movement.move();
	enemy_shape.change_shape_mood();
	return enemy_movement.is_arived();
}

void Enemy::set_glue_shot_info(GlueShotInfo shot_info_){ glue_shot_info = shot_info_; }

GlueShotInfo Enemy::get_glue_shot_info(){ return glue_shot_info; }

money_t Enemy::get_shot_damage_effect(blood_t shot_damage){
	
	enemy_health -= shot_damage;
	if(enemy_health <= 0){
		return kill_price;
	}
	return 0;	
}

MyPoint Enemy::get_position() const{ return enemy_movement.get_curr_position(); }

int Enemy::get_last_move_order_index(){ return enemy_movement.get_last_move_order(); }

void Enemy::set_move_order(pair<pair<int, char>, MyPoint> move_order){

	enemy_movement.set_destination(move_order.second);
	enemy_movement.set_direction(move_order.first);
	enemy_shape.set_image_name(move_order.first);
	enemy_shape.reset_shape_mood_counter();
}

Runner::Runner(MyPoint position_, pair<pair<int, char>, MyPoint> move_order_, int health_maker_, string type_,
				int speed_, money_t kill_price_, blood_t damage_to_user_)
		: Enemy(position_, move_order_, type_, speed_, kill_price_, damage_to_user_)
{
	set_health(health_maker_);
	enemy_shape.set_full_amount_of_enemy_health(enemy_health);
}

void Runner::set_health(int health_maker){ enemy_health = (0.9 + 0.1 * health_maker) * enemys_base_health[runner]; }

StubbornRunner::StubbornRunner(MyPoint position_, pair<pair<int, char>, MyPoint> move_order_, int health_maker_, string type_,
								int speed_, money_t kill_price_, blood_t damage_to_user_)
				: Enemy(position_, move_order_, type_, speed_, kill_price_, damage_to_user_)
{
	set_health(health_maker_);
	enemy_shape.set_full_amount_of_enemy_health(enemy_health);
}

void StubbornRunner::set_health(int health_maker){ enemy_health = (0.9 + 0.1 * health_maker) * enemys_base_health[stubborn_runner]; }

SuperTrooper::SuperTrooper(MyPoint position_, pair<pair<int, char>, MyPoint> move_order_, int health_maker_, string type_,
							int speed_, money_t kill_price_, blood_t damage_to_user_)
			: Enemy(position_, move_order_, type_, speed_, kill_price_, damage_to_user_)
{
	set_health(health_maker_);
	enemy_shape.set_full_amount_of_enemy_health(enemy_health);
}

void SuperTrooper::set_health(int health_maker){ enemy_health = (0.9 + 0.1 * health_maker) * enemys_base_health[super_trooper]; }

Scrambler::Scrambler(MyPoint position_, pair<pair<int, char>, MyPoint> move_order_, int health_maker_, string type_,
						int speed_, money_t kill_price_, blood_t damage_to_user_)
			: Enemy(position_, move_order_, type_, speed_, kill_price_, damage_to_user_)
{
	set_health(health_maker_);
	enemy_shape.set_full_amount_of_enemy_health(enemy_health);
}

void Scrambler::set_health(int health_maker){ enemy_health = (0.9 + 0.1 * health_maker) * enemys_base_health[scrambler]; }
