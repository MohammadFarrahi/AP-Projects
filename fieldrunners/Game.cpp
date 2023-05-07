#include"Game.hpp"
#include<sstream>
#include<ctime>

#define WINDOW_TITLE "FieldRuners"
#define WINDOW_WIDTH 1365
#define WINDOW_HEIGHT 1024

#define BACKGROUND_IMAGE_PATH "./Assets/background.png"

#define HORIZONTAL 'H'
#define VERTICAL 'V'

using namespace std;


Game::Game() : window(new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)), game_status(IS_RUNNING, true) {}

void Game::check_input_event(){

	try{
		pair<money_t, pair<Point, char> > user_request = user.get_user_request(window);
		field.process_user_request(user_request);
	}
	catch(string& no_request_expression){}
	catch(exception& exit_program){

		cerr << exit_program.what() << endl;
		delete window;
		exit(0);
	}
}

void Game::prepare_to_exit(){

	field.process_exiting_game();
	int R, B, G;
	string message;
	if(game_status.second == WIN){
		R = 128; G = 128; B = 255;
		message = WINNING_MESSAGE;
	}
	else{
		R = 64; G = 128; B = 128;
		message = LOSING_MESSAGE;
	}
	window->draw_rect(Rectangle(Point(300, 265),720, 360), BLACK);
	window->fill_rect(Rectangle(Point(304, 269),712, 352), RGB(R, G, B));
	window->show_text(message, Point(350, 355), RED, MESSAGE_FONT_NAME, 50);
	window->show_text(CLOSING_MESSAGE, Point(355, 475), RED, MESSAGE_FONT_NAME, 30);
}

bool Game::display(){

	window->clear();
	window->draw_img(BACKGROUND_IMAGE_PATH);
	user.display_health_and_money(window);
	field.display(window);
	window->update_screen();
	if(game_status.first != IS_RUNNING){

		delay(500);
		prepare_to_exit();
		window->update_screen();
	}
	return game_status.first;
}

void Game::play(){

	bool is_wave_dead;
	field.reset_user_related_variables();
	check_input_event();
	is_wave_dead = field.update_current_wave_state();
	if(is_wave_dead == true){
		if(field.is_game_finished()){
			game_status = {false, WIN};
		}
	}
	field.update_towers_state();
	field.update_shots_state();
	user.update_health(field.get_total_user_health_damage());
	user.update_money(field.get_total_user_cost());
	if(user.is_dead()){
		game_status = {false, LOST};
	}
}

vector<pair<pair<int, char>, MyPoint> > generate_move_order(const pair<int, int>& src, const pair<int, int>& dest){

	pair <int, char> direction;
	vector<pair<pair<int, char>, MyPoint> > move_orders;
	if(src.first == dest.first){
			
		direction.second = VERTICAL;
		direction.first = src.second - dest.second < 0 ? 1 : -1;
		for(int i = src.second + direction.first; i != dest.second + direction.first; i = i + direction.first){
			move_orders.push_back({direction, get_middle_of_cell({src.first, i})});
		}
	}
	else{
		direction.second = HORIZONTAL;
		direction.first = src.first - dest.first < 0 ? 1 : -1;
		for(int i = src.first + direction.first; i != dest.first + direction.first; i = i + direction.first){
			move_orders.push_back({direction, get_middle_of_cell({i, src.second})});
		}
	}
	return move_orders;
}

vector<pair<pair<int, char>, MyPoint> > generate_input_move_orders(string input_cells){

	vector<pair<pair<int, char>, MyPoint> > move_orders, temp_move_orders;
	pair<int, int> previous_cell, current_cell;
	istringstream info_stream(input_cells);
	info_stream >> previous_cell.first >> previous_cell.second;
	while(info_stream >> current_cell.first){
		
		info_stream >> current_cell.second;
		temp_move_orders = generate_move_order(previous_cell, current_cell);
		move_orders.insert(move_orders.end(), temp_move_orders.begin(), temp_move_orders.end());
		previous_cell = current_cell;
	}
	return move_orders;
}

vector<int> generate_random_indexs(int vector_size){

	vector<int> random_indexs;
	int random_index, index_counter = 1;
	while(index_counter <= vector_size){

		bool is_new = true;
		random_index = rand() % vector_size;
		for(int i = 0; i < random_indexs.size(); i++){
			
			if(random_indexs[i] == random_index){
				is_new =false;
				break;
			}
		}
		if(is_new == false){
			continue;
		}
		index_counter++;
		random_indexs.push_back(random_index);
	}
	return random_indexs;
}

vector<pair<bool, Enemy*> > Game::randomise_arrangment_of_enemys(const vector<pair<bool, Enemy*> >& wave){

	int wave_size = wave.size();
	vector<pair<bool, Enemy*> > randomised_wave(wave_size);
	vector<int> random_indexs = generate_random_indexs(wave_size);
	for(int i = 0; i < wave_size; i++){
		randomised_wave[i] = wave[random_indexs[i]];
	}
	return randomised_wave;
}

vector<pair<bool, Enemy*> > Game::generate_input_enemy_wave(string wave_info, const pair<pair<int, char>, MyPoint>& first_move_order,
															const MyPoint& starting_position)
{
	static int wave_counter = 1;
	int number_of_enemys_of_each_type = 0;
	istringstream info_stream(wave_info);
	vector<pair<bool, Enemy*> > wave;

	for(int enemy_type_counter = 0; enemy_type_counter < NUMBER_OF_ENEMY_TYPES; enemy_type_counter++){

		info_stream >> number_of_enemys_of_each_type;
		switch(enemy_type_counter){
	
			case runner:{
				for(int i = 0; i < number_of_enemys_of_each_type; i++){
					wave.push_back({NOT_AVAILABLE, new Runner(starting_position, first_move_order, wave_counter)});
				}
				break;
			}
			case stubborn_runner:{
				for(int i = 0; i < number_of_enemys_of_each_type; i++){
					wave.push_back({NOT_AVAILABLE, new StubbornRunner(starting_position, first_move_order, wave_counter)});
				}
				break;
			}
			case super_trooper:{
				for(int i = 0; i < number_of_enemys_of_each_type; i++){
					wave.push_back({NOT_AVAILABLE, new SuperTrooper(starting_position, first_move_order, wave_counter)});
				}
				break;
			}
			case scrambler:{
				for(int i = 0; i < number_of_enemys_of_each_type; i++){
					wave.push_back({NOT_AVAILABLE, new Scrambler(starting_position, first_move_order, wave_counter)});
				}
				break;
			}
		}
	}
	if(wave.size() != 0){ wave_counter++; }
	return randomise_arrangment_of_enemys(wave);
}

void Game::initialize_field_waves(){

	string input_data;
	pair<int, int> starting_cell;

	getline(cin, input_data);
	istringstream stream(input_data);
	stream >> starting_cell.first >> starting_cell.second;
	MyPoint starting_position = get_middle_of_cell(starting_cell);

	pair<pair<int, char>, MyPoint> first_move_order = field.set_wave_movment_orders(generate_input_move_orders(input_data));
	srand(time(0));
	while(getline(cin, input_data)){
		field.add_wave(generate_input_enemy_wave(input_data, first_move_order, starting_position));
	}
}
