#ifndef U_MANAGER_HPP
#define U_MANAGER_HPP "U_MANAGER_HPP"

#include"Const.hpp"


struct ProperConditionInfo;

class UsersManager {
public:
	UsersManager() : current_logged_in_user(NULL) {}
	~UsersManager();
	class User;
	void add_user(std::string username, std::string email, std::string password);
	void login_user(std::string email, std::string password);
	void logout();
	void set_filter_for_user_based_arguments(const std::string& filter_info);
	void extract_user_manual_weights(std::string weights_info);

	User* current_logged_in_user;

private:
	std::vector<User*> users;
	bool is_new_user_info(const std::string& username, const std::string& email);
	ProperConditionInfo extract_city_filter_info(std::string filter_info);
	ProperConditionInfo extract_stars_filter_info(std::string filter_info);
	ProperConditionInfo extract_price_filter_info(std::string filter_info);
	ProperConditionInfo extract_rooms_filter_info(std::string filter_info);
	void extract_buget_filter_info(std::string filter_info);
};

#endif
