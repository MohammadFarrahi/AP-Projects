#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

#define NEWLINE_DELIM '\n'
#define DELIM_TO_IGNORE_FIRST_LINE '\n'
#define MIN_GRADE_TO_PASS_COURSE 10
#define CHAR_SIZE 1
#define ZERO 0


enum Week_Day{ Sat, Sun, Mon, Tue, Wed, Thu };


typedef int ID;
typedef vector<struct Day_Time> Schedule;
typedef vector<ID> Courses_ID;
typedef vector<pair <int, double> >CourseGrade;
typedef vector<struct Course> CourseTable;


struct Day_Time {
    Week_Day course_day;
    int starting_time;
    int ending_time;
};

struct Course {
    ID id;
    string name;
    int units;
    Schedule schedule;
    Courses_ID prerequisites;
};




int get_time(istream& ss){

    int HH, MM, time;
    const char ignore_colon = ':';

    ss >> HH;
    ss.ignore(CHAR_SIZE, ignore_colon);
    ss >> MM;
    time = HH * 100 + MM;

     return time;
}

Schedule read_schedule(string schedule_info){

    const char ignore_dash = '-',ignore_slash = '/';
    int course_day;
    Schedule schedule;
    Day_Time day_time;
    string day;
   
    vector<string> possible_days={"Sat", "Sun", "Mon", "Tue", "Wed", "Thu" };
    stringstream schedule_stream(schedule_info);

   while(getline(schedule_stream, day, ignore_dash)){

    for(course_day=Sat; course_day <= Thu; course_day ++){

        if(day == possible_days[course_day]){

            day_time.course_day = (Week_Day)course_day;
            break; 
        }
    }

   day_time.starting_time = get_time(schedule_stream);
   schedule_stream.ignore(CHAR_SIZE, ignore_dash);
   day_time.ending_time = get_time(schedule_stream);

   schedule_stream.ignore(CHAR_SIZE, ignore_slash);

   schedule.push_back(day_time);
    }
    return schedule;
}

Course read_one_course(string course_info){

     const char ignore_comma = ',' , ignore_dash = '-';
    Course course;
    string prerequisite_id_text;
    string schedule_info;
    stringstream course_stream(course_info);

    course_stream >> course.id;
    course_stream.ignore(CHAR_SIZE, ignore_comma);

    getline(course_stream, course.name, ignore_comma);
    
    course_stream >> course.units;
    course_stream.ignore(CHAR_SIZE,ignore_comma);

    getline(course_stream, schedule_info, ignore_comma);
    course.schedule = read_schedule(schedule_info);

    while(getline(course_stream, prerequisite_id_text, ignore_dash)){

        if(stoi(prerequisite_id_text) == ZERO)
            break;

        course.prerequisites.push_back(stoi(prerequisite_id_text));
    }
    return course;
}

CourseTable read_courses(string courses_info_file_path){

    CourseTable input_course_table;
    Course course;
    ifstream input_file(courses_info_file_path);
    stringstream input_stream;
    string line;

    input_stream << input_file.rdbuf();
    getline(input_stream, line, DELIM_TO_IGNORE_FIRST_LINE);

    while(getline(input_stream, line, NEWLINE_DELIM)){

        course = read_one_course(line);
        input_course_table.push_back(course);
    }
    return input_course_table;
}

CourseGrade read_grades(string grades_info_file_path){

    CourseGrade course_grade;
    bool id_exists = false;
    ID course_id;
    double grade;
    string line;
    const char ignore_comma = ',';
    
    ifstream grades_file(grades_info_file_path);
    getline(grades_file, line, DELIM_TO_IGNORE_FIRST_LINE);

    while(grades_file >> course_id){

        grades_file.ignore(CHAR_SIZE, ignore_comma);
        grades_file >> grade;

        for(int counter_of_id = ZERO; counter_of_id < course_grade.size(); counter_of_id++){
        
            if(course_grade[counter_of_id].first == course_id ){

                course_grade[counter_of_id].second = grade;
                id_exists = true;
            }
        }

        if(id_exists == false)
            course_grade.push_back(make_pair(course_id, grade));

        id_exists = false;
    }
    return course_grade;
}

Courses_ID passed_courses_id(CourseGrade course_grade){

    Courses_ID passed_courses;

    for(int id_counter = ZERO; id_counter < course_grade.size(); id_counter++){

        if(course_grade[id_counter].second >= MIN_GRADE_TO_PASS_COURSE)

            passed_courses.push_back(course_grade[id_counter].first);
    }
    return passed_courses;
}

bool is_passed_before(Courses_ID passed_courses, ID course_id){

    for(int i=ZERO; i < passed_courses.size(); i++)
        if(passed_courses[i] == course_id)
            return true;

    return false;
}

bool is_prerequisites_passed(Courses_ID passed_courses, Courses_ID prerequisites_of_course){

    int passed_prerequisites = ZERO;

    for(int i = ZERO; i< prerequisites_of_course.size(); i++)

        for(int index = ZERO; index < passed_courses.size(); index++)

            if(prerequisites_of_course[i] == passed_courses[index])

                passed_prerequisites ++;

    if(passed_prerequisites == prerequisites_of_course.size())
        return true;

    return false;
}

vector<Course> find_possible_courses_to_get(Courses_ID passed_courses,const CourseTable& course_table){

    vector<Course> courses_to_get;

    for(int course_counter = ZERO; course_counter < course_table.size(); course_counter ++){

        if(! is_passed_before( passed_courses, course_table[ course_counter ].id) && is_prerequisites_passed( passed_courses, course_table[ course_counter ].prerequisites))

            courses_to_get.push_back(course_table[course_counter]);
    }
    return courses_to_get;
}

void generate_output(const vector<Course>& courses_to_get){

    vector< pair< string, ID> > ids_sorted_by_names;

    for(int course_counter = ZERO; course_counter < courses_to_get.size(); course_counter++)

        ids_sorted_by_names.push_back(make_pair(courses_to_get[course_counter].name , courses_to_get[course_counter].id));

    sort(ids_sorted_by_names.begin() , ids_sorted_by_names.end());

    for(pair<string , ID> id_to_be_showed : ids_sorted_by_names)

        cout << id_to_be_showed.second << endl;
}

int main(int argc, char *argv[]){

    int input_file_path_index = ZERO;
    CourseTable course_table;
    CourseGrade course_grades;
    vector<Course> courses_to_get;
    
    course_table = read_courses(argv[++ input_file_path_index]);
    course_grades = read_grades(argv[++ input_file_path_index]);
    courses_to_get = find_possible_courses_to_get( passed_courses_id(course_grades), course_table);
    generate_output(courses_to_get);

    return ZERO;
}
