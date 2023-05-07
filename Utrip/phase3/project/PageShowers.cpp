#include"PageShowers.hpp"
#include"Const.hpp"
#include"UTrip.hpp"
#include"Exception.hpp"
#include<utility>
#include<fstream>
#include<map>

using namespace std;


Response* SignupForm::callback(Request* req){
	if(utrip->has_user_logged_in(req->getSessionId())){
		return Response::redirect("/home");
	}
	Response* res = new Response();
	ostringstream body;

	res->setHeader("Content-Type", "text/html");
	body 
 << "<!DOCTYPE html>" << endl
 << "<html>" << endl
 <<	"<head>" << endl
 <<	"	<title>Signup-UTrip</title>" << endl
 << "	<style>" << endl
 << "		body{" << endl
 << "			background-color: powderblue;" << endl
 << "			margin: auto;" << endl
 << "		}" << endl
 << "	</style>" << endl
 << "</head>" << endl
 << "<body>" << endl
 << "	<h2>Please compelete the form.</h2>" << endl
 << "	<p >***The signup will fail if your username or email has already existed***</><br>" << endl
 << "	<form action='signup' method='post'>" << endl
 << "			Username:<br><input type='text' name='username'/><br>" << endl
 << "		Password:<br><input type='Password' name='password'/><br>" << endl
 << "		Repeat Password:<br><input type='Password' name='R_password'/><br>" << endl
 << "		Email:<br><input type='text' name='email'/><br>" << endl
 << "		<input type='submit' value='Signup'/>" << endl
 << "	</form>" << endl
<< "<pre style='color: red; font-size: 25px;'>" << utrip->get_result_message() << "</pre>" << endl
<<"	</body></html>";
	res->setBody(body.str());
	return res;
}

Response* LoginForm::callback(Request* req){
	if(utrip->has_user_logged_in(req->getSessionId())){
		return Response::redirect("/home");
	}
	Response* res = new Response();
	ostringstream body;

	res->setHeader("Content-Type", "text/html");
	body
<< "<!DOCTYPE html>" << endl
<< "<html>" << endl
<< "	<head>" << endl
<< "		<title>Login-UTrip</title>" << endl
<< "		<style>" << endl
<< "			body{" << endl
<< "				background-color: powderblue;" << endl
<< "				text-align: center;" << endl
<< "			}" << endl
<< "			.Form{" << endl
<< "				background-color: green;" << endl
<< "				margin: auto;" << endl
<< "				max-width: 300px;" << endl
<< "				padding: 2%;" << endl
<< "			}" << endl
<< "			.input{" << endl
<< "				padding: 10px;" << endl
<< "				margin: auto;" << endl
<< "				margin-bottom: 5px;" << endl
<< "			}" << endl
<< "		</style>" << endl
<< "	</head>" << endl
<< "	<body>" << endl
<< "		<h2>Login Form</h2>" << endl
<< "		<div class='Form'>" << endl
<< "			<form action='login' method='post'>" << endl
<< "				<input type='text' name='email' placeholder='Email' class='input'/><br>" << endl
<< "				<input type='Password' name='password' placeholder='Password'; class='input'/><br>" << endl
<< "				<button type='sumbit' style='margin-top: 20px; text-align: center; width: 100px;'>Login</button>" << endl
<< "			</form>" << endl
<< "			<p style='color: red; font-size: 25px; margin-top: 25px; margin-bottom: 10px;'>" << utrip->get_result_message()
			<<"</p>" << endl
<< "		</div></body></html>";
	res->setBody(body.str());
	return res;
}

Response* HomePage::callback(Request* req){
	try{
		utrip->detect_request_owner(req->getSessionId());
		Response* res = new Response();
		ostringstream body;

	res->setHeader("Content-Type", "text/html");
	fill_body_of_home_page(body);
	res->setBody(body.str());
	utrip->offline_requset_owner();
	return res;
	}
	catch(exception& e){
		return Response::redirect("/error");
	}
}

void HomePage::fill_body_of_home_page(ostream& body){
	vector<Hotel*> hotels_to_be_showed = utrip->get_hotels_to_be_showed_for_user();

	body
<< "<!DOCTYPE html>" << endl
<< "<html>" << endl
<< "	<head>" << endl
<< "		<title>Home-UTrip</title>" << endl
<< "		<meta name='viewport' content='width=device-width, initial-scale=1'>" << endl
<< "		<link rel='stylesheet' href='static/home-page.css'>" << endl
<< "	</head>" << endl
<< "	<body>" << endl
<< "		<br><h2>Hi " << utrip->get_user_name() << "</h2><br>" << endl
<< "<ul>" << endl
<< " 			<li><a class='active' href='home'>Home</a></li>" << endl
<< "			<li><a href='credit'>Credit</a></li>" << endl
<< "			<li style='float:right'><a href='logout'>Logout</a></li>" << endl
<< "		</ul><br><br>" << endl
<< "		<form action='filter' method='post'>" << endl
<< "			Filter Hotel stars: " << endl
<< "			<input name='min_stars' type='text' placeholder='Min stars'/>" << endl
<< "			<input name='max_stars' type='text' placeholder='Max stars'/>" << endl
<< "			<button type='submit'>Filter</button>" << endl
<< "		</form>" << endl
<< "<p style='font-size: 25px; margin-top: 25px; margin-bottom: 10px;'>" << utrip->get_result_message()
<< "</p>";

	for(auto& hotel : hotels_to_be_showed){
		body
<< "		<br><div class='container'>" << endl
<< "		<img src='" << hotel->get_url_image() << "' alt='Hotel Image' style='width:100%;'>" << endl
<< "		<div class='content'>" << endl
<< "			<h1>" << hotel->get_hotel_name() << "</h1>" << endl
<< "				<pre style='font-size: 18px;'>City: " << hotel->get_city_name() << "  Stars: " << hotel->get_stars()
<< "  <a href='details?id=" << hotel->get_id() << "' style='color: white;'>Details</a></pre>" << endl
<< "		</div></div>";
	}
	body << "<br></body></html>";
}

Response* LogoutPage::callback(Request* req){
	utrip->logout_user(req->getSessionId());
	
	ifstream logout_page_source(LOGOUT_PAGE_HTML_SOURCE_CODE);
	Response* res = new Response();
	stringstream body;
	body << logout_page_source.rdbuf();
	res->setHeader("Content-Type", "text/html");
	res->setBody(body.str());
	res->setSessionId(EMPTY);
	return res;
}

Response* CreditPage::callback(Request* req){
	utrip->detect_request_owner(req->getSessionId());
	Response* res = new Response();
	ostringstream body;

	res->setHeader("Content-Type", "text/html");
	fill_body_of_credit_page(body);
	res->setBody(body.str());
	utrip->offline_requset_owner();
	return res;
}

void CreditPage::fill_body_of_credit_page(ostream& body){
	body
<< "<!DOCTYPE html>" << endl
<< "<html>" << endl
<< "	<head>" << endl
<< "		<title>Credit-UTrip</title>" << endl
<< "		<meta name='viewport' content='width=device-width, initial-scale=1'>" << endl
<< "		<link rel='stylesheet' href='static/credit-page.css'>" << endl
<< "	</head>" << endl
<< "	<body>" << endl
<< "		<br><h2>Hi " << utrip->get_user_name() << "</h2><br>" << endl
<< "		<ul>" << endl
<< " 			<li><a href='home'>Home</a></li>" << endl
<< "			<li><a class='active' href='credit'>Credit</a></li>" << endl
<< "			<li style='float:right'><a href='logout'>Logout</a></li>" << endl
<< "		</ul><br><br>" << endl
<< "		<div class='Credit'>" << endl
<< "			<h3>Current Credit: " << utrip->get_user_credit() <<"</h3>" << endl
<< "		<br></div>" << endl
<< "		<div class='Increase'>" << endl
<< "			<h3 style='margin-top: 10px;'>Charge your account:</h3>" << endl
<< "			<pre>((The increasing amount must be" << endl
<< "more than zero))</pre>" << endl
<< "			<form action='/credit' method='post'>" << endl
<< "				<input name='amount' type='text' placeholder='Increasing Amount'/><br>" << endl
<< "				<button type='submit' style='margin-top: 10px;'>Increase</button>" << endl
<< "			</form>" << endl
<< "			<p style='font-size: 15px;'>" << utrip->get_result_message() << "</p>" << endl
<< "		</div>" << endl
<< "	</body>" << endl
<< "</html>";
}

