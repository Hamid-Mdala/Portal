#pragma once
#include<string>
#include <fstream>
#include <iostream>
#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"
#include "HandleMenus.h"


class AbstractClass {
    public:
        AbstractClass();
        virtual ~AbstractClass();
    public:
        virtual bool editPassword() = 0;
        virtual bool editFirstName() = 0;
        virtual bool editLastName() = 0;
        virtual bool editDOB() = 0;
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
        User(const string& username);
        virtual ~User()  = default;

    public:
        virtual bool editPassword();
        virtual bool editFirstName();
        virtual bool editLastName();
        virtual bool editDOB();

        void setUsername(const string& username);
        string getUsername();
        void setPassword(const string& password);
        string getPassword();
};

