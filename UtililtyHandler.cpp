#include "UtililtyHandler.h"
#include <iostream>

#include "ModifyPortalUsers.h"
#include "DatabaseManager.h"
#include <conncpp/Connection.hpp>

static float gpa;
inline std::string course_name_;  //IMPORTANT! value that compares with the course_name the admin enters
inline std::string department_;   //IMPORTANT! value that compares with the department the admin enters

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
                user.editLastName();
                break;
            case 4:
                user.editDOB();
                break;
            case 0:
                std::cout << "Exited previous menu.." << "\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter valid value between (1-5)" << "\n";
                break;
        }
    } while (choice != 0);  //while the choice is not equal to 0 we will stay in the loop
    return true;
}

bool Category::deleteProfile() {
    std::cout << "Delete profile menu" << "\n";

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    if (bool exists = dbManager.searchUser(username_)) {
        dbManager.deleteUser(username_);
        std::exit(EXIT_SUCCESS);   //exit the program
    } else {
        std::cout << "The User does no longer exist in the database" << "\n";
        std::cout << "For any issues please report to the software developer to help you fix the issue or contact +256994500600" << "\n";
        std::exit(EXIT_FAILURE);   //exit the program
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

bool CategoryTeacher::teacherView() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();
    int choice;
    do {
        //view students that you are teaching
        //view the students gpa results in the students table
        //view my profile office number, department, hire date teacher_id and the course he teaches
        std::cout << "View option menu" << "\n";
        std::cout << "1. View students that learn your course" << "\n";
        std::cout << "2. View students GPA results" << "\n";
        std::cout << "3. View profile" << "\n";
        std::cout << "Note: enter 0 to go back to the previous menu" << "\n";
        std::cout << "Enter your choice: " << "\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                dbManager.numOfUsersThatLearnFromTeacher(course_code);
                break;
            case 2:
                dbManager.displayGPA();
                break;
            case 3:
                dbManager.viewProfile(username_);
                break;
            case 0:
                std::cout << "Exited previous menu.." << "\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter valid value between (1-3)" << "\n";
                break;
        }
    } while (choice != 0);
    return true;
}


bool CategoryAdmin::makeCourseInDB() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();
    bool exists;
    do {
        std::cout << "Enter the course code: " << "\n";
        std::cin >> course_code;
        exists = ValidationCheck::validateCourseId(course_code);
    } while (!exists);

    do {
        if (exists == dbManager.searchCourse(course_code)) {
            std::cout << "already exists in course database" << "\n";
            return false;
        } else {
            do {
                std::cout << "Enter course name: " << "\n";
                std::cin >> course_name;
                exists = ValidationCheck::validateCourseName(course_name);
            } while (!exists);

            do {
                std::cout << "Enter department: " << "\n";
                std::cin >> department;
                exists = ValidationCheck::validateAllString(department);
            } while (!exists);

            do {
                std::cout << "What semester will the course be learned in:  " << "\n";
                std::cin >> semester;
                exists = ValidationCheck::validateAllInt(semester);
            } while (!exists);

            {
                dbManager.createCourse(course_code, course_name, department, semester);
            }
        }
    } while (false);  //if the course code is found in the database
    return true;
}

bool CategoryAdmin::removeCourseInDB() {
    std::cout << "Delete course menu " << "\n";

    std::cout << "Enter the course code of the course you want to delete: " << "\n";
    std::cin >> course_code;

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    if (bool exists = dbManager.searchCourse(course_code)) {
        dbManager.deleteCourse(course_code);
        std::exit(EXIT_SUCCESS);   //exit the program
    } else {
        std::cout << "The Course does no longer exist in the database" << "\n";
        std::cout << "For any issues please report to the software developer to help you fix the issue or contact +256994500600" << "\n";
        std::exit(EXIT_FAILURE);   //exit the program
    }
}

bool CategoryAdmin::updateCourseInDB() {
    std::cout << "Update course menu " << "\n";

    std::cout << "Enter the course code of the course you want to update: " << "\n";
    std::cin >> course_code;

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    if (bool exists = dbManager.searchCourse(course_code)) {
        int choice;
        do {
            std::cout << "1. Update course name" << "\n";
            std::cout << "2. Update the class which the course is to be learned" << "\n";
            std::cout << "Enter your choice: " << "\n";
            std::cin >> choice;
            if (choice == 1) {
                do {
                    std::cout << "Enter new course name: " << "\n";
                    std::cin >> course_name;
                    exists = ValidationCheck::validateCourseName(course_name);
                } while (!exists);

                do {
                    if (exists && course_name == course_name_) {
                        std::cout << "You  entered your old course name" << "\n";
                        std::cout << "Enter new course name: " << "\n";
                        std::cin >> course_name;
                        exists = ValidationCheck::validateCourseName(course_name);
                    } else if (!exists) {
                        std::cout << "Enter new course name: " << "\n";
                        std::cin >> course_name;
                        exists = ValidationCheck::validateCourseName(course_name);
                    }
                } while (!exists && course_name == course_name_ );
                dbManager.updateCourse(course_code, course_name_, department_);
            } else if (choice == 2) {
                do {
                    std::cout << "Enter new department where the course will be taught: " << "\n";
                    std::cin >> department;
                    exists = ValidationCheck::validateAllString(department);
                } while (!exists);

                do {
                    if (exists && department == department_) {
                        std::cout << "You  entered your old department name" << "\n";
                        std::cout << "Enter new department where the course will be taught: " << "\n";
                        std::cin >> department;
                        exists = ValidationCheck::validateCourseName(department);
                    } else if (!exists) {
                        std::cout << "Enter new course name: " << "\n";
                        std::cin >> department;
                        exists = ValidationCheck::validateCourseName(department);
                    }
                } while (!exists && department == department_ );
                dbManager.updateCourse(course_code, course_name_, department_);
            } else {
                std::cout << "Invalid choice. Please enter valid between (1-2)" << "\n";
            }
        } while (choice > 2 && choice < 0);
    }
    return true;
}

bool CategoryAdmin::adminView() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    int choice;
    do {
        std::cout << "View option menu" << "\n";
        std::cout << "1. View all users" << "\n";
        std::cout << "2. View all courses" << "\n";
        std::cout << "3. View all students" << "\n";
        std::cout << "4. View all teachers" << "\n";
        std::cout << "5. View profile" << "\n";  //TODO: THIS LATER
        std::cout << "Note: enter 0 to go back to the previous menu" << "\n";
        std::cout << "Enter your choice: " << "\n";
        std::cin >> choice;
        switch(choice) {
            case 1:
                dbManager.displayUser();
                break;
            case 2:
                dbManager.displayCourse();
                break;
            case 3:
                dbManager.displayStudent();
                break;
            case 4:
                dbManager.displayTeacher();
                break;
            case 5:
                dbManager.viewProfile(username_);
                break;
            case 0:
                std::cout << "Exited previous menu.." << "\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter valid value between (1-4)" << "\n";
        }
    } while (choice != 0);  //while choice is not equal to 0 we will stay in the loop and the messages will be displayed
    return true;
}

void CategoryStudent::setId(const int& id) { user_id = id;}
int CategoryStudent::getId() {return user_id;}


