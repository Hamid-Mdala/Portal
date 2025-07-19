#include <iostream>
#include <conncpp/Connection.hpp>
#include "UtililtyHandler.h"

#include <filesystem>

#include "DatabaseManager.h"
#include "ModifyPortalUsers.h"
#include "HandlingValidationCheck.h"


inline std::string course_code_;    //IMPORTANT! value that compares with the course_name the admin enters
inline std::string department_;     //IMPORTANT! value that compares with the department the admin enters
inline int student_id_;             //IMPORTANT! value that is used by student who is already logged in to enroll into more courses
inline int teacher_id_;             //IMPORTANT! value that is used by teacher to get the course the teacher gets
inline std::string year_;           //IMPORTANT! value that is used by the student who is already logged in to enroll into more courses
inline std::string course_name_;    //IMPORTANT! value that is used by the admin because of the constraint unique of course_name in database, so this will prevent errors when the admin enters the same course_name

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
    } while (choice != 0);
    return true;
}

bool Category::deleteProfile() {
    std::cout << "Delete profile menu" << "\n";

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    if (bool exists = dbManager.searchUser(username_)) {
        dbManager.deleteUser(username_);
        std::exit(EXIT_SUCCESS);
    } else {
        std::cout << "The User does no longer exist in the database" << "\n";
        std::cout << "For any issues please report to the software developer to help you fix the issue or contact +256994500600" << "\n";
        std::exit(EXIT_FAILURE);
    }
}

bool CategoryStudent::enrollCourse() {
    std::cout << "Enroll course menu" << "\n";
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");

    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
    stmt->setString(1, username_);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    if (res->next()) {
       user_id = res->getInt("id");
        if (bool exists = dbManager.searchStudent(user_id)) {
            student_id = student_id_;
            year = year_;
            do {
                dbManager.displayCourse();
                std::cout << "What course do you want to enroll? " << "\n";
                std::cin >> course_code;
                exists = ValidationCheck::validateCourseId(course_code);
            } while (!exists);
            do {
                exists = dbManager.searchCourse(course_code);
                if (exists) {
                    dbManager.createStudent(student_id, year, user_id, course_code);
                    std::cout << "Successfully enrolled into the course" << "\n";
                }
            } while (!exists);
        } else {
            do {
                std::cout << "Enter your student ID: " << "\n";
                std::cin >> student_id;
                exists = ValidationCheck::validateId(student_id);
                system("clear");
            } while (exists);
            do {
                std::cout << "what is your class year\n" << "Are you either 'fresh-man,"
                                                            "sophomore, junior or senior'?" << "\n";
                std::cout << "Enter your year: " << "\n";
                std::cin >> year;   //what the year of their class
                exists = ValidationCheck::validateYear(year);
                system("clear");
            } while (!exists);
            do  {
                dbManager.displayCourse();
                std::cout << "Enter the course you want to learn: " << "\n";
                std::cin >> course_code;
                system("clear");
                exists = dbManager.searchCourse(course_code);
                    if (exists) {
                        dbManager.createStudent(student_id, year, user_id, course_code);
                        std::cout << "Successfully enrolled into the course" << "\n";
                    }
            } while (!exists);
        }
    } else {
        std::cout << "Couldn't find the users username" << "\n";
        std::cout << "Please report to the software engineer teem to fix your issue" << "\n";
        std::exit(EXIT_FAILURE);
    }
    return true;
}

bool CategoryStudent::getResults() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Students WHERE student_id = ?"));
    stmt->setInt(1, student_id);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    int index = 0;
    while(res->next() && res->getString("gpa") != nullptr) {
        std::cout << ++index << ". Student_ID: " << res->getInt("student_id");
        std::cout << ", Class: " << res->getString("class");
        std::cout << ", Course_code: " << res->getString("course_code");
        std::cout << ", GPA: " << res->getFloat("gpa");
    }
    if (index > 0) {
        std::cout << "Total number of courses with results: " << index << "\n";
        return true;
    } else {
        std::cout << "Your grade score results is empty" << "\n";
        return false;
    }
}

bool CategoryTeacher::teacherView() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();
    int choice;
    do {
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

//NOTE: That the teacher could claim that a course is his while the course is not actually his in the database
bool CategoryTeacher::uploadGPA() {
    std::cout << "Upload/Update students results menu" << "\n";
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();

    std::unique_ptr<sql::PreparedStatement> stmt(
        conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
    stmt->setString(1, username_);

    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
    if (res->next()) {
        user_id =  res->getInt("id");
        if (bool exists = dbManager.searchTeacher(user_id)) {
            teacher_id = teacher_id_;
            int student_id;
            std::string code;
            do {
                exists = dbManager.numOfUsersThatLearnFromTeacher(course_code);
                if (!exists) {
                    std::cout << "So do not have the priviledge to upload results" << "\n";
                    return EXIT_FAILURE;
                } else {
                    std::cout << "Use the students ID below that learn from your course" << "\n";
                }
            } while (!EXIT_FAILURE);
            do {
                std::cout << "Enter the students ID to upload the results: " << "\n";
                std::cin >> student_id;
                exists = ValidationCheck::validateId(student_id);
            } while (!exists);
            do {
                exists = dbManager.searchStudent(student_id);
                if (!exists && student_id != student_id_) {
                    std::cout << "Student is not found" << "\n";
                    std::cout << "Enter student ID to upload the results: " << "\n";
                    std::cin >> student_id;
                    exists = ValidationCheck::validateId(student_id);

                } else if (!exists) {
                    std::cout << "Enter student ID to upload the results: " << "\n";
                    std::cin >> student_id;
                    exists = ValidationCheck::validateId(student_id);
                }
                //NOTE: Once I enter the student ID, I must get the students courses lists
            } while (student_id != student_id_ || !exists);
            do {
                std::cout << "What course code you teach and want to upload results? " << "\n";
                std::cin >> code;
                exists = ValidationCheck::validateCourseId(code);
                //NOTE: I also have to validate the course code the teacher enters so that the teacher does not false clam
                //NOTE: And validate here so that when I am updating the students table it does not give me SQL errors
            } while (!exists);
            do {
                exists = dbManager.searchCourse(code);
                if (!exists && code != course_code_) {
                    std::cout << "Course is not found" << "\n";
                    std::cout << "What course code you teach and want to upload results? " << "\n";
                    std::cin >> code;
                    exists = ValidationCheck::validateCourseId(code);
                } else if (!exists) {
                    std::cout << "What course code you teach and want to upload results? " << "\n";
                    std::cin >> code;
                    exists = ValidationCheck::validateCourseId(code);
                }
            } while (code != course_code_ || !exists);
            do {
                std::cout << "Enter the students results: " << "\n";
                std::cin >> gpa_;
                exists = ValidationCheck::validateGpa(gpa_);
            } while (!exists);
            {
                dbManager.uploadResults(gpa_, student_id, code);
            }
        }
    } else {
        std::cout << "Couldn't find the users username" << "\n";
        std::cout << "Please report to the software engineer teem to fix your issue" << "\n";
        std::exit(EXIT_FAILURE);
    }
   return true;
}



bool CategoryAdmin::makeCourseInDB() {
    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    sql::Connection& conn_ = dbManager.getConnectionRef();
    bool exists;
    exists = dbManager.displayCourse();
    if (exists) {
        std::cout << "Those are the course you have created lately in the course table" << "\n";
    } else {
        std::cout << "This is the first course that will be created in the course table" << "\n";
    }
    do {
        std::cout << "Enter the course code: " << "\n";
        std::cin >> course_code;
        exists = ValidationCheck::validateCourseId(course_code);
    } while (!exists);
    bool check = false;
    do {
        exists = dbManager.searchCourse(course_code);
        if (exists) {
            std::cout << "Course code already exist" << "\n";
            std::cout << "Enter course code: " << "\n";
            std::cin >> course_code;
            check = ValidationCheck::validateCourseId(course_code);
        }
    } while (exists || !check);
    do {
        std::cout << "Enter course name: " << "\n";
        std::cin >> course_name;
        exists = ValidationCheck::validateCourseName(course_name);
    } while (!exists);
    do {
        if (exists && course_name == course_name_) {
            std::cout << "Course name already exist" << "\n";
            std::cout << "Enter course name: " << "\n";
            std::cin >> course_name;
            exists = ValidationCheck::validateCourseName(course_name);
        } else if (!exists) {
            std::cout << "Enter course name: " << "\n";
            std::cin >> course_name;
            exists = ValidationCheck::validateCourseName(course_name);
        }

    } while (course_name == course_name_ || !exists);
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
    return true;
}

bool CategoryAdmin::removeCourseInDB() {
    std::cout << "Delete course menu " << "\n";

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    bool exists;

    do {
        exists = dbManager.displayCourse();
        if (!exists) return EXIT_FAILURE;
        std::cout << "Enter the course code of the course you want to delete: " << "\n";
        std::cin >> course_code;
        exists = ValidationCheck::validateCourseId(course_code);
    } while (!exists);
    do {
        dbManager.searchCourse(course_code);
        if (exists && course_code == course_code_) {
            dbManager.deleteCourse(course_code);
            std::exit(EXIT_SUCCESS);
        } else {
            std::cout << "The Course does no longer exist in the database" << "\n";
            std::cout << "For any issues please report to the software developer to help"
                         "you fix the issue or contact +256994500600" << "\n";
            std::exit(EXIT_FAILURE);
        }
    } while (EXIT_SUCCESS);
}

bool CategoryAdmin::updateCourseInDB() {
    std::cout << "Update course menu " << "\n";

    DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
    dbManager.connect();
    bool exists;
    do {
        exists = dbManager.displayCourse();
        if (!exists) return EXIT_FAILURE;
        std::cout << "Enter the course code of the course you want to update: " << "\n";
        std::cin >> course_code;
        exists = ValidationCheck::validateCourseId(course_code);
        } while (!exists);

    do {
        exists = dbManager.searchCourse(course_code);
        if (exists) {
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
                    } while (!exists || exists && course_name == course_name_);
                    dbManager.updateCourse(course_code, course_name, department_);
                    course_name = course_name_;
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
                            exists = ValidationCheck::validateAllString(department);
                            //This was not correct so its exists
                        } else if (!exists) {
                            std::cout << "Enter new department where the course wil be taught: " << "\n";
                            std::cin >> department;
                            exists = ValidationCheck::validateAllString(department);
                        }
                    } while (!exists || exists && department == department_ );
                    dbManager.updateCourse(course_code, course_name_, department);
                    department = department_;
                } else {
                    std::cout << "Invalid choice. Please enter valid between (1-2)" << "\n";
                }
            } while (choice > 2 && choice < 0);
        } else {
            std::cout << "Could not processed because of the message above" << "\n";
            return false;
        }
    } while (false);
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
        std::cout << "5. View profile" << "\n";
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
    } while (choice != 0);
    return true;
}