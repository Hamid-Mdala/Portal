#include "DatabaseManager.h"
#include <iostream>
#include <memory>
#include <mariadb/conncpp.hpp>
#include <utility>

DatabaseManager::DatabaseManager(std::string user, std::string password, std::string db)
	: user_(std::move(user)), password_(std::move(password)), db_(std::move(db))
{}
bool DatabaseManager::connect() {
	try {
		sql::Driver *driver = sql::mariadb::get_driver_instance();
		sql::SQLString url("jdbc:mariadb://localhost:3306/" + db_);
		sql::Properties properties({
			{"user", user_},       //admin username
			{"password", password_}}
			);

		conn_ = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
		//Display << "connected to the MariaDB" << "\n";
		return true;
	} catch (sql::SQLException& e) {    //this is for error condition using mariaDB
		std::cerr << "Error: " << e.what() << "\n";
		return false;
	}
}


bool DatabaseManager::createUser(const std::string &username, const std::string &password,
	const std::string &first_name, const std::string &last_name,
	const std::string &category, const int& day,
	const int& month, const int& year)
{
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Users (username, password, first_name, last_name, category, birth_date) VALUES (?, ?, ?, ?, ?, ?)")); //insert the fields in the User table with no value
		stmt->setString(1, username);
		stmt->setString(2, password);
		stmt->setString(3, first_name);
		stmt->setString(4, last_name);
		stmt->setString(5, category);

		std::string birth_date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
		stmt->setString(6, birth_date);  //this is dd/mm/yyyy format
		std::cout << "The user is successfully created" << "\n";

		return stmt->executeUpdate() > 0; //returns true if the user is created successfully
	} catch (sql::SQLDataException& e) {
		std::cerr << "User creation failed: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::deleteUser(const std::string &username) {
	try {
		if (!conn_) return false;
		std::unique_ptr<sql::PreparedStatement> stmt (
				conn_->prepareStatement("DELETE FROM Users WHERE username = ?"));
		stmt->setString(1, username);

		if (int affected_rows = stmt->executeUpdate(); affected_rows > 0) {
			std::cout << "removed the user: " << username << " from the database" << "\n";
		} else {
			std::cout << "Can not delete user because the user is not found: " << username << "\n";
			return false;
		}
	} catch (sql::SQLDataException &e) {
		std::cerr << "Error deleting user: " << e.what() << "\n";
		return false;
	}
	return true;
}

bool DatabaseManager::updateUser(const std::string &username, const std::string &new_password, const std::string &new_first_name, const std::string &new_last_name, const std::string &new_category, const std::string &new_dob) {

	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("UPDATE Users SET first_name = ?, last_name = ?, password = ?, birth_date = ? WHERE username = ?"));
		stmt->setString(1, new_first_name);
		stmt->setString(2, new_last_name);
		stmt->setString(3, new_password);
		stmt->setString(4, new_dob);
		stmt->setString(5, username);

		if (int affected_rows = stmt->executeUpdate(); affected_rows > 0) {
			std::cout << "Successfully updated the user: " << username << " in the database" << "\n";
			return true;
		} else  {
			std::cout << "Can not update user because the user is not found: " << username << "\n";
			return false;
		}


	} catch (sql::SQLException& e) {
		std::cerr << "Error updating details: "  << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayUser(const std::string& username, const std::string& category) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SHOW COLUMN username, first_name, last_name, category, birth_date FROM Users"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next() && res->getInt(1)) {
			int index = 0;
			std::cout << ++index << ". Username: " << res->getString("username");
			std::cout << ",First Name: " << res->getString("first_name");
			std::cout << ",Last Name: " << res->getString("last_name");
			std::cout << ",Category: " << res->getString("category");
			std::cout << ",birth_date: " << res->getString("birth_date") << "\n";
			std::cout << "Total number of users in database: " << index << "\n";
			return true;
		} else {
			std::cout << "No user found with username: " << username << "\n";
			return false;
		}
	} catch (sql::SQLDataException& e) {
		std::cerr << "Error displaying user: " << e.what() << "\n";
		return false;
	}
}
bool DatabaseManager::searchUser(const std::string &username) {
	if (!conn_) return false;
	//make a statement
	std::unique_ptr<sql::PreparedStatement> stmt(
	conn_->prepareStatement("SELECT COUNT(*) FROM Users WHERE username =?"));
	stmt->setString(1, username);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next() && res->getInt(1)) {
		std::cout << "found the user: " << username << " from the database" << "\n";
		return true;
	} else {
		std::cout << "No user found with username: " << username << "\n";
		return false;
	}
}

bool DatabaseManager::authenticateUser(const std::string& username, const std::string& password) {
	if (!conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt(
		conn_->prepareStatement("SELECT * FROM Users WHERE username =? AND password =?"));
	stmt->setString(1, username);   //this is the username from the user while logging in
	stmt->setString(2, password);   //this is the password from the user while logging in


	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next() && res->getInt(1)) {
		std::cout << "Login successful" << "\n";
		category = res->getString("category");
		return true;
	}
	std::cout << "Invalid credentials, please try again." << "\n";
	return false;
}

bool DatabaseManager::createCourse(const std::string &code, const std::string &name, const std::string &department) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("INSERT INTO Course (course_code, name, department) VALUES (?, ?, ?)"));
		stmt->setString(1, code);
		stmt->setString(2, name);
		stmt->setString(3, department);

		return stmt->executeUpdate() > 0; //returns true if the course is created successfully
	} catch (sql::SQLDataException& e) {
		std::cerr << "Course creation failed: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::deleteCourse(const std::string &code) {
	try {
		if (!conn_) return false;
		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("DELETE FROM Course WHERE course_code = ?"));
		stmt->setString(1, code);

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next() && res->getInt(1)) {
			std::cout << "Successfully removed the course: " << code << " from the database" << "\n";
			return true;
		} else {
			std::cout << "No courses found with code: " << code << "\n";
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error deleting course: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::updateCourse(const std::string &code, const std::string &new_name, const std::string &new_department) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("UPDATE Course SET name = ?, department = ? WHERE code = ?"));
		stmt->setString(1, new_name);
		stmt->setString(2, new_department);
		stmt->setString(3, code);

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next() && res->getInt(1)) {
			std::cout << "Successfully updated the user: " << code << " in the database" << "\n";
			return true;
		} else {
			std::cout << "No courses found with code: " << code << "\n";
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error updating details: "  << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayCourse(const std::string &code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("SHOW COLUMN course_code, name, department FROM Course"));
		stmt->setString(1, code);

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next() && res->getInt(1)) {
			std::cout << "Course Code: " << res->getString("course_code");
			std::cout << ", Name: " << res->getString("name");
			std::cout << ", Department: " << res->getString("department") << "\n";
			return true;
		} else {
			std::cout << "No courses found with the code: " << code << "\n";
			return false;
		}
	} catch (sql::SQLDataException& e) {
		std::cerr << "Error displaying course: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::searchCourse(const std::string &code) {
	if (!conn_) return false;
	//make a statement
	std::unique_ptr<sql::PreparedStatement> stmt(
	conn_->prepareStatement("SELECT COUNT(*) FROM Course WHERE code = ?"));
	stmt->setString(1, code);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next() && res->getInt(1)) {
		std::cout << "Successfully removed the user: " << code << "from the database" << "\n";
		return true;
	}
	return false;
}

bool DatabaseManager::createStudent(const int &student_id, const std::string &class_,
	const int &user_id, const float &gpa,
	const std::string &course_code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Students (student_id, class, user_id, gpa, course_code) VALUES(?, ?, ?, ?, ?)"));
		stmt->setInt(1, student_id);
		stmt->setString(2, class_);
		stmt->setInt(3, user_id);
		stmt->setFloat(4, gpa);
		stmt->setString(5, course_code);

		std::cout << "The student is successfully created" << "\n";
		return stmt->executeUpdate() > 0;

	} catch (sql::SQLException& e) {
		std::cerr << "Error creating student: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::createAdmin(const int &admin_id, const int &user_id, const std::string& department,
	const std::string& office_number, const std::string& hire_date) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Admin (admin_id, user_id, department, office_number, hire_date) VALUES(?, ?, ?, ?, ?)"));
		stmt->setInt(1, admin_id);
		stmt->setInt(2, user_id);
		stmt->setString(3, department);
		stmt->setString(4, office_number);
		stmt->setString(5, hire_date);

		std::cout << "The admin is successfully created" << "\n";
		return stmt->executeUpdate() > 0;

	} catch (sql::SQLException& e) {
		std::cerr << "Error creating admin: " << e.what() << "\n";
		return false;
	}
}

void DatabaseManager::setConnection(std::unique_ptr<sql::Connection> conn) {conn_ = std::move(conn);}
sql::Connection& DatabaseManager::getConnectionRef() {
	if (!conn_) {
		throw std::runtime_error("Database connection is not established.");
	}
	return *conn_;
}

void DatabaseManager::setUser(const std::string &user) {user_ = user;}
std::string DatabaseManager::getUser() { return user_;}

void DatabaseManager::setPassword(const std::string &password) {password_ = password;}
std::string DatabaseManager::getPassword() {return password_;}

void DatabaseManager::setDb(const std::string &db) {db_ = db;}
std::string DatabaseManager::getDb() {return db_;}


