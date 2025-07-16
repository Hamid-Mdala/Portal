#include "HandleMenus.h"

#include <filesystem>

#include "UtililtyHandler.h"
#include <utility>

#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"

Menu::Menu(const std::string& username, const std::string& category) {
	username_ = username;
	category_ = category;
}

bool Menu::studentMenu() {
	while(category_ == "student") {
		CategoryStudent studentUser(username_);
		int choice;
		do {
			std::cout << "1. Enroll into course" << "\n";
			std::cout << "2. Get results score" << "\n";
			std::cout << "3. Update profile" << "\n";
			std::cout << "4. Delete profile" << "\n";
			std::cout << "Note: enter 0 to end program" << "\n";
			std::cout << "Enter your choice: " << "\n";
			std::cin >> choice;
			system("clear");

			if (choice == 1) {
				studentUser.enrollCourse();
			} else if (choice == 2) {
				studentUser.getResults();
			} else if (choice == 3) {
				studentUser.updateProfile();
			} else if (choice == 4) {
				studentUser.deleteProfile();
			} else if (choice == 0) {
				std::cout << "Ended program.." << "\n";
				std::exit(EXIT_SUCCESS);
			} else {
				std::cout << "Please enter a valid choice between (1-4)" << "\n";
			}
		} while (choice != 0);
	}
	return true;
}

bool Menu::teacherMenu() {
	while (category_ == "teacher") {
		//the teacher is able to view and get the semester by the admin in the course table
		CategoryTeacher teacherUser(username_);
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		sql::Connection& conn_ = dbManager.getConnectionRef();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
		stmt->setString(1, username_);

		if (std::unique_ptr<sql::ResultSet> res(stmt->executeQuery()); res->next()) {
			int user_id = res->getInt("id");
			if (bool exists = dbManager.searchTeacher(user_id)) {
				int choice;
				do {
					std::cout << "1. View" << "\n";
					std::cout << "2. Upload GPA" << "\n";
					std::cout << "3. Update GPA" << "\n";
					std::cout << "4. Update Profile" << "\n";
					std::cout << "5. Delete Profile" << "\n";
					std::cout << "Note: enter 0 to end program" << "\n";
					std::cout << "Enter your choice: " << "\n";
					std::cin >> choice;
					system("clear");

					if (choice == 1) {
						teacherUser.teacherView();
					} else if (choice == 2) {
						teacherUser.uploadGPA();
					} else if (choice == 3) {
						teacherUser.updateGPA();
					} else if (choice == 4) {
						teacherUser.updateProfile();
					} else if (choice == 5) {
						teacherUser.deleteProfile();
					} else if (choice == 0) {
						std::cout << "Ended program.." << "\n";
						std::exit(EXIT_SUCCESS);
					} else {
						std::cout << "Invalid choice. Please enter value between (1-3)" << "\n";
					}
				} while (choice != 0);

			} else {
				int teacher_id, day, month, year;
				std::string department_, course_code, office_number;
				do {
					std::cout << "What is your Identification Number(ID): " << "\n";
					std::cin >> teacher_id;
					exists = ValidationCheck::validateId(teacher_id);
				} while (!exists);
				bool check;
				do {
					exists = dbManager.searchTeacher(teacher_id);
					if (exists) {
						std::cout << "Identification Number(ID) already exist" << "\n";
						std::cout << "What is your Identification Number(ID): " << "\n";
						std::cin >> teacher_id;
						check = ValidationCheck::validateId(teacher_id);
					}
				} while (exists || !check);
				do {
					std::cout << "What is your office (room number): " << "\n";
					std::cin >> office_number;
					exists = ValidationCheck::validateAllString(office_number);
				} while (!exists);
				do {
					std::cout << "Which department do you work-in this corporation: " << "\n";
					std::cin >> department_;
					exists = ValidationCheck::validateAllString(department_);
				} while (!exists);
				do {
					std::cout << "What was your hire date: " << "\n";
					std::cout << "Day(DD): ";
					std::cin >> day;
					std::cout << "Month(MM): ";
					std::cin >> month;
					std::cout << "Year(YYYY): ";
					std::cin >> year;
					exists = ValidationCheck::validateDOB(day, month, year);
				} while (!exists);
				do {
					exists = dbManager.displayCourse();
					//NOTE: If the course table does not exist the program ends
					//NOTE: If the course table does exist the program continues
				} while (!exists);
				do {
					std::cout << "What course code are you teaching?" << "\n";
					std::cin >> course_code;
					exists = ValidationCheck::validateCourseId(course_code);
				} while (!exists);
				bool check;
				do {
					exists = dbManager.searchCourse(course_code);
					if (!exists) {
						std::cout << "Course is not found" << "\n";
						std::cout << "What is your course code you are learning?" << "\n";
						std::cin >> course_code;
						check = ValidationCheck::validateCourseId(course_code);
					}
				} while (!exists || !check);
				{
					std::string hire_date;
					hire_date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
					dbManager.createTeacher(teacher_id, user_id, office_number, hire_date, department_, course_code);
				}
			}
		} else {
			std::cout << "Couldn't find user" << "\n";
			std::cout << "Please report to the software engineer teem to fix your issue" << "\n";
			std::exit(EXIT_FAILURE);
		}
	}
	return true;
}

