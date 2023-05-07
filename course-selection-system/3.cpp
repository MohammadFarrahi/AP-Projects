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
#define MIN_GRADE_TO_PASS_COURSE 10.00
#define MIN_GRADE_TO_TAKE_MOST_UNITS 17.00
#define GPA_INCREASING_AMOUNT 1.05
#define NORM_MAX_UNITS_TO_TAKE 20
#define MOST_UNITS_TO_TAKE 24
#define CHAR_SIZE 1
#define ZERO 0
#define FILENAME "semester"
#define FILE_TYPE_NAME ".sched"


enum Week_Day{ Sat, Sun, Mon, Tue, Wed, Thu };


typedef int ID;
typedef int Unit;
typedef vector<ID> Courses_ID;
typedef vector<struct Course> CourseTable;
typedef pair <ID, pair <double, Unit> > GradeInfo;
typedef vector <GradeInfo > CourseGrade;
typedef vector<struct Day_Time> Schedule;


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

struct CoursesInfo {
    CourseTable all_courses;
    CourseTable possible_courses_to_get;
    Courses_ID passed_courses;
    CourseGrade course_grades;
    double total_gpa;
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

Unit get_units_PointedBy_id(ID id, const CourseTable& courses, int counter = ZERO){

    Unit units = ZERO;

    if( counter == courses.size())
        return ZERO;

    if(id == courses[counter].id)
        return courses[counter].units;

    units = get_units_PointedBy_id (id, courses, ++counter);

    return units;
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

CourseGrade read_grades(string grades_info_file_path, const CourseTable& all_courses){

    CourseGrade course_grade;
    bool id_exists = false;
    ID course_id;
    double grade;
    Unit units;
    string line;
    const char ignore_comma = ',';
    
    ifstream grades_file(grades_info_file_path);
    getline(grades_file, line, DELIM_TO_IGNORE_FIRST_LINE);

    while(grades_file >> course_id){

        grades_file.ignore(CHAR_SIZE, ignore_comma);
        grades_file >> grade;

        for(int counter_of_id = ZERO; counter_of_id < course_grade.size(); counter_of_id++){
        
            if(course_grade[counter_of_id].first == course_id ){

                course_grade[counter_of_id].second.first = grade;
                id_exists = true;
            }
        }

        if(id_exists == false){

            units = get_units_PointedBy_id (course_id, all_courses);
            course_grade.push_back( make_pair (course_id, make_pair (grade, units)));
        }

        id_exists = false;
    }
    return course_grade;
}

Courses_ID find_passed_courses_id(CourseGrade course_grade){

    Courses_ID passed_courses_id;

    for(int id_counter = ZERO; id_counter < course_grade.size(); id_counter++){

        if(course_grade[id_counter].second.first >= MIN_GRADE_TO_PASS_COURSE)

            passed_courses_id.push_back(course_grade[id_counter].first);
    }
    return passed_courses_id;
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

double calculate_gpa(const CourseGrade& course_grades){

    double total_gpa;
    double sum_of_grades = ZERO;
    int sum_of_units = ZERO;

    for(int grade_index = ZERO; grade_index < course_grades.size(); grade_index++){

        sum_of_units += course_grades[grade_index].second.second ;

        sum_of_grades += course_grades[grade_index].second.first * course_grades[grade_index].second.second ;
    }

    total_gpa = sum_of_grades / sum_of_units;

    return total_gpa;
}

CourseGrade update_course_grades(CourseGrade course_grades, CourseTable former_recommended_courses, double termic_gpa){

    bool id_exists = false;
    pair <double, Unit> temp_pair;
    
    for(int index1 = ZERO; index1 < former_recommended_courses.size(); index1++){

        for(int index2 = ZERO; index2 < course_grades.size(); index2++){

            if(former_recommended_courses[index1].id == course_grades[index2].first){
                id_exists = true;
                course_grades[index2].second.first = termic_gpa;
                break;
            }
        }
        if(! id_exists){

            temp_pair.second = former_recommended_courses[index1].units;
            temp_pair.first = termic_gpa;
            course_grades.push_back(make_pair(former_recommended_courses[index1].id , temp_pair));
            }

        id_exists = false;
    }
    return course_grades;
}

Unit get_max_units_possible(double student_termic_gpa){

    if(student_termic_gpa >= MIN_GRADE_TO_TAKE_MOST_UNITS)

        return MOST_UNITS_TO_TAKE;

    return NORM_MAX_UNITS_TO_TAKE;
}

bool order_sorting_manner(const Course& C1, const Course& C2){

    if(C1.units != C2.units)

        return (C1.units > C2.units);

    return (C1.name < C2.name); 
}

bool commen_in_time(int start1, int end1, int start2, int end2){

    if(start1 < start2 && start2 < end1)
        return true;
    if(start1 < end2 && end2 < end1)
        return true;
    if(start2 <= start1 && end1 <= end2)
        return true;

    return false;
}

bool is_course_dismatch_with_others(Schedule schedule_of_course, const CourseTable& courses_to_check, int counter = ZERO){

    if(counter == courses_to_check.size())
        return false;

    bool status = false;
    Schedule schedule_to_check = courses_to_check[counter].schedule;
    
    for(int index1 = ZERO; index1 < schedule_of_course.size(); index1++ ){

        for(int index2 = ZERO; index2 < schedule_to_check.size(); index2++){

            if(schedule_of_course[index1].course_day != schedule_to_check[index2].course_day)
                continue;

            if(commen_in_time(schedule_of_course[index1].starting_time, schedule_of_course[index1].ending_time, 
                schedule_to_check[index2].starting_time, schedule_to_check[index2].ending_time))

                status = true;
        }
    }

    if(status == false)

        status = is_course_dismatch_with_others(schedule_of_course, courses_to_check, ++counter);

    return status;
}

CourseTable find_recommended_courses_to_take(const CourseTable& possible_courses_to_get, Unit max_possible_units_to_get){

   CourseTable recommended_courses;
    Unit sum_of_units = ZERO, course_units;

    for(int course_counter = ZERO; course_counter < possible_courses_to_get.size(); course_counter++){

         course_units = possible_courses_to_get[ course_counter ].units;

        if( sum_of_units + course_units > max_possible_units_to_get )
            continue;

        if(! is_course_dismatch_with_others(possible_courses_to_get[course_counter].schedule, recommended_courses)){

            sum_of_units += course_units;
            recommended_courses.push_back(possible_courses_to_get[course_counter]);
        }
    }
    return recommended_courses;
}

 Courses_ID add_new_passed_courses(Courses_ID passed_courses,const CourseTable& recommended_courses,int counter = ZERO){

    if(counter == recommended_courses.size())

        return passed_courses;

    passed_courses.push_back(recommended_courses[counter].id);

     passed_courses = add_new_passed_courses(passed_courses, recommended_courses, ++counter);

     return passed_courses;
 }

CourseTable find_possible_courses_to_get(Courses_ID passed_courses,const CourseTable& course_table){

    CourseTable courses_to_get;

    for(int course_counter = ZERO; course_counter < course_table.size(); course_counter ++){

        if(! is_passed_before( passed_courses, course_table[ course_counter ].id) && is_prerequisites_passed( passed_courses, course_table[ course_counter ].prerequisites))

            courses_to_get.push_back(course_table[course_counter]);
    }
    return courses_to_get;
}

CourseTable process_recommended_courses( CoursesInfo student_courses_info, double termic_gpa){

    Unit max_possible_units;
    CourseTable recommended_courses;

    sort(student_courses_info.possible_courses_to_get.begin(), student_courses_info.possible_courses_to_get.end(), order_sorting_manner);


    max_possible_units = get_max_units_possible(termic_gpa);
    recommended_courses = find_recommended_courses_to_take(student_courses_info.possible_courses_to_get, max_possible_units);

    return recommended_courses;
}

void save_recommended_courses_in_file(const CourseTable& recommended_courses, int name_counter ){

    vector< pair< string, ID> > ids_sorted_by_names;
    stringstream file_name;

    file_name <<FILENAME << name_counter <<FILE_TYPE_NAME;

    ofstream output_file(file_name.str());

    for(int course_counter = ZERO; course_counter < recommended_courses.size(); course_counter++)

        ids_sorted_by_names.push_back(make_pair(recommended_courses[course_counter].name , recommended_courses[course_counter].id));

    sort(ids_sorted_by_names.begin() , ids_sorted_by_names.end());

    for(pair<string, ID> R_C : ids_sorted_by_names)

        output_file << R_C.second << endl;
}

CoursesInfo process_reading_files(char *path[]){

    CoursesInfo student_courses_info;
    int input_file_path_index = ZERO;

    student_courses_info.all_courses = read_courses(path[++ input_file_path_index]);
    student_courses_info.course_grades = read_grades(path[++ input_file_path_index], student_courses_info.all_courses);

    return student_courses_info;
}

CoursesInfo preprocess_possible_courses(CoursesInfo student_courses_info){

    student_courses_info.total_gpa = calculate_gpa( student_courses_info.course_grades);
    student_courses_info.passed_courses = find_passed_courses_id(student_courses_info.course_grades);

    return student_courses_info;
}

CoursesInfo update_student_courses_info(CoursesInfo student_courses_info, const CourseTable& recommended_courses, double termic_gpa){

    student_courses_info.passed_courses = add_new_passed_courses(student_courses_info.passed_courses, recommended_courses);

    student_courses_info.course_grades = update_course_grades(student_courses_info.course_grades, recommended_courses, termic_gpa);

    student_courses_info.total_gpa = calculate_gpa( student_courses_info.course_grades);

    return student_courses_info;
}

int main(int argc, char *argv[]){

    CoursesInfo student_courses_info;
    CourseTable recommended_courses;
    double termic_gpa;
    int saving_counter = ZERO;
   
    student_courses_info = process_reading_files(argv);
    student_courses_info = preprocess_possible_courses(student_courses_info);
    termic_gpa = student_courses_info.total_gpa;


    while(student_courses_info.all_courses.size() != student_courses_info.passed_courses.size()){

    student_courses_info.possible_courses_to_get = find_possible_courses_to_get(student_courses_info.passed_courses, student_courses_info.all_courses);

    recommended_courses = process_recommended_courses(student_courses_info, termic_gpa);

    termic_gpa = student_courses_info.total_gpa * GPA_INCREASING_AMOUNT ;

    student_courses_info = update_student_courses_info(student_courses_info, recommended_courses, termic_gpa);
    
    save_recommended_courses_in_file(recommended_courses, ++saving_counter);
}

return ZERO;
}