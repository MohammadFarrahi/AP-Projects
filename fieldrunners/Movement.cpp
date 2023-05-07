#include"Movement.hpp"
#include<cmath>
#include<vector>

using namespace std;


Movement::Movement(MyPoint curr_pos_, MyPoint dest_pos_,int speed_per_second_){

	current_position = curr_pos_;
	set_destination(dest_pos_);
	movement_per_delay = (double)speed_per_second_ * (FRAME_DELAY + AVRAGE_EXECUTION_TIME) / ONE_SECOND;
}

void Movement::set_direction(){}

MyPoint Movement::get_curr_position() const{ return current_position; }

void Movement::set_destination(MyPoint dest_pos){ destination_position = dest_pos; }

bool Movement::is_arived(){

	if( abs(current_position.x - destination_position.x) <= 2 &&
		abs(current_position.y - destination_position.y) <= 2)
	{
		current_position = destination_position;
		return true;
	}
	return false;
}

void Movement::set_speed(double new_speed_per_second){
	movement_per_delay = new_speed_per_second * (FRAME_DELAY + AVRAGE_EXECUTION_TIME) / ONE_SECOND;
}

void EnemyMovement::change_speed_by_percentage(int percentage){
	set_speed(base_speed_per_second * (100 + percentage) / 100);
}

EnemyMovement::EnemyMovement(MyPoint curr_pos_, MyPoint dest_pos_, int speed_per_second_, pair<int, char> direction_, int last_move_order_index_)
						: Movement(curr_pos_, dest_pos_, speed_per_second_), last_move_order_index(last_move_order_index_),
							base_speed_per_second(speed_per_second_)
{
	set_direction(direction_);
}

int EnemyMovement::get_last_move_order() { return last_move_order_index; }

void EnemyMovement::move(){

	if(direction.second == VERTICAL){
		current_position.y += movement_per_delay * direction.first; 
	}
	else{
		current_position.x += movement_per_delay * direction.first;
	}
}

void EnemyMovement::set_direction(pair<int, char> direction_){

	direction = direction_;
	last_move_order_index++;
}

ShotMovement::ShotMovement(MyPoint curr_pos_, MyPoint dest_pos_,int speed_per_second_)
						: Movement(curr_pos_, dest_pos_, speed_per_second_)
{
	set_direction();
}

void ShotMovement::move(){

	current_position.x += movement_per_delay * direction.cos_teta;
	current_position.y += movement_per_delay * direction.sin_teta;
}

void ShotMovement::set_direction(){

	double distance_to_dest = distance(current_position, destination_position);
	direction.sin_teta = (destination_position.y - current_position.y) / distance_to_dest;
	direction.cos_teta = (destination_position.x - current_position.x) / distance_to_dest;
}

double distance(MyPoint pos1, MyPoint pos2){
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

pair<int, int> get_cell_cover_position(MyPoint pos){

	for(int i = 0; i <= field_cordinate_info.horizontal_edges; i++){

		for(int j = 0; j <= field_cordinate_info.vertical_edges; j++){

			if(field_cordinate_info.top_left.first + i * field_cordinate_info.cell_edge <= pos.x &&
				field_cordinate_info.top_left.first + (i + 1) * field_cordinate_info.cell_edge >= pos.x){

				if(field_cordinate_info.top_left.second + j * field_cordinate_info.cell_edge <= pos.y &&
					field_cordinate_info.top_left.second + (j + 1) * field_cordinate_info.cell_edge >= pos.y){
					return make_pair(i, j);
				}
			}
		}
	}
}

MyPoint get_middle_of_cell(pair<int,int> cell){

	MyPoint position;
	position.x = (field_cordinate_info.top_left.first + cell.first * field_cordinate_info.cell_edge) +
					(field_cordinate_info.top_left.first + (cell.first + 1) * field_cordinate_info.cell_edge);
	position.y = (field_cordinate_info.top_left.second + cell.second * field_cordinate_info.cell_edge) +
					(field_cordinate_info.top_left.second + (cell.second + 1) * field_cordinate_info.cell_edge);
	position.x /= 2; position.y /= 2;
	return position;
}

bool is_in_time_period(int& frame_counter, const long& number_of_frames_in_time_priod){

	if(frame_counter == FINISHED){
		return false;
	}
	frame_counter++;
	if(frame_counter == number_of_frames_in_time_priod){

		frame_counter = FINISHED;
		return false;
	}
	return true;
}
