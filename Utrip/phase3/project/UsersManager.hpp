#ifndef U_MANAGER_HPP
#define U_MANAGER_HPP "U_MANAGER_HPP"

#include"Const.hpp"
#include<map>


class UsersManager {
public:
	class User;
	UsersManager() : current_online_user(NULL) {}
	~UsersManager();
	std::string add_user(std::string username, std::string email, std::string password);
	std::string login_user(std::string email, std::string password);
	void logout_user(std::string session_id);
	bool has_user_logged_in(std::string session_id);
	void detect_online_user(std::string session_id);

	User* current_online_user;
	
private:
	std::vector<User*> users;
	std::map<std::string, User*> logged_in_users_on_server;
	bool is_new_user_info(const std::string& username, const std::string& email);
};

#endif
