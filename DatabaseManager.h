#pragma once
#include <memory>
#include<string>
#include <mariadb/conncpp.hpp>

extern std::string category; //this is used to get the category when the user logs in
extern std::string course_name_;  //this is used when we want to update the course name
extern std::string department_;   //this is used when we want to update the course department
class DatabaseManager {
    private:
        std::string user_;
        std::string password_;
        std::string db_;
        std::unique_ptr<sql::Connection> conn_;
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
        bool displayUser(const std::string& username, const std::string& category);
        bool searchUser(const std::string& username);
        bool authenticateUser(const std::string& username, const std::string& password);

        bool createCourse(const std::string& code, const std::string& name, const std::string& department);
        bool deleteCourse(const std::string& code);
        bool updateCourse(const std::string& code, const std::string& new_name, const std::string& new_department);
        bool displayCourse(const std::string& code);
        bool searchCourse(const std::string& code);

        bool createStudent(const int& student_id, const std::string& class_,
            const int& user_id, const float& gpa, const std::string& course_code);
        bool createAdmin(const int& admin_id, const int& user_id, const std::string& department,
            const std::string& office_number, const std::string& hire_date);

    //setter and getters
        void setUser(const std::string& user);
        std::string getUser();
        void setPassword(const std::string& password);
        std::string getPassword();
        void setDb(const std::string& db);
        std::string getDb();
        void setConnection(std::unique_ptr<sql::Connection> conn);
        sql::Connection& getConnectionRef();

};