bool Menu::adminMenu() {
	while (category_ == "admin") {
		//admin has access to full database controls
		CategoryAdmin adminUser(username_);
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		sql::Connection& conn_ = dbManager.getConnectionRef();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
		stmt->setString(1, username_);

		if (std::unique_ptr<sql::ResultSet> res(stmt->executeQuery()); res->next()) {
			int user_id = res->getInt("id");
			if (bool exists = dbManager.searchAdmin(user_id)) {
				int choice;
				do {
					std::cout << "1. View" << "\n";
					std::cout << "2. Create course" << "\n";
					std::cout << "3. Update course" << "\n";
					std::cout << "4. Delete course" << "\n";
					std::cout << "5. Update Profile" << "\n";
					std::cout << "6. Delete Profile" << "\n";
 					std::cout << "Note: enter 0 to end program" << "\n";
					std::cout << "Enter your choice: " << "\n";
					std::cin >> choice;
					system("clear");

					if (choice == 1) {
						adminUser.adminView();
					} else if (choice == 2) {
						adminUser.makeCourseInDB();
					} else if (choice == 3) {
						adminUser.updateCourseInDB();
					} else if (choice == 4) {
						adminUser.removeCourseInDB();
					} else if (choice == 5) {
						adminUser.updateProfile();
					} else if (choice == 6) {
						adminUser.deleteProfile();
					}
					else if (choice == 0) {
						std::cout << "Ended program.." << "\n";
						std::exit(EXIT_SUCCESS);
					} else {
						std::cout << "Invalid choice. Please enter value between (1-3)" << "\n";
					}
				} while (choice != 0);
			} else {
				int admin_id, day, month, year;
				std::string department_, office_number;
				do {
					std::cout << "What is your Identification Number(ID): " << "\n";
					std::cin >> admin_id;
					exists = ValidationCheck::validateId(admin_id);
				} while (!exists);
				bool check;
				do {
					exists = dbManager.searchAdmin(admin_id);
					if (exists) {
						std::cout << "Identification Number(ID) already exists" << "\n";
						std::cout << "What is your Identification Number(ID): " << "\n";
						std::cin >> admin_id;
						check = ValidationCheck::validateId(admin_id);
					}
				} while (exists || !check);
				do {
					std::cout << "What is your office (room number): " << "\n";
					std::cin >> office_number;
					exists = ValidationCheck::validateAllString(office_number);
				} while (!exists);
				do {
					std::cout << "Which department do you work-in this corporation: " << "\n";
					std::cin >> department_;
					exists = ValidationCheck::validateAllString(department_);
				} while (!exists);
				do {
					std::cout << "What was your hire date: " << "\n";
					std::cout << "Day(DD): ";
					std::cin >> day;
					std::cout << "Month(MM): ";
					std::cin >> month;
					std::cout << "Year(YYYY): ";
					std::cin >> year;
					exists = ValidationCheck::validateDOB(day, month, year);
				} while (!exists);
				{
					std::string hire_date;
					hire_date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
					dbManager.createAdmin(admin_id, user_id, department_, office_number, hire_date);
				}
			}
		} else {
			std::cout << "Couldn't find user" << "\n";
			std::cout << "Please report to the software engineer teem to fix your issue" << "\n";
			std::exit(EXIT_FAILURE);
		}
	}
	return true;
}