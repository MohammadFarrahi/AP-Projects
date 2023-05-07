#ifndef GAME_HPP
#define GAME_HPP "GAME_HPP"

#include"./src/rsdl.hpp"
#include"Field.hpp"
#include"User.hpp"
#include<string>
#include<vector>
#include<utility>

#define WINNING_MESSAGE "Congratulation! You WON"
#define LOSING_MESSAGE "Sorry! You LOST the game"
#define CLOSING_MESSAGE "The window will be closed in a few seconds..."
#define MESSAGE_FONT_NAME "./Assets/FreeSansBoldOblique-g9mR.ttf"

#define IS_RUNNING true
#define WIN true
#define LOST false


class Game {
public:
	Game();
	void initialize_field_waves();
	void play();
	bool display();

private:
	Window* window;
	User user;
	Field field;
	std::pair<bool, bool> game_status;

	void prepare_to_exit();
	void check_input_event();
	std::vector<std::pair<bool, Enemy*> > randomise_arrangment_of_enemys(const std::vector<std::pair<bool, Enemy*> >& wave);
	std::vector<std::pair<bool, Enemy*> > generate_input_enemy_wave(std::string wave_info,
									const std::pair<std::pair<int, char>, MyPoint>& first_move_order, const MyPoint& starting_position);
};

std::vector<std::pair<std::pair<int, char>, MyPoint> > generate_move_order(const std::pair<int, int>& src, const std::pair<int, int>& dest);
std::vector<std::pair<std::pair<int, char>, MyPoint> > generate_input_move_orders(std::string input_cells);
std::vector<int> generate_random_indexs(int vector_size);

#endif
