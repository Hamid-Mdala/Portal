#ifndef PORTALUSERS_H
#define PORTALUSERS_H
#include<string>
#include <fstream>
#include <iostream>
#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"
#include "NavigationMenus.h"


class AbstractClass {
    public:
        virtual ~AbstractClass();
    public:
        virtual void editPassword() = 0;
        virtual void editFirstName() = 0;
        virtual void editlastName() = 0;
        virtual void editDOB() = 0;
};
class User {
    public:
        //More attributes
        std::string first_name;
        std::string last_name;
        std::string category;
        std::string birth_date;
    private:
        //AUTO INCREMENTED ID
        string username_;
        string password_;
    public:
        explicit User(const string& username);
        virtual ~User()  = default;

    public:
        bool editPassword();
        bool editFirstName();
        bool editLastName();
        bool editDOB();

        void setUsername(const string& username);
        string getUsername();
        void setPassword(const string& password);
        string getPassword();
};


class Student : public User {

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
};

#endif //PORTALUSERS_H
