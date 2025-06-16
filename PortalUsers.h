#ifndef PORTALUSERS_H
#define PORTALUSERS_H
#include<string>
#include <fstream>
#include <iostream>
#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"
#include "NavigationMenus.h"
using namespace std;

class AbstractClass {
    public:
        virtual ~AbstractClass();
    public:
        virtual void searchForUsername(const string& username) = 0;
        virtual void view() = 0;
        virtual void editDetails() = 0;
};
class User {
    public:
        //More attributes
        string first_name;
        string last_name;
        string sex;
        string date_of_birth;
        char del = '_';
    private:
        //Attributes
        string id;
        string username;
        string password;
        string user_classification;
    public:
        explicit User(const string& username);
        virtual ~User()  = default;
    public:
        void setUsername(const string& username);
        string getUsername();
        void setPassword(const string& password);
        string getPassword();
        void setId(const string& id);
        string getId();
        void setUserClassification(const string&  student_classification);
        string getUserClassification();
        virtual bool view();
        virtual bool editDetails();
};
class Course final {
    public:
        string course_name;
        string course_year;
    private:
        string course_id;
    public:
        explicit Course(const string& course_id);
        ~Course() = default;
        void setCourseId(const string& course_id);
        string getCourseId();
};
class Student final: public User {
    public:
        explicit Student(const string& username): User(username){};
        bool view() override;
        bool makeStudentsEnrollCourseTable(const string& course_id);
};
class Employee {
    public:
        static bool searchForUsername(const string& username);
        virtual ~Employee() = default;
        static bool employeeView();
};
class Teacher final: public User, public Employee {
    public:
        explicit Teacher(const string& username): User(username), Employee(){}
        bool readStudentsEnrolledToACourse(const string& course_id);
        bool view() override;
        bool makeStudentsGradeTable();
};
class Admin final : public User, public Employee {
     public:
        explicit Admin(const string& username): User(username), Employee(){};
        bool registration();
        bool view() override;
        bool editDetails() override;
};

#endif //PORTALUSERS_H