Response* HotelPage::callback(Request* req){
	utrip->detect_request_owner(req->getSessionId());
	Response* res  = new Response();
	ostringstream body;
	hotel = utrip->find_hotel_by_id(req->getQueryParam("id"));

	res->setHeader("Content-Type", "text/html");
	fill_body_of_hotel_page(body);
	res->setBody(body.str());
	utrip->offline_requset_owner();
	return res;
}

void HotelPage::fill_body_of_hotel_page(ostream& body){
	vector<string> amenities = hotel->get_amenities();
	map<string, pair<int, int> > hotel_rooms_info = hotel->get_rooms_info();
	body
<< "<!DOCTYPE html>" << endl
<< "<html>" << endl
<< "	<head>" << endl
<< "		<title>Credit-UTrip</title>" << endl
<< "		<meta name='viewport' content='width=device-width, initial-scale=1'>" << endl
<< "		<link rel='stylesheet' href='static/hotel-page.css'>" << endl
<< "	</head>" << endl
<< "	<body>" << endl
<< "		<br><h2>Hi " << utrip->get_user_name() << "</h2><br>" << endl
<< "	<ul class='navbar'>" << endl
<< "			<li><a href='home'>Home</a></li>" << endl
<< "			<li><a href='credit'>Credit</a></li>" << endl
<< "			<li style='float:right'><a href='logout'>Logout</a></li>" << endl
<< "		</ul><br><br>" << endl
<< "		<div class='container'>" << endl
<< "			<img src='" << hotel->get_url_image() << "' alt='Hotel Image' style='width:100%;'>" << endl
<< "			<div class='content'>" << endl
<< "				<h1>" << hotel->get_hotel_name() << "</h1>" << endl
<< "			</div>" << endl
<< "		</div><br>" << endl
<< "		<div class='details'>" << endl
<< "			<h1>Details</h1>" << endl
<< "			<div class='content'>" << endl
<< "				<dl>" << endl
<< " 					<dt>Hotel overview:</dt>" << endl
<< "  						<dd>- " << hotel->get_overview() << "</dd>" << endl
<< "  					<dt>Property emenities:</dt>" << endl
<< "  						<dd>" << endl
<< "  							<ul>";
  	for(string amenity : amenities){
		body
		<< "<li>" << amenity << "</li>" << endl;
  	}
  	body
<< "						</ul>" << endl
<< "						</dd>" << endl
<< "					<dt>Hotel star rating:</dt>" << endl
<< "						<dd>- " << hotel->get_stars() << "</dd>" << endl
<< "					<dt>City:</dt>" << endl
<< "						<dd>- " << hotel->get_city_name() << "</dd>" << endl
<< "					<dt>Rooms:</dt><dd><table>" << endl
<< "						<tr>" << endl
<< "							<th>Type</th>" << endl
<< "							<th>Price per night</th>" << endl
<< "							<th>Ready to reserve</th>" << endl
<< "						</tr>";
	for(int i = 0; i < NUMBER_OF_ROOM_TYPES; i++){
		body
		<< "<tr>" << endl
<< "				<td>" << ROOM_TYPES[i] << "</td>" << endl
<< "				<td>" << hotel_rooms_info[ROOM_TYPES[i]].first << "</td>" << endl
<< "				<td>" << hotel_rooms_info[ROOM_TYPES[i]].second << "</td></tr>";
	}
	body
<< "						</table></dd></dl></div></div></body></html>";
}
