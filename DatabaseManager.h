#pragma once
#include <memory>
#include<string>
#include <mariadb/conncpp.hpp>

extern std::string category;        //IMPORTANT: global variable used to get the category when the user authenticates
extern std::string course_code_;    //IMPORTANT: global variable used when we want to update the course name
extern std::string department_;     //IMPORTANT: global variable used when we want to update the course department
extern int teacher_id_;
extern int student_id_;
extern std::string year_;
class DatabaseManager {
    public:
        ~DatabaseManager() = default; //Destructor
        DatabaseManager(std::string  user, std::string  password, std::string  db);
        bool connect();

        bool createUser(const std::string& username,const std::string& password,
            const std::string& first_name, const std::string& last_name,
            const std::string& category, const int& day,
            const int& month, const int& year);
        bool deleteUser(const std::string& username);
        bool updateUser(const std::string& username, const std::string& new_password,
            const std::string& new_first_name, const std::string& new_last_name,
            const std::string& new_category, const std::string& new_dob);
        bool displayUser();
        bool searchUser(const std::string& username);
        bool authenticateUser(const std::string& username, const std::string& password);
        bool viewProfile(const std::string& username);

        bool createCourse(const std::string& code, const std::string& name,
            const std::string& department, const int& semester);
        bool deleteCourse(const std::string& code);
        bool updateCourse(const std::string& code, const std::string& new_name, const std::string& new_department);
        bool displayCourse();
        bool searchCourse(const std::string& code);

        bool createStudent(const int& student_id, const std::string& class_,
            const int& user_id, const std::string& course_code);
        bool searchStudent(const int& student_id);
        //TODO: WE MUST BE ABLE TO MAKE THE TEACHER AND MAKE ALSO HIS FUNCTIONS
        bool createTeacher(const int& teacher_id, const int& user_id, const std::string& office_number,
             const std::string& hire_date, const std::string& department, const std::string& course_code);
        bool numOfUsersThatLearnFromTeacher(const std::string& course_code);
        bool displayGPA();
        bool uploadResults(const float& gpa, const int& student_id, const std::string& course_code);
        bool searchTeacher(const int& teacher_id);
        bool createAdmin(const int& admin_id, const int& user_id, const std::string& department,
            const std::string& office_number, const std::string& hire_date);
        bool searchAdmin(const int& admin_id);
        bool displayStudent();
        bool displayTeacher();
        bool displayAdmin();

        //setter and getters
        void setUser(const std::string& user);
        std::string getUser();
        void setPassword(const std::string& password);
        std::string getPassword();
        void setDb(const std::string& db);
        std::string getDb();
        void setConnection(std::unique_ptr<sql::Connection> conn);
        sql::Connection& getConnectionRef();
    private:
        std::string user_;
        std::string password_;
        std::string db_;
        std::unique_ptr<sql::Connection> conn_;
};
