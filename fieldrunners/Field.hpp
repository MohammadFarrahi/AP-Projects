#ifndef FIELD_HPP
#define FIELD_HPP "FIELD_HPP"

#include"./src/rsdl.hpp"
#include"Movement.hpp"
#include"Enemy.hpp"
#include"Shot.hpp"
#include"Tower.hpp"
#include<vector>
#include<utility>


class Field {
public:
	Field();
	bool is_game_finished();
	bool update_current_wave_state();
	void update_towers_state();
	void update_shots_state();
	void reset_user_related_variables();
	money_t get_total_user_cost();
	blood_t get_total_user_health_damage();
	void process_user_request(std::pair<money_t, std::pair<Point, char> > user_request);
	std::pair<std::pair<int, char>, MyPoint> set_wave_movment_orders(std::vector<std::pair<std::pair<int, char>, MyPoint> > move_orders_);
	void add_wave(std::vector<std::pair<bool, Enemy*> > new_wave);
	void display(Window* window);
	void process_exiting_game();

private:
	std::vector<std::pair<std::pair<int, char>, MyPoint> > wave_movement_orders;
	std::vector<std::vector<std::pair<bool, Enemy*> > > waves_of_enemys;
	std::vector<Tower*> towers;
	std::vector<std::pair<bool, Shot*> > shots;
	money_t total_user_cost;
	blood_t total_user_health_damage;
	int frame_counter_of_wave_appear;
	int current_moving_wave_index;

	int get_tower_index_in_this_position(MyPoint new_position);
	void update_enemy_state(int index);
	bool is_position_on_enemys_move(MyPoint pos);
	void process_tower_related_request(char tower_type, money_t user_money, MyPoint tower_position, std::pair<bool, int> position_permission);
	void process_upgrade_tower(money_t user_money, int tower_index);
	void shot_hitting_process(int index);
	void show_waves_move_path(Window* win);
};

bool is_position_inside_field(MyPoint pos);

#endif
