#ifndef MOVE_HPP
#define MOVE_HPP "MOVE_HPP"

#include"./src/rsdl.hpp"
#include<utility>

#define ONE_SECOND 1000
#define AVRAGE_EXECUTION_TIME 0
#define FRAME_DELAY 10
#define START 0
#define FINISHED -1

#define HORIZONTAL 'H'
#define VERTICAL 'V'


struct FieldCordinateInfo{
std::pair<float, float> top_left;
std::pair<float, float> bottom_right;
int cell_edge;
int vertical_edges;
int horizontal_edges;
};

struct MyPoint {
double x;
double y;
};

struct PolarDirection {
double sin_teta;
double cos_teta;
};

const FieldCordinateInfo field_cordinate_info = 
{
	{120, 175}, {1260, 835}, 60, 11, 19
};



class Movement {
public:
	Movement(MyPoint curr_pos_, MyPoint dest_pos_, int speed_per_second_);
	virtual void move() = 0;
	bool is_arived();
	void set_direction();
	void set_destination(MyPoint dest_pos);
	void set_speed(double new_speed_per_second);
	MyPoint get_curr_position() const;

protected:
	MyPoint current_position;
	MyPoint destination_position;
	double movement_per_delay;
};

class EnemyMovement : public Movement {
public:
	EnemyMovement(MyPoint curr_pos_, MyPoint dest_pos_, int speed_per_second_, std::pair<int, char> direction_, int last_move_order_index_ = -1);
	void move();
	void set_direction(std::pair<int, char> direction_);
	int get_last_move_order();
	void change_speed_by_percentage(int percentage);
	
private:
	std::pair<int, char> direction;
	int last_move_order_index;
	int base_speed_per_second;

};

class ShotMovement : public Movement {
public:
	ShotMovement(MyPoint curr_pos_, MyPoint dest_pos_,int speed_per_second_);
	void move();
	void set_direction();

private:
	PolarDirection direction;
};

double distance(MyPoint pos1, MyPoint pos2);
std::pair<int, int> get_cell_cover_position(MyPoint pos);
MyPoint get_middle_of_cell(std::pair<int,int> cell);
bool is_in_time_period(int& frame_counter, const long& number_of_frames_in_time_priod);

#endif
