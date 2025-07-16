#pragma once
#include<string>

class AbstractClass {
    public:
        AbstractClass();
        virtual ~AbstractClass();
        virtual bool editPassword() = 0;
        virtual bool editFirstName() = 0;
        virtual bool editLastName() = 0;
        virtual bool editDOB() = 0;
};

class User {
    public:
        std::string first_name;
        std::string last_name;
        std::string category;
        std::string birth_date;
    private:
        std::string username_;
        std::string password_;
    public:
        User(const std::string& username);
        virtual ~User()  = default;

        virtual bool editPassword();
        virtual bool editFirstName();
        virtual bool editLastName();
        virtual bool editDOB();

        //setter and getters
        void setUsername(const std::string& username);
        std::string getUsername();
        void setPassword(const std::string& password);
        std::string getPassword();
};

