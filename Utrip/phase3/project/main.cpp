#include<iostream>
#include"Const.hpp"
#include"UTrip.hpp"
#include"Handlers.hpp"
#include"PageShowers.hpp"
#include "../server/server.hpp"

using namespace std;


int main(int argc, char* argv[]){
	try{
		Server server(8080);
		UTrip utrip;
		
		utrip.load_data(argv[HOTEL_DATA_FILE_PATH_COMMAND_INDEX], argv[RATING_DATA_FILE_PATH_COMMAND_INDEX]);
		server.get("/", new ShowPage(MAIN_PAGE_HTML_SOURCE_CODE));
		server.get("/signup", new SignupForm(&utrip));
		server.get("/login", new LoginForm(&utrip));
		server.post("/login", new LoginHandler(&utrip));
		server.post("/signup", new RegisterHandler(&utrip));
		server.get("/home", new HomePage(&utrip));
		server.get("/static/home-page.css", new ShowPage(HOME_PAGE_DESIGN_SOURCE_CODE));
		server.get("/error", new ShowPage(ERROR_PAGE_HTML_SOURCE_CODE));
		server.get("/logout", new LogoutPage(&utrip));
		server.get("/credit", new CreditPage(&utrip));
		server.get("/static/credit-page.css", new ShowPage(CREDIT_PAGE_DESIGN_SOURCE_CODE));
		server.post("/credit", new CreditHandler(&utrip));
		server.get("/details", new HotelPage(&utrip));
		server.get("/static/hotel-page.css", new ShowPage(HOTEL_PAGE_DESIGN_SOURCE_CODE));
		server.post("/filter", new StarsFilterHandler(&utrip));

		server.run();
	}
	catch(Server::Exception e){
		cerr << e.getMessage() << endl;
	}
	return 0;
}
