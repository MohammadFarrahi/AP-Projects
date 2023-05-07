#include"Field.hpp"
#include<stdexcept>

#define GATLING_REQUEST 'g'
#define	MISSILE_REQUEST 'm'
#define TESLA_REQUEST 't'
#define GLUE_REQUEST 'l'
#define UPGRADE_REQUEST 'u'
#define EXIT 'q'
#define NO_REQUEST '0'

#define ONE_SECOND 1000
#define AVRAGE_EXECUTION_TIME 0
#define FRAME_DELAY 10
#define NUMBER_OF_WAVE_APPEAR_FRAMES  3 * ONE_SECOND / (AVRAGE_EXECUTION_TIME + FRAME_DELAY)
#define NUMBER_OF_ENEMY_APPEAR_FRAMES 500 / (AVRAGE_EXECUTION_TIME + FRAME_DELAY)

#define ARIVED true
#define INVALID -1

using namespace std;


bool Field::is_game_finished(){
	
	if((current_moving_wave_index + 1) >= (int)waves_of_enemys.size()){
		return true;
	}
	current_moving_wave_index++;
	return false;
}

void Field::show_waves_move_path(Window* win){

	for(int i = 0; i < wave_movement_orders.size(); i++){

		int x = wave_movement_orders[i].second.x - field_cordinate_info.cell_edge / 2 + 5;
		int y = wave_movement_orders[i].second.y - field_cordinate_info.cell_edge / 2 + 5;
		win->draw_rect(Rectangle(Point(x, y), field_cordinate_info.cell_edge - 10, field_cordinate_info.cell_edge - 10), RED, 1);
	}
}

void Field::display(Window* window){

	show_waves_move_path(window);
	for(pair<bool, Enemy*> enemy_to_be_showed : waves_of_enemys[current_moving_wave_index]){

		if(enemy_to_be_showed.first == AVAILABLE){
			enemy_to_be_showed.second->display(window);
		}
	}
	for(Tower* tower : towers){
		tower->display(window);
	}
	for(pair<bool, Shot*> shot : shots){
		if(shot.first == AVAILABLE){
			shot.second->display(window);
		}
	}
}

void Field::update_enemy_state(int index){

	Enemy* enemy_to_be_updated = waves_of_enemys[current_moving_wave_index][index].second;
	if(enemy_to_be_updated->is_arived_destination()){

		int last_move_order_index = enemy_to_be_updated->get_last_move_order_index();
		if(last_move_order_index < (int)wave_movement_orders.size() - 1){
			enemy_to_be_updated->set_move_order(wave_movement_orders[last_move_order_index + 1]);
		}
		else{
			waves_of_enemys[current_moving_wave_index][index].first = NOT_AVAILABLE;
			total_user_health_damage += enemy_to_be_updated->get_user_damage_amount();
			delete enemy_to_be_updated;
		}
	}
}

bool Field::update_current_wave_state(){

	bool is_current_wave_dead = true;
	static int frame_counter_of_enemy_appear = FINISHED;
	static int last_appeared_enemy_in_wave_index = INVALID;

	if(!is_in_time_period(frame_counter_of_wave_appear, NUMBER_OF_WAVE_APPEAR_FRAMES) && (waves_of_enemys.size() != 0)){

		if((last_appeared_enemy_in_wave_index < (int)waves_of_enemys[current_moving_wave_index].size() - 1) &&
			!is_in_time_period(frame_counter_of_enemy_appear, NUMBER_OF_ENEMY_APPEAR_FRAMES))
		{
			last_appeared_enemy_in_wave_index++;
			waves_of_enemys[current_moving_wave_index][last_appeared_enemy_in_wave_index].first = AVAILABLE;
			frame_counter_of_enemy_appear = START;
		
		}
		for(int i = 0; i <= last_appeared_enemy_in_wave_index; i++){

			if(waves_of_enemys[current_moving_wave_index][i].first == AVAILABLE){

				is_current_wave_dead = false;
				update_enemy_state(i);
			}
		}
		if(is_current_wave_dead == true){

			frame_counter_of_wave_appear = START;
			frame_counter_of_enemy_appear = FINISHED;
			last_appeared_enemy_in_wave_index = INVALID;
		}
		return is_current_wave_dead;
	}
	else{
		if(waves_of_enemys.size() == 0){
			return true;
		}
		return false;
	}
}

void Field::update_towers_state(){

	for(int i = 0; i < towers.size(); i++){

		if(towers[i]->is_able_to_shoot()){

			Shot* new_shot = towers[i]->shooting_process(waves_of_enemys[current_moving_wave_index]);
			if(new_shot != NULL){
				shots.push_back({AVAILABLE, new_shot});
			}
		}
	}
}

void Field::shot_hitting_process(int index){

	GlueShot* glue_shot_ptr = dynamic_cast<GlueShot*>(shots[index].second);
	if(glue_shot_ptr != NULL){
		glue_shot_ptr->damaging_process(waves_of_enemys[current_moving_wave_index]);
		delete glue_shot_ptr;
		shots[index].first = NOT_AVAILABLE;
	}
	else{
		MissileShot* missile_shot_ptr = dynamic_cast<MissileShot*>(shots[index].second);
		if(missile_shot_ptr != NULL){
			total_user_cost -= missile_shot_ptr->damaging_process(waves_of_enemys[current_moving_wave_index]);
			delete missile_shot_ptr;
			shots[index].first = NOT_AVAILABLE;
		}
		else{
			total_user_cost -= shots[index].second->damaging_process();
			delete shots[index].second;
			shots[index].first = NOT_AVAILABLE;
		}
	}
}

