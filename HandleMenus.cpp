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
				std::exit(EXIT_SUCCESS);  //end the program
			} else {
				std::cout << "Please enter a valid choice between (1-4)" << "\n";
			}
		} while (choice != 0);
	}
	return true;
}

bool Menu::teacherMenu() {
	while (category_ == "teacher") {
		//the teacher is able to view the semester made by the admin in the course table
		CategoryTeacher teacherUser(username_);
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		sql::Connection& conn_ = dbManager.getConnectionRef();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
		stmt->setString(1, username_);

		if (std::unique_ptr<sql::ResultSet> res(stmt->executeQuery()); res->next()) {
			int user_id = res->getInt("id");

			stmt.reset(conn_.prepareStatement("SELECT * FROM Teachers WHERE user_id = ?"));
			stmt->setInt(1, user_id);

			res.reset(stmt->executeQuery());
			if (res->next()) {
				int choice;
				do {
					std::cout << "1. View" << "\n";   //this view the students enrolled into his course
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

					} else if (choice == 3) {

					} else if (choice == 4) {
						teacherUser.updateProfile();
					} else if (choice == 5) {
						teacherUser.deleteProfile();
					} else if (choice == 0) {

					} else {

					}
				} while (choice != 0);

			} else {
				//todo: have to add the enter id, office number, department, hire date  just like admin
				//however on the course code i have to input the course code that i am given in the school
				//and i have to check if the course exists in db
				//as i do this i can see when the course is taught in the semester column
				int teacher_id, day, month, year;
				std::string department_, course_code, office_number;
				bool exists;
				do {
					std::cout << "What is your Identification Number(ID): " << "\n";
					std::cin >> teacher_id;  //add verification mechanism
					exists = ValidationCheck::validateId(teacher_id);
					do {
						stmt.reset(conn_.prepareStatement("SELECT * FROM Admin WHERE admin_id = ?"));

						stmt->setInt(1, teacher_id);
						res.reset(stmt->executeQuery());
						if (res->next()) {
							std::cout << "Identification Number(ID) already exists" << "\n";
							std::cout << "What is your Identification Number(ID): " << "\n";
							std::cin >> teacher_id;
							exists = ValidationCheck::validateId(teacher_id);
						}
					}while (res->next());
				} while (!exists);

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

				//before search check if the course table has columns using the course display
				do {
					exists = dbManager.displayCourse();
					if (!exists) {
						std::cout << "The admin has not yet created any course in the database" << "\n";
						std::cout << "Due to the above you can not processed in creating your teacher account" << "\n";
						return EXIT_SUCCESS;
					} else {
						do {
							std::cout << "What course code are you teaching?" << "\n";
							std::cin >> course_code;
							exists = ValidationCheck::validateCourseId(course_code);
							if (!exists) {
								return false;
							} else {
								do {
									exists = dbManager.searchCourse(course_code);
									if (!exists) {
										return false;
									} else {
										std::cout << "processing information" << "\n";
									}
								} while (false);
							}
						} while (false);
					}
				} while (!exists);
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
	while (category_ == "admin") {  //admin has access to full database controls that is why we
		CategoryAdmin adminUser(username_);
		//sign up an account in the admin database
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		sql::Connection& conn_ = dbManager.getConnectionRef();

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
		stmt->setString(1, username_);

		if (std::unique_ptr<sql::ResultSet> res(stmt->executeQuery()); res->next()) {
			int user_id = res->getInt("id");

			stmt.reset(conn_.prepareStatement("SELECT * FROM Admin WHERE user_id = ?"));
			stmt->setInt(1, user_id);

			res.reset(stmt->executeQuery());
			if (res->next()) {
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
				bool exists;
				do {
					std::cout << "What is your Identification Number(ID): " << "\n";
					std::cin >> admin_id;  //add verification mechanism
					exists = ValidationCheck::validateId(admin_id);
					do {
						stmt.reset(conn_.prepareStatement("SELECT * FROM Admin WHERE admin_id = ?"));

						stmt->setInt(1, admin_id);
						res.reset(stmt->executeQuery());
						if (res->next()) {
							std::cout << "Identification Number(ID) already exists" << "\n";
							std::cout << "What is your Identification Number(ID): " << "\n";
							std::cin >> admin_id;
							exists = ValidationCheck::validateId(admin_id);
						}
					}while (res->next());
				} while (!exists);

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
