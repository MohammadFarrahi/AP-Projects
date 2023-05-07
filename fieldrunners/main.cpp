#include"Game.hpp"

#define OUT false

using namespace std;


int main(){
	Game fieldrunners;
	bool status;
	fieldrunners.initialize_field_waves();
	while(true){

		fieldrunners.play();
		status = fieldrunners.display();
		if(status == OUT){
			break;
		}
		delay(10);
	}
	delay(5000);
	return 0;
}
