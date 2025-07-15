#include "ModifyPortalUsers.h"
#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"
#include <mariadb/conncpp.hpp>
#include <memory>


User::User(const string& username) {
	//so if we search for the unique username let us get the fields
	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
	dbManager.connect();
	sql::Connection& conn_ = dbManager.getConnectionRef();

	std::unique_ptr<sql::PreparedStatement> stmt(
		conn_.prepareStatement("SELECT * FROM Users WHERE username = ?"));
	stmt->setString(1, username);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next() && res->getInt(1)) {
		username_ = username;
		password_ = res->getString("password");
		first_name = res->getString("first_name");
		last_name = res->getString("last_name");
		category = res->getString("category");
		birth_date = res->getString("birth_date");
	} else {
		std::cout << "Error: User not found." << "\n";
	}
}

void User::setUsername(const string& username) {username_ = username;}
string User::getUsername() {return username_;}

void User::setPassword(const string& password) {password_ = password;}
string User::getPassword() {return password_;}

// bool User::view() {
// 	//view algorithm for user used to view all the users file in the management system,
// 	//However it is possible for the function to change completely under other user's implementation
// 	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
// 	dbManager.displayUser(username_, category);
// 	return true;
// }

bool User::editPassword() {
	bool exists;
	std::string old_pass;
	std::string new_pass;
	do {
		std::cout << "Please Enter Old Password: ";
		std::cin >> old_pass;

		while (old_pass != password_) {
			std::cout << "Incorrect password!" << "\n";
			std::cout << "Please Enter Old Password: ";
			std::cin >> old_pass;
		}
		exists = ValidationCheck::validatePassword(old_pass);
	} while (!exists);

	if (password_ == old_pass) {
		do {
			std::cout << "Please Enter New Password: ";
			std::cin >> new_pass;

			while (new_pass == old_pass) {
				std::cout << "The new password cannot be the same as the old password. Please enter a different password." << "\n";
				std::cout << "Please Enter New Password: ";
				std::cin >> new_pass;
			}
			exists = ValidationCheck::validatePassword(new_pass);
		} while (!exists);

		std::string confirm_pass;
		do {
			std::cout << "Confirm Password: ";
			std::cin >> confirm_pass;

			while (confirm_pass != new_pass) {
				std::cout << "The confirmation password does not match the new password. Please try again." << "\n";
				std::cout << "Confirm Password: ";
				std::cin >> confirm_pass;
			}
			exists = ValidationCheck::validatePassword(confirm_pass);
		} while (!exists);
	}

	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();  //when i make the contractor I must always make a new connection

		dbManager.updateUser(username_, new_pass, first_name, last_name, category, birth_date);

	}
	return true;
}



bool User::editFirstName() {
	bool exists;
	std::string f_name;
	do {
		std::cout << "Please Enter New First Name: ";
		std::cin >> f_name;
		exists = ValidationCheck::validateFirstName(f_name);
	} while (!exists);

	do {
		if (exists && f_name == first_name) {std::cout << "You entered your old first name." << "\n";
			std::cout << "Please Enter New first Name: ";
			std::cin >> f_name;
			exists = ValidationCheck::validateFirstName(f_name);
		} else if (!exists) {
			std::cout << "Please Enter New first Name: ";
			std::cin >> f_name;
			exists = ValidationCheck::validateFirstName(f_name);
		}
	} while (!exists || f_name == first_name);
	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		dbManager.updateUser(username_, password_, f_name, last_name, category, birth_date);
		first_name = f_name; //update the first name in the constructor so that in code everything goes well
	}
	return true;
}

bool User::editLastName() {
	bool exists;
	std::string l_name;
	do {
		std::cout << "Please Enter New Last Name: ";
		std::cin >> l_name;
		exists = ValidationCheck::validateLastName(l_name);
	} while (!exists);

	do {
		if (exists && l_name == last_name) {std::cout << "You entered your old last name." << "\n";
			std::cout << "Please Enter New Last Name: ";
			std::cin >> l_name;
			exists = ValidationCheck::validateLastName(l_name);
		} else if (!exists) {
			std::cout << "Please Enter New Last Name: ";
			std::cin >> l_name;
			exists = ValidationCheck::validateLastName(l_name);
		}
	} while (!exists || l_name == last_name);
	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		dbManager.updateUser(username_, password_, first_name, l_name, category, birth_date);
		last_name = l_name; //update the first name in the constructor so that in code everything goes well
	}
	return true;
}

bool User::editDOB() {
	bool exists;
	int day, month, year;
	do {
		std::cout << "Enter your new date of birth (DD MM YYYY)" << "\n";
		std::cout << "Day(DD): ";
		std::cin >> day;
		std::cout << "Month(MM): ";
		std::cin >> month;
		std::cout << "Year(YYYY): ";
		std::cin >> year;
		exists = ValidationCheck::validateDOB(day, month, year);

	} while (!exists);
	{
		std::string new_dob = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.connect();
		dbManager.updateUser(username_, password_, first_name, last_name, category, new_dob);
	}
	return true;
}
