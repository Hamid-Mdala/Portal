#include "PortalUsers.h"
#include <filesystem>
//int main() function will handle a case when the files are not yet made on a server: else take them to the logging page
struct DataTypes {
	std::string username;
	std::string password;
	std::string first_name;
	std::string last_name;
	std::string category;
	int day, month, year;
};
// bool checkLogin() {
// 	if (!login::handlingLogin()) {
// 		std::cout << "Credentials are not found in our records." << "\n";
// 		return false;
// 	}
// 	return true;
// }
int main() {
	DataTypes data;
	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
	if(!dbManager.connect()) {
		return 1; // Exit if connection fails
	}
	bool exists;
	// struct DataTypes data;
	char option;
	std::cout << "Welcome to Computer Clinic Management Portal" << "\n";
	std::cout << "Do you already have an account?yes for '(Y or y)' OR no for '(N or n)': " << "\n";
	std::cin >> option;
	if (option == 'Y' || option == 'y') {
		do {
			do {
				std::cout << "Enter your username: ";
				std::cin >> data.username;
				exists = ValidationCheck::validateUsername(data.username);

			} while (!exists);
			exists = dbManager.searchUser(data.username);
			do {
				std::cout << "Enter your password: ";
				std::cin >> data.password;
				exists = ValidationCheck::validatePassword(data.password);
			} while (!exists);

		} while(!dbManager.authenticateUser(data.username, data.password));

	} else {
		do {
			std::cout << "Enter your username: " << "\n";
			std::cin >> data.username;
			exists = ValidationCheck::validateUsername(data.username);
		} while (!exists);
		do {
			std::cout << "Enter your password: " << "\n";
			std::cin >> data.password;
			exists = ValidationCheck::validatePassword(data.password);
		} while (!exists);
		do {
			std::cout << "Enter your first name: " << "\n";
			std::cin >> data.first_name;
			exists = ValidationCheck::validateFirstName(data.first_name);
		} while (!exists);
		do {
			std::cout << "Enter last name: " << "\n";
			std::cin >> data.last_name;
			exists = ValidationCheck::validateLastName(data.last_name);
		} while (!exists);
		do {
			std::cout << "Who are you signing up as \n Are you either 'student, teacher or admin'"
			std::cout << "Enter your category: " << "\n";
			std::cin >> data.category;
			exists = ValidationCheck::validateCategory(data.category);
		} while (!exists);
		do {
			std::cout << "Enter your Date Of Birth (DD MM YYYY): " << "\n";
			std::cin >> data.day >> data.month >> data.year;
			exists = ValidationCheck::validateDOB(data.day, data.month, data.year);
		} while (!exists);
	}




		// while (true) {
		// 	ofstream outFile("temp_file_one.txt");
		// 	ofstream otherOutFile("temp_file_two.txt");
		// 	outFile.close();
		// 	otherOutFile.close();
		// 	if (login::handlingLogin()) {
		//               break;
		//           }
		// 	system("CLS");
		// }

	return 0;
}