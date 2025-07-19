#include "ModifyPortalUsers.h"  //modifies users profile
#include "UtililtyHandler.h"    //handles functionalities of students
#include "DatabaseManager.h"    //Database operations
#include "HandleMenus.h"
#include "HandlingValidationCheck.h"
#include <iostream>

inline std::string category;

//int main() function will handle a case when the files are not yet made on a server: else take them to the logging page
struct DataTypes {
	std::string username;
	std::string password;
	std::string first_name;
	std::string last_name;
	std::string category;
	int day{}, month{}, year{};
};

int main() {
	DataTypes data;
	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
	if(!dbManager.connect()) {
		return 1; // Exit if connection fails
	}
	bool exists;
	char option;
	do {
		std::cout << "Welcome to Computer Clinic Management Portal" << "\n";
		std::cout << "Do you already have an account?yes for '(Y or y)' OR no for '(N or n)': " << "\n";
		std::cin >> option;
		if (option == 'Y' || option == 'y') {
			do {
				do {
					std::cout << "Enter your username: ";
					std::cin >> data.username;
					exists = ValidationCheck::validateUsername(data.username);
				} while (!exists); system("clear");
				do {
					std::cout << "Enter your password: ";
					std::cin >> data.password;
					exists = ValidationCheck::validatePassword(data.password);
				} while (!exists); system("clear");
			} while(!dbManager.authenticateUser(data.username, data.password));

		} else if (option == 'n' || option == 'N') {
			do {
				std::cout << "Enter your username: " << "\n";
				std::cin >> data.username;
				exists = ValidationCheck::validateUsername(data.username);
			} while (!exists);
			exists = dbManager.searchUser(data.username);
			std::system("clear");  //this will remove the details from the search
			while (exists) {
				do {
					std::cout << "Username already exists, please try another another username." << "\n";
					std::cout << "Enter your username: " << "\n";
					std::cin >> data.username;
					exists = ValidationCheck::validateUsername(data.username);
					system("clear");
				} while (!exists);
				exists = dbManager.searchUser(data.username);
				if (exists == false) {
					break; // Exit the loop if username is not found
				}
			}
			do {
				std::cout << "Enter your password: " << "\n";
				std::cin >> data.password;
				exists = ValidationCheck::validatePassword(data.password);
				system("clear");
			} while (!exists);
			do {
				std::cout << "Enter your first name: " << "\n";
				std::cin >> data.first_name;
				exists = ValidationCheck::validateFirstName(data.first_name);
				system("clear");
			} while (!exists);
			do {
				std::cout << "Enter last name: " << "\n";
				std::cin >> data.last_name;
				exists = ValidationCheck::validateLastName(data.last_name);
				system("clear");
			} while (!exists);
			do {
				std::cout << "Who are you signing up as \n Are you either 'student, teacher or admin'?" << "\n";
				std::cout << "Enter your category: " << "\n";
				std::cin >> data.category;
				exists = ValidationCheck::validateCategory(data.category);
				system("clear");
			} while (!exists);
			do {
				std::cout << "Enter your Date Of Birth:" << "\n";
				std::cout << "Day(DD): ";
				std::cin >> data.day;
				std::cout << "Month(MM): ";
				std::cin >> data.month;
				std::cout << "Year(YYYY): ";
				std::cin >> data.year;
				exists = ValidationCheck::validateDOB(data.day, data.month, data.year);
				system("clear");
			} while (!exists);
			//now create the user in the database
			dbManager.createUser(data.username, data.password,
				data.first_name, data.last_name,
				data.category, data.day,
				data.month, data.year);
		} else {
			std::cout << "Invalid choice option" << "\n";
			std::cout << "option must be either yes('y' or 'Y') or no('n' or 'N')" << "\n";
		}
			{
				//when the user is signing up
				Menu menu(data.username, data.category);
				menu.studentMenu();
				menu.teacherMenu();
				menu.adminMenu();
			}
			{
				//when the user is already logged in
				Menu menu(data.username, category);
				menu.studentMenu();
				menu.teacherMenu();
				menu.adminMenu();
			}

	} while (option != 'y' || option != 'Y' || option != 'n' || option != 'N');  //so that the user inputs either yes or no


	return 0;
}