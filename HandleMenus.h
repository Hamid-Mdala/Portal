#pragma once
#include <iostream>

#include "UtililtyHandler.h"

class Menu {
    public:
        Menu(const std::string& username, const std::string& category);
        bool studentMenu();
        bool teacherMenu();
        bool adminMenu();
    private:
        std::string username_;
        std::string category_;
};