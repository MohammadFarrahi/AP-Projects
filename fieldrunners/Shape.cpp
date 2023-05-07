#include"Shape.hpp"
#include<string>


using namespace std;


Shape::Shape(string owner_type_) : owner_type(owner_type_), image_name(owner_type_) {}

void Shape::set_owner_type(string new_type){ image_name = new_type; owner_type = new_type; }

void Shape::display(Window* win, MyPoint position){

	win->draw_img(PATH + image_name + SUFFIX,
				Rectangle(Point(position.x - field_cordinate_info.cell_edge / 2, position.y - field_cordinate_info.cell_edge / 2),
					field_cordinate_info.cell_edge, field_cordinate_info.cell_edge));
}

void EnemyShape::display(Window* win, MyPoint position, blood_t current_health){

	win->draw_img(PATH + image_name + to_string(((int)shape_mood_counter) % 2) + SUFFIX,
				Rectangle(Point(position.x - field_cordinate_info.cell_edge / 2, position.y - field_cordinate_info.cell_edge / 2 - 12),
					field_cordinate_info.cell_edge, field_cordinate_info.cell_edge), NULL_RECT, 0, flip_horizontal, false);

	show_health_amount(win, position, current_health);
}

void EnemyShape::show_health_amount(Window* win, const MyPoint& position, const blood_t& current_health){

	win->draw_rect(Rectangle(Point(position.x - field_cordinate_info.cell_edge / 2 , position.y - field_cordinate_info.cell_edge / 2 - 27),
					field_cordinate_info.cell_edge , 10), BLACK, 2);

	int length_to_be_colored = current_health * field_cordinate_info.cell_edge / full_amount_of_enemy_health;
	win->fill_rect(Rectangle(Point(position.x - field_cordinate_info.cell_edge / 2 + 2, position.y - field_cordinate_info.cell_edge / 2 - 25),
					length_to_be_colored, 8), RED);
}

void ShotShape::display(Window* win, MyPoint position){
	win->fill_circle(Point(position.x, position.y), 7 + owner_level * 4, RGB(R, G, B));
}

EnemyShape::EnemyShape(string owner_type_, pair<int, char> direction) : Shape(owner_type_), shape_mood_counter(0) { set_image_name(direction); }

void EnemyShape::set_image_name(pair<int, char> direction){

	if(direction.second == HORIZONTAL){

		if(direction.first == -1){
			flip_horizontal = true;
		}
		else{
			flip_horizontal = false;
		}
		image_name = owner_type + move_direction_names[Right];
	}
	else if(direction.first == 1){
		image_name = owner_type + move_direction_names[Down];
	}
	else{
		image_name = owner_type + move_direction_names[Up];
	}
}

ShotShape::ShotShape(string owner_type_, level_t owner_level_) : R(GRAY), G(GRAY), B(GRAY), Shape(owner_type_), owner_level(owner_level_)
{
	set_color_of_shot();
}

void ShotShape::set_color_of_shot(){

	if(owner_type == towers_type[gatling][owner_level]){
		R = 255; G = 190 - owner_level * 50; B = 0;
	}
	if(owner_type == towers_type[missile][owner_level]){
		R = 255; G = 0; B = owner_level * 100;
	}
	if(owner_type == towers_type[tesla][owner_level]){
		R = 0; B = 255; G = 100 + owner_level * 70;
	}
	if(owner_type == towers_type[glue][owner_level]){
		R = 255 - 75 * owner_level; G = 255; B = 0;
	}
}

void EnemyShape::reset_shape_mood_counter(){ shape_mood_counter = 0; }

void EnemyShape::change_shape_mood(){ shape_mood_counter += 0.05; }

void EnemyShape::set_full_amount_of_enemy_health(blood_t health){ full_amount_of_enemy_health = health; }

void TowerShape::set_image_name(const MyPoint& enemy_position, const MyPoint& tower_position){

	image_name = owner_type;
	if(enemy_position.y > tower_position.y){
		image_name += move_direction_names[Down];
	}
	else if(enemy_position.y < tower_position.y){
		image_name += move_direction_names[Up];
	}
	if(enemy_position.x != tower_position.x){

		image_name += move_direction_names[Right];
		if(enemy_position.x > tower_position.x){
			flip_horizontal = false;
		}
		else{
			flip_horizontal = true;
		}
	}
}

TowerShape::TowerShape(string owner_type_) : Shape(owner_type_), flip_horizontal(true) { image_name += move_direction_names[Right]; }

void TowerShape::display(Window* win, const MyPoint& position){

	win->draw_img(PATH + image_name + SUFFIX,
				Rectangle(Point(position.x - field_cordinate_info.cell_edge / 2, position.y - field_cordinate_info.cell_edge / 2),
					field_cordinate_info.cell_edge, field_cordinate_info.cell_edge), NULL_RECT, 0, flip_horizontal, false);
}

void TowerShape::set_owner_type(string new_type){

	Shape::set_owner_type(new_type);
	image_name += move_direction_names[Right];
	flip_horizontal = true;
}
