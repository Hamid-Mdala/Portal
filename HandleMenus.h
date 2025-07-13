#pragma once
#include <iostream>

#include "UtililtyHandler.h"

class Menu {
        private:
                std::string username_;   //should be private because we do not want any user gaining access to other user profile
                std::string category_;  //so that the same category is use within methods in this class
        public:
                Menu(const std::string& username, const std::string& category);
                bool studentMenu();
                bool teacherMenu();
                bool adminMenu();

};






















// #ifndef NAVIGATIONMENUS_H
// #define NAVIGATIONMENUS_H
//
// #include <string>
// using namespace std;
//
// class AllocateUser {
// public:
//     //Function handling the users allocation the aim is after logged in by the system during runtime they will have their own menu.
//     static bool allocateUserLoginClassification(const string& username);
// };
// class login {
//     public:
//         //Function handling the login in our management system
//         static bool handlingLogin();
// };
//
//
// #endif //NAVIGATIONMENUS_H