void Field::update_shots_state(){

	for(int i = 0; i < shots.size(); i++){

		if(shots[i].first == AVAILABLE){
			if(shots[i].second->follow_target() == ARIVED){
				shot_hitting_process(i);
			}
		}
	}
}

void Field::reset_user_related_variables(){

	total_user_cost = 0;
	total_user_health_damage = 0;
}

money_t Field::get_total_user_cost(){ return total_user_cost; }

blood_t Field::get_total_user_health_damage(){ return total_user_health_damage; }

Field::Field() : total_user_cost(0), total_user_health_damage(0), frame_counter_of_wave_appear(FINISHED), current_moving_wave_index(0) {}

void Field::process_user_request(pair<money_t, pair<Point, char> > user_request){

	char request_type = user_request.second.second;
	if(request_type == EXIT){
		process_exiting_game();
		throw runtime_error("Exiting...\n");
	}
	pair<int, int> field_cell_clicked_by_mouse = get_cell_cover_position({(double)user_request.second.first.x, (double)user_request.second.first.y});
	MyPoint new_position = get_middle_of_cell(field_cell_clicked_by_mouse);
	if(!is_position_inside_field(new_position)){
		cerr << "Selected positon is outside of field!\n\n";
		return;
	}
	pair<bool, int> position_permission(is_position_on_enemys_move(new_position), get_tower_index_in_this_position(new_position));
	try{
		process_tower_related_request(request_type, user_request.first, new_position, position_permission);
	}
	catch(string& error_description){
		cerr << error_description << endl;
	}
}

pair<pair<int, char>, MyPoint> Field::set_wave_movment_orders(vector<pair<pair<int, char>, MyPoint> > move_orders_){
	
	wave_movement_orders = move_orders_;
	return wave_movement_orders[0];
}

bool Field::is_position_on_enemys_move(MyPoint pos){

	for(int i = 0; i < wave_movement_orders.size(); i++){

		if((abs(wave_movement_orders[i].second.x - pos.x) <= 1) && (abs(wave_movement_orders[i].second.y - pos.y) <= 1)){
			return true;
		}
	}
	return false;
}

void Field::process_tower_related_request(char request, money_t user_money, MyPoint position, pair<bool, int> position_permission){

	switch(request){

		case GATLING_REQUEST :{
			if(position_permission.first == true || position_permission.second != INVALID){
				throw string("You can't build tower in this cell!\n");
			}
			if(towers_build_cost[gatling] > user_money){
				throw string("More money is needed for building!\n"); 
			}
			towers.push_back(new Gatling(position));
			total_user_cost += towers_build_cost[gatling];
			break;
		}
		case MISSILE_REQUEST :{
			if(position_permission.first == true || position_permission.second != INVALID){
				throw string("You can't build tower in this cell!\n");
			}
			if(towers_build_cost[missile] > user_money){
				throw string("More money is needed for building!\n"); 
			}
			towers.push_back(new Missile(position));
			total_user_cost += towers_build_cost[missile];
			break;
		}
		case TESLA_REQUEST :{
			if(position_permission.first == true || position_permission.second != INVALID){
				throw string("You can't build tower in this cell!\n");
			}
			if(towers_build_cost[tesla] > user_money){
				throw string("More money is needed for building!\n"); 
			}
			towers.push_back(new Tesla(position));
			total_user_cost += towers_build_cost[tesla];
			break;
		}
		case GLUE_REQUEST :{
			if(position_permission.first == true || position_permission.second != INVALID){
				throw string("You can't build tower in this cell!\n");
			}
			if(towers_build_cost[glue] > user_money){
				throw string("More money is needed for building!\n"); 
			}
			towers.push_back(new Glue(position));
			total_user_cost += towers_build_cost[glue];
			break;
		}
		case UPGRADE_REQUEST :{
			process_upgrade_tower(user_money, position_permission.second);
			break;
		}
		default :{
			throw string("Undefined request!\n");
			break;
		}
	}
}

int Field::get_tower_index_in_this_position(MyPoint new_position){

	for(int i = 0; i < towers.size(); i++){

		if((abs(towers[i]->get_position().x - new_position.x) <= 1) && (abs(towers[i]->get_position().y - new_position.y) <= 1)){
			return i;
		}
	}
	return INVALID;
}

void Field::process_upgrade_tower(money_t user_money, int tower_index){

	if(tower_index == INVALID){
		throw string("There is no tower to upgrde in selected position!\n");
	}
	if(towers[tower_index]->get_upgrade_cost() <= user_money){

		bool is_last_level = towers[tower_index]->upgrade();
		if(!is_last_level){
			total_user_cost += towers[tower_index]->get_upgrade_cost();
		}
		return;
	}
	else{
		throw string("For upgrade selected tower, more money is needed!\n");
	}
}

void Field::process_exiting_game(){

	for(int i = 0; i < waves_of_enemys.size(); i++){

		for(int j = 0; j < waves_of_enemys[i].size(); j++){

			if(waves_of_enemys[i][j].first == AVAILABLE){
				delete waves_of_enemys[i][j].second;
			}
		}
	}
	for(Tower* tower : towers){
		delete tower;
	}
	for(pair<bool, Shot*> shot : shots){

		if(shot.first == AVAILABLE){
			delete shot.second;
		}		
	}
}

void Field::add_wave(vector<pair<bool, Enemy*> > new_wave){
	
	if(new_wave.size() != 0){
		waves_of_enemys.push_back(new_wave);
	}
}

bool is_position_inside_field(MyPoint pos){

	if(field_cordinate_info.top_left.first <= pos.x <= field_cordinate_info.bottom_right.first &&
		field_cordinate_info.top_left.second <= pos.y <= field_cordinate_info.bottom_right.second)
	{
		return true;
	}
	return false;
}
