#include "UtililtyHandler.h"
#include <iostream>
#include "ModifyPortalUsers.h"
#include "DatabaseManager.h"
#include <conncpp/Connection.hpp>

static float gpa;
inline std::string global_course;

Category::Category(const std::string &username) {this->username_ = username;}

bool Category::updateProfile() {
    int choice;
    User user(username_);
    do {
        std::cout << "Update profile menu" << "\n";
        std::cout << "1. Update password" << "\n";
        std::cout << "2. Update first name" << "\n";
        std::cout << "3. Update last name" << "\n";
        std::cout << "4. Update date of birth" << "\n";
        std::cout << "Note: enter 0 to go back to the previous menu" << "\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        system("clear");

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
            case 0:
                std::cout << "Exited previous menu.." << "\n";
                break;
            default:
                std::cout << "Invalid choice please enter between (1 - 5)";
                break;
        }
    } while (choice != 0);  //while the choice is not equal to 5 we will stay in the loop
    return true;
}

bool Category::deleteProfile() {
    int choice;
    User user(username_);

    std::cout << "Delete profile menu" << "\n";

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    if (bool exists = dbManager.searchUser(username_)) {
        dbManager.deleteUser(username_);
        std::exit(EXIT_SUCCESS);  // exit the program
    } else {
        std::cout << "The User does no longer exist in the database" << "\n";
        std::cout << "For any issues please report to the software developer to help you fix the issue or contact +256994500600" << "\n";
        std::exit(EXIT_FAILURE);  //exit the program
    }
}

bool CategoryStudent::enrollCourse() {  //a student is made when they enroll into a course
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    std::cout << "Enroll Course" << "\n";
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
    stmt->setString(1, username_);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    if (res->next() &&  res->getInt(1)) {
        //the username exist
        user_id = res->getInt("id");
        std::cout << "Found the users username" << "\n";
    } else {
        //the username does not exist
        std::cout << "Couldn't find the users username" << "\n";
    }
    stmt.reset( conn_.prepareStatement("SELECT * FROM Students WHERE user_id = ?"));
    stmt->setInt(1, user_id);  //this is an index in the database

    res.reset( stmt->executeQuery());
    if (res->next() && res->getInt(1)) {
        //user already exists in the students table
        do {
            student_id = res->getInt("student_id");
            year = res->getString("class");

            std::cout << "Enter the course: " << "\n";
            std::cin >> course_code;
            system("clear");

            stmt.reset(conn_.prepareStatement("SELECT * FROM Course WHERE course_code = ?"));
            stmt->setString(1, course_code);

            res.reset(stmt->executeQuery());
            if (res->next() && res->getInt(1)) {
                //the course code exist
                std::cout << "Course_code: " << res->getString("course_code");
                std::cout << ", Name: " << res->getString("name");
                std::cout << ", Department: " << res->getString("department") << "\n";
                dbManager.createStudent(student_id, year, user_id, gpa, course_code);
                std::cout << "Successfully enrolled into the course" << "\n";
            } else {
                //the course code does not exist
                std::cout << "Couldn't find course course_code" << "\n";
                return false;
            }
        } while (!false);
    }
        {
            //user does not exist in the students table
            bool exists;
            do {
                std::cout << "Enter your student ID: " << "\n";
                std::cin >> student_id;  //2420016
                exists = ValidationCheck::validateId(student_id);
                system("clear");
            } while (exists);
            do {
                std::cout << "what is your class year\n" << "Are you either 'fresh-man, sophomore, junior or senior'?" << "\n";
                std::cout << "Enter your year: " << "\n";
                std::cin >> year;   //what the year of their class
                exists = ValidationCheck::validateYear(year);
                system("clear");
            } while (!exists);
            do  {
                std::cout << "Enter the course code: " << "\n";
                std::cin >> course_code;
                system("clear");

                stmt.reset(conn_.prepareStatement("SELECT * FROM Course WHERE course_code = ?"));
                stmt->setString(1, course_code);

                res.reset(stmt->executeQuery());
                if (res->next() && res->getInt(1)) {
                    //if the course code exist
                    std::cout << "Course_code: " << res->getString("course_code");
                    std::cout << ", Name: " << res->getString("name");
                    std::cout << ", Department: " << res->getString("department") << "\n";
                    dbManager.createStudent(student_id, year, user_id, gpa, course_code);
                    std::cout << "Successfully enrolled into the course" << "\n";
                } else {
                    //the course code does not exist
                    std::cout << "Couldn't find any course code in the database" << "\n";
                    return false;
                }
            } while (!false);
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

std::string CategoryAdmin::makeCourseInDB() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::cout << "Enter the course code: " << "\n";
    std::cin >> course_code;
    //SEARCH COURSE_CODE
    if (bool exists = dbManager.searchCourse(course_code)) {
        std::cout << "already exists in course database" << "\n";
        std::exit(EXIT_SUCCESS);
    } else {
        std::cout << "Enter course name: " << "\n";
        std::cin >> course_name;
        std::cout << "Enter department: " << "\n";
        std::cin >> department;

        if (bool exists = dbManager.createCourse(course_code, course_name, department)) {
            std::cout << "Successfully created a course" << "\n";
        } else {
            std::cout << "Couldn't create a course" << "\n";
            std::exit(EXIT_FAILURE);
        }
    }
    return global_course = course_code;
}


void CategoryStudent::setId(const int& id) { user_id = id;}
int CategoryStudent::getId() {return user_id;}


