#include"UsersManager.hpp"
#include"User.hpp"
#include"Exception.hpp"
#include"Tools.hpp"
#include"Filter.hpp"
#include"TimePeriod.hpp"
#include<map>
#include<functional>
#include<algorithm>

using namespace std;


UsersManager::~UsersManager(){
	for(auto user : users){
		delete user;
	}
}

void UsersManager::detect_online_user(std::string session_id){
	auto online_user = logged_in_users_on_server.find(session_id);
	if(online_user == logged_in_users_on_server.end()){ throw invalid_access(); }
	current_online_user = online_user->second;
}

bool UsersManager::has_user_logged_in(string session_id){
	return logged_in_users_on_server.find(session_id) != logged_in_users_on_server.end();
}

bool UsersManager::is_new_user_info(const string& username, const string& email){
	for(auto user : users){
		if(username == user->username || email == user->email){
			return false;
		}
	}
	if(username == EMPTY || email == EMPTY){ return false; }
	return true;
}

string UsersManager::add_user(string username, string email, string password){
	if(!is_new_user_info(username, email) || password == EMPTY){
		throw failed_task();
	}
	string session_id = username;
	User* new_user = new UsersManager::User(username, email, password);
	users.push_back(new_user);
	logged_in_users_on_server[session_id] = new_user;
	return session_id;
}

string UsersManager::login_user(string email, string password){
	for(auto user : users){
		if((user->email == email) && user->password == hash<string>{}(password)){
			string session_id = user->username;
			logged_in_users_on_server[session_id] = user;
			return session_id;
		}
	}
	throw failed_task();
}

void UsersManager::logout_user(string session_id){
	current_online_user = logged_in_users_on_server[session_id];
	logged_in_users_on_server.erase(session_id);
	current_online_user->prepare_logout();
	current_online_user = NULL;
}
