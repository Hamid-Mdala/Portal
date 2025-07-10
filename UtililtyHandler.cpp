#include "UtililtyHandler.h"
#include <iostream>
#include "PortalUsers.h"
#include "DatabaseManager.h"
#include <conncpp/Connection.hpp>

static float gpa;

CategoryStudent::CategoryStudent(const std::string &username) {this->username_ = username;}

bool CategoryStudent::enrollCourse() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    std::cout << "Enroll Course" << "\n";
    //std::cout << "";  //if its the new student enrolling we have to insist of the student_id
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
    stmt->setString(1, username_);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    if (res->next() &&  res->getInt(1)) {
        user_id = res->getInt("id");
        std::cout << "Found the users username" << "\n";
    } else {
        std::cout << "Couldn't find the users username" << "\n";
    }
    stmt.reset( conn_.prepareStatement("SELECT * FROM Students WHERE user_id = ?"));
    stmt->setInt(1, user_id);  //this is an index in the database

    res.reset( stmt->executeQuery());
    if (res->next() && res->getInt(1)) {
        student_id = res->getInt("student_id");
        gpa = res->getFloat("gpa");
        return true;
    } else {
        std::cout << "Couldn't find the users Identification Number" << "\n";
        bool exists;
        do {
            std::cout << "Enter your student ID: " << "\n";
            std::cin >> student_id;  //2420016
            exists = ValidationCheck::validateId(student_id);
        } while (exists);
        do {
            std::cout << "what is your class year\n" << "Are you either 'fresh-man, sophomore, junior or senior'?"
            std::cout << "Enter your year: " << "\n";
            std::cin >> year;
            exists = ValidationCheck::validateYear(year);
        } while (!exists);
        do {
            //have to show the course table details so that we could enroll into the course
        }
        dbManager.createStudent(student_id, year, user_id, gpa, course_code);
        return false;
    }
}

bool CategoryStudent::getResults() {

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Students WHERE student_id = ?"));
    stmt->setInt(1, student_id);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    if (res->next() && res->getInt(1)) {
        gpa = res->getFloat("gpa");
        std::cout << "Your grade score difference is: " << gpa << "\n";
        return true;
    } else {
        std::cout << "Your grade score difference is null" << "\n";
        return false;
    }
}

bool CategoryStudent::updateProfile() {
    int choice;
    User user(username_);
    do {
        std::cout << "Update profile menu" << "\n";
        std::cout << "1. Update password" << "\n";
        std::cout << "2. Update first name" << "\n";
        std::cout << "3. Update last name" << "\n";
        std::cout << "4. Update date of birth" << "\n";
        std::cout << "5. choice to exit the update profile menu" << "\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                user.editPassword();
                break;
            case 2:
                user.editFirstName();
                break;
            case 3:
                user.editFirstName();
                break;
            case 4:
                user.editDOB();
                break;
            default:
                std::cout << "Invalid choice please enter between (1 - 5)";
                break;
        }
    } while (choice != 5);  //while the choice is not equal to 5 we will stay in the loop
}

void CategoryStudent::setId(const int& id) { user_id = id;}
int CategoryStudent::getId() {return user_id;}


