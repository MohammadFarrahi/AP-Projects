#ifndef CONST_HPP
#define CONST_HPP "CONST_HPP"

#include<vector>
#include<string>


#define HOTEL_DATA_FILE_PATH_COMMAND_INDEX 1
#define RATING_DATA_FILE_PATH_COMMAND_INDEX 2

#define POST_TYPE_REQUSET "POST"
#define GET_TYPE_REQUEST "GET"
#define DELETE_TYPE_REQUEST "DELETE"

#define DEFAULT_OUTPUT_MESSAGE "OK\n"

#define ARGUMENT_SPECIFIER "?"
#define EMPTY ""
#define SPACE_CHAR ' '

#define ASCENDING_ORDER "ascending"
#define DESCENDING_ORDER "descending"
#define DEFAULT_PROPERTY "id"
#define DEFAULT_ORDER "ascending"

#define RATING_ITEMS 6
#define NUMBER_OF_ROOM_TYPES 4

#define NUM_OF_FILTERS 5
#define LEAST_RESERVES_FOR_BUDGET_FILTER 10
#define BUDGET_FILTER_MESSAGE "* Results have been filtered by the default price filter.\n"
#define EMPTY_MESSAGE ""

#define ENOUGH true
#define FIRST_CHAR 1

#define ACTIVE true
#define DISABLE false
#define ACTIVE_ORDER "true"
#define DISABLE_ORDER "false"

#define DELIMITER1 ','
#define POP_DELIMITER '|'
#define NEW_LINE '\n'

#define LEAST_RATINGS_TO_USE_ESTIMATED_WEIGHTS 5
#define END_OF_RATING_VALUE_RANGE 5
#define FIRST_OF_RATING_VALUE_RANGE 1
#define NUM_OF_ESTIMATE_WEIGHTS 1000
#define STEP_SIZE 1
#define EPSILON 1e-4

#define FAIL false
#define OK true


enum ArgumentIndex { A_username, A_email, A_password, A_R_password, A_amount, A_count, A_id, A_type,
						A_quantity, A_check_in, A_check_out, A_hotel, A_comment, A_property, A_order, A_active, A_rating };

enum RequestIndex { R_signup, R_login, R_logout, R_wallet, R_hotels, R_filters, R_reserves, R_comments, R_ratings, R_budget_filter,
					R_sort, R_manual_weights, R_estimated_weights };

enum FilterArgumentIndex { F_A_city, F_A_min_star, F_A_max_star, F_A_min_price, F_A_max_price, F_A_type, F_A_quantity, F_A_check_in, F_A_check_out,
							F_A_buget_filter_order};

enum PropertyIndex { P_id, P_name, P_stars, P_city, P_standard_price, P_deluxe_price, P_luxury_price, P_premium_price,
					P_average_price, P_rating_overall, P_rating_personal };

enum RatingItemsIndex { Location, Cleanliness, Staff, Facilities, Value_for_money, Overall_rating };

enum RoomTypeIndex { Standard, Deluxe, Luxury, Permium };

enum FilterType { city, stars, price, rooms, budget };

enum HotelFieldsIndex { H_id, H_name, H_stars, H_overview, H_amenities, H_city, H_latitude, H_longitude,
						H_image_url, H_num_of_rooms, H_price_of_rooms = 13 };

const std::vector<std::string> ARGUMENTS = {"username", "email", "password", "R_password", "amount", "count", "id", "type", "quantity",
									"check_in", "check_out", "hotel", "comment", "property", "order", "active", "location", "cleanliness",
									"staff", "facilities", "value_for_money", "overall_rating"};



const std::vector<std::string> REQUESTS = {"signup", "login", "logout", "wallet", "hotels", "filters", "reserves",
									"comments", "ratings", "default_price_filter", "sort", "manual_weights", "estimated_weights"};

const std::vector<std::string> FILTER_ARGUMENTS = {"city", "min_stars", "max_stars", "min_price", "max_price", "type", "quantity",
										"check_in", "check_out", "active"};

const std::vector<std::string> PROPERTIES = {"id", "name", "star_rating", "city", "standard_room_price", "deluxe_room_price",
									"luxury_room_price", "premium_room_price", "average_room_price", "rating_overall", "rating_personal"};

const std::vector<std::string> RATINGS_ITEMS = {"location", "cleanliness", "staff", "facilities", "value_for_money", "overall_rating"};

const std::vector<std::string> ROOM_TYPES = {"standard", "deluxe", "luxury", "premium"};

const std::string LOGOUT_PAGE_HTML_SOURCE_CODE = "static/logout-page.html";
const std::string MAIN_PAGE_HTML_SOURCE_CODE = "static/main-page.html";
const std::string ERROR_PAGE_HTML_SOURCE_CODE = "static/error-page.html";
const std::string HOME_PAGE_DESIGN_SOURCE_CODE = "static/home-page.css";
const std::string CREDIT_PAGE_DESIGN_SOURCE_CODE = "static/credit-page.css";
const std::string HOTEL_PAGE_DESIGN_SOURCE_CODE = "static/hotel-page.css";

const std::string SUCCESSFUL_OPERATION = "!!The oparation was successful!!";

#endif
