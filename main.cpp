#include "PortalUsers.h"
#include <filesystem>
//int main() function will handle a case when the files are not yet made on a server: else take them to the logging page
struct DataTypes {
	std::string username;
	std::string password;
	std::string first_name;
	std::string last_name;
	std::string gender;
	int day, month, year;
};
bool checkLogin() {
	if (!login::handlingLogin()) {
		std::cout << "Credentials are not found in our records." << "\n";
		return false;
	}
	return true;
}
int main() {
	bool exists;
	struct DataTypes data;
	std::string queryFile = "Query.txt";
	std::cout << "Welcome to Computer Clinic Management Portal" << "\n";
	if (std::filesystem::exists("Query.txt")) {
		do {
			std::cout << "To log in" << "\n";
			do {
				std::cout << "Enter your username: ";
				std::cin >> data.username;
				exists = ValidationCheck::validateUsername(data.username);
			} while (!exists);
			do {
				std::cout << "Enter your password: ";
				std::cin >> data.password;
				exists = ValidationCheck::validatePassword(data.password);
			} while (!exists);
		}
		while(!checkLogin());
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
			std::cout << "=======================";
			std::cout << "# Male" << "\n";
			std::cout << "# Female" << "\n";
			std::cout << "======================";

			std::cout << "Enter your gender (Female or Male): " << "\n";
			std::cin >> data.gender;
			exists = ValidationCheck::validateGender(data.gender);
		} while (!exists);
		do {
			std::cout << "Enter your Date Of Birth (DD MM YYYY): " << "\n";
			std::cin >> data.day >> data.month >> data.year;
			exists = ValidationCheck::validateDOB(data.day, data.month, data.year);
		} while (!exists);

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
	}
	return 0;
}