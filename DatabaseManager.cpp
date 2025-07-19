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
			{"user", user_},
			{"password", password_}}
			);

		conn_ = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
		//Display << "connected to the MariaDB" << "\n";
		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return false;
	}
}


bool DatabaseManager::createUser(const std::string &username, const std::string &password,
	const std::string &first_name, const std::string &last_name,
	const std::string &category, const int& day,
	const int& month, const int& year) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Users (username, password, first_name,"
						   "last_name, category, birth_date) VALUES (?, ?, ?, ?, ?, ?)"));
		stmt->setString(1, username);
		stmt->setString(2, password);
		stmt->setString(3, first_name);
		stmt->setString(4, last_name);
		stmt->setString(5, category);
		std::string birth_date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
		stmt->setString(6, birth_date);  //this is dd/mm/yyyy format

		std::cout << "The user is successfully created" << "\n";
		return stmt->executeUpdate() > 0;
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

		std::cout << "The user is successfully deleted" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLDataException &e) {
		std::cerr << "Error deleting user: " << e.what() << "\n";
		return false;
	}
	return true;
}

bool DatabaseManager::updateUser(const std::string &username, const std::string &new_password,
	const std::string &new_first_name, const std::string &new_last_name,
	const std::string &new_category, const std::string &new_dob) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("UPDATE Users SET first_name = ?, last_name = ?,"
						   "password = ?, birth_date = ? WHERE username = ?"));
		stmt->setString(1, new_first_name);
		stmt->setString(2, new_last_name);
		stmt->setString(3, new_password);
		stmt->setString(4, new_dob);
		stmt->setString(5, username);

		std::cout << "The user is successfully updated" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error updating details: "  << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayUser() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT * FROM Users"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Username: " << res->getString("username");
			std::cout << ", User_ID: " << res->getInt("id");
			std::cout << ", First Name: " << res->getString("first_name");
			std::cout << ", Last Name: " << res->getString("last_name");
			std::cout << ", Category: " << res->getString("category");
			std::cout << ", birth_date: " << res->getString("birth_date");
			std::cout << ", created_at: " << res->getString("created_at") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of users in database: " << index << "\n";
			return true;
		} else {
			std::cout << "User table is empty" << "\n";
			return EXIT_FAILURE;
		}
	} catch (sql::SQLDataException& e) {
		std::cerr << "Error displaying user: " << e.what() << "\n";
		return false;
	}
}
bool DatabaseManager::searchUser(const std::string &username) {
	if (!conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt(
	conn_->prepareStatement("SELECT * FROM Users WHERE username =?"));
	stmt->setString(1, username);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
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
		conn_->prepareStatement("SELECT * FROM Users WHERE username = ? AND password = ?"));
	stmt->setString(1, username);
	stmt->setString(2, password);


	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		std::cout << "Login successful" << "\n";
		category = res->getString("category");
		return true;
	} else {
		std::cout << "Invalid credentials, please try again." << "\n";
		return false;
	}
}

bool DatabaseManager::viewProfile(const std::string& username) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("SELECT * FROM Users WHERE username = ?"));
		stmt->setString(1, username);

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		if (res->next()) {
			std::cout <<  "Username: " << res->getString("username");
			std::cout << ", User_ID: " << res->getInt("id");
			std::cout << ", First Name: " << res->getString("first_name");
			std::cout << ", Last Name: " << res->getString("last_name");
			std::cout << ", Category: " << res->getString("category");
			std::cout << ", birth_date: " << res->getString("birth_date");
			std::cout << ", created_at: " << res->getString("created_at") << "\n";
			return true;
		} else {
			std::cout << "Sorry could not display your profile lately,"
				"please contact +265994500600 " << username << "\n";
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error viewing profile: " << e.what() << "\n";
		return false;
	}
}


bool DatabaseManager::createCourse(const std::string &code, const std::string &name,
	const std::string &department, const int& semester) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("INSERT INTO Course (course_code, name,"
						   "department, semester) VALUES (?, ?, ?, ?)"));
		stmt->setString(1, code);
		stmt->setString(2, name);
		stmt->setString(3, department);
		stmt->setInt(4, semester);

		std::cout << "The course is successfully created" << "\n";
		return stmt->executeUpdate() > 0;
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

		std::cout << "The course is successfully deleted" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error deleting course: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::updateCourse(const std::string &code, const std::string &new_name,
	const std::string& new_department) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("UPDATE Course SET name = ?, department = ? WHERE course_code = ?"));
		stmt->setString(1, new_name);  //other its only updating one side the course name
		stmt->setString(2, new_department);
		stmt->setString(3, code);

		std::cout << "The course is successfully updated" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error updating details: "  << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayCourse() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt(
			conn_->prepareStatement("SELECT * FROM Course"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Course Code: " << res->getString("course_code");
			std::cout << ", Name: " << res->getString("name");
			std::cout << ", Department: " << res->getString("department");
			std::cout << ", Semester: " << res->getString("semester") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of courses in database: " << index << "\n";
			return true;
		} else {
			std::cout << "Course table is empty" << "\n";
			return false;
		}
	} catch (sql::SQLDataException& e) {
		std::cerr << "Error displaying course: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::searchCourse(const std::string &code) {
	if (!conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt(
	conn_->prepareStatement("SELECT * FROM Course WHERE course_code = ?"));
	stmt->setString(1, code);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		course_code_ = res->getString("course_code");
		department_ = res->getString("department");
		course_name_ = res->getString("name");
		std::cout << "found the course: " << code << " from the database" << "\n";
		return true;
	} else {
		std::cout << "No course found with course_code: " << code << "\n";
		return false;
	}
}

bool DatabaseManager::createStudent(const int &student_id, const std::string &class_,
	const int &user_id, const std::string &course_code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Students (student_id, class,"
						   "user_id, course_code) VALUES(?, ?, ?, ?, ?)"));
		stmt->setInt(1, student_id);
		stmt->setString(2, class_);
		stmt->setInt(3, user_id);
		stmt->setString(4, course_code);

		std::cout << "The student is successfully created" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error creating student: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::searchStudent(const int &user_id) {
	if (conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt (
		conn_->prepareStatement("SELECT * FROM Students where user_id = ?"));
	stmt->setInt(1, user_id);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		student_id_ = res->getInt("student_id");
		year_ = res->getString("year");
		std::cout << "found the student: " << user_id << " from the database" << "\n";
		return true;
	} else {
		stmt.reset(conn_->prepareStatement("SELECT * FROM Students WHERE student_id = ?"));
		stmt->setInt(1, user_id);

		res.reset(stmt->executeQuery());
		if (res->next()) {
			student_id_ = res->getInt("student_id");
		}
		return false;
	}
}


bool DatabaseManager::createTeacher(const int &teacher_id, const int &user_id, const std::string &office_number,
	const std::string &hire_date, const std::string &department, const std::string &course_code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Teachers (teacher_id, user_id, office_number,"
						   "hire_date, department, course_code) VALUES(?, ?, ?, ?, ?, ?)"));
		stmt->setInt(1, teacher_id);
		stmt->setInt(2, user_id);
		stmt->setString(3, office_number);
		stmt->setString(4, hire_date);
		stmt->setString(5, department);
		stmt->setString(6, course_code);

		std::cout << "The teacher is successfully created" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error creating teacher: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::numOfUsersThatLearnFromTeacher(const std::string& course_code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT * FROM Students WHERE course_code = ?"));
		stmt->setString(1, course_code);

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Username: " << res->getString("username");
			std::cout << ", User_ID: " << res->getInt("user_ID");
			std::cout << ", First Name: " << res->getString("first_name");
			std::cout << ", Last Name: " << res->getString("last_name") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of students: " << index << "\n";
			return true;
		} else {
			std::cout << "No student has enrolled to your course" << "\n";
			return false;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error getting the number of users that learn from your course" << "\n";
		return false;
	}
}

bool DatabaseManager::displayGPA() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT student_id, class, course_code, gpa FROM Students"));

		std::unique_ptr<sql::ResultSet> res (stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Student_ID: " << res->getInt("student_id");
			std::cout << ", Class: " << res->getString("class");
			std::cout << ", Course_code: " << res->getString("course_code");
			std::cout << ", GPA: " << res->getFloat("gpa");
		}
		if (index > 0) {
			std::cout << "Total number of students who have results: " << index << "\n";
			return true;
		} else {
			std::cout << "Student table is empty" << "\n";
			return EXIT_FAILURE;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error creating admin: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::uploadResults(const float &gpa, const int& student_id, const std::string& course_code) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("UPDATE Students SET gpa = ? WHERE student_id = ? AND course_code = ?"));
		stmt->setFloat(1, gpa);
		stmt->setInt(2, student_id);
		stmt->setString(3, course_code);

		std::cout << "The students results is successfully uploaded" << "\n";
		return stmt->executeUpdate() > 0;
	} catch (sql::SQLException& e) {
		std::cerr << "Error uploading results: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::searchTeacher(const int &user_id) {
	if (!conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt (
		conn_->prepareStatement("SELECT * FROM Teachers where user_id = ?"));
	stmt->setInt(1, user_id);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		teacher_id_ = res->getInt("teacher_id");
		std::cout << "found the teacher with user_ID: " << user_id << " from the database" << "\n";
		//do not get this course would be a list course_code_ = res->getString("course_code");
		//NOTE: We could use Vectors to store information or Lists to store that information and clean memory after
		//if later we want to get the lists of the course the teacher is teaching so that we can use them for data integrity
		//teacher is not allowed to claim accounts that it's theirs
		return true;
	} else {
		stmt.reset(conn_->prepareStatement("SELECT * FROM Teachers WHERE teacher_id = ?"));
		stmt->setInt(1, user_id);

		res.reset(stmt->executeQuery());
		if (res->next()) {
			teacher_id_ = res->getInt("teacher_id");
		}
		return false;
	}
}

bool DatabaseManager::createAdmin(const int &admin_id, const int &user_id, const std::string& department,
	const std::string& office_number, const std::string& hire_date) {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("INSERT INTO Admin (admin_id, user_id, department,"
						   "office_number, hire_date) VALUES(?, ?, ?, ?, ?)"));
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

bool DatabaseManager::searchAdmin(const int &user_id) { //search is used to either determine which user is logged in as admin or not
	if (!conn_) return false;

	std::unique_ptr<sql::PreparedStatement> stmt (
		conn_->prepareStatement("SELECT * FROM Admin WHERE user_id = ?"));
	stmt->setInt(1, user_id);

	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		admin_id_ = res->getInt("admin_id");
		std::cout << "found the admin: " << user_id << " from the database" << "\n";
		return true;
	} else { //here when the user is not found it may mean that his a new admin user so we have to check if the user_id is not the same in the database
		stmt.reset(conn_->prepareStatement("SELECT * FROM Admin WHERE admin_id = ?"));
		stmt->setInt(1, user_id);

		res.reset(stmt->executeQuery());
		if (res->next()) {
			admin_id_ = res->getInt("admin_id");
		}
		return false;
	}
}

bool DatabaseManager::displayStudent() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT * FROM Students"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while ( res->next()) {
			std::cout << ++index << ". Student_ID: " << res->getInt("student_id");
			std::cout << ", Class: " << res->getString("class");
			std::cout << ", User_ID: " << res->getInt("user_id");
			std::cout << ", GPA: " << res->getFloat("gpa");
			std::cout << ", Enrollment_date: " << res->getString("enrollment_date");
			std::cout << ", Course_code: " << res->getString("course_code");
			std::cout << ", Semester: " << res->getInt("semester") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of students in database: " << index << "\n";
			return true;
		} else {
			std::cout << "Student table is empty" << "\n";
			return EXIT_FAILURE;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error displaying student: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayTeacher() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT * FROM Teachers"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Teacher_ID: " << res->getInt("teacher_id");
			std::cout << ", User_ID: " << res->getInt("class");
			std::cout << ", Office_number: " << res->getString("user_id");
			std::cout << ", Hire_date: " << res->getString("hire_date");
			std::cout << ", Department: " << res->getString("department");
			std::cout << ", Course_code: " << res->getString("course_code");
			std::cout << ", Semester: " << res->getInt("semester") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of teachers in database: " << index << "\n";
			return true;
		} else {
			std::cout << "Teacher table is empty" << "\n";
			return EXIT_FAILURE;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error displaying teacher: " << e.what() << "\n";
		return false;
	}
}

bool DatabaseManager::displayAdmin() {
	try {
		if (!conn_) return false;

		std::unique_ptr<sql::PreparedStatement> stmt (
			conn_->prepareStatement("SELECT * FROM Admin"));

		std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
		int index = 0;
		while (res->next()) {
			std::cout << ++index << ". Admin_ID: " << res->getInt("teacher_id");
			std::cout << ", User_ID: " << res->getInt("class");
			std::cout << ", Department: " << res->getString("user_id");
			std::cout << ", Office_number: " << res->getString("hire_date");
			std::cout << ", Hire_date: " << res->getString("department") << "\n";
		}
		if (index > 0) {
			std::cout << "Total number of admins in database: " << index << "\n";
			return true;
		} else {
			std::cout << "Teacher table is empty" << "\n";
			return EXIT_FAILURE;
		}
	} catch (sql::SQLException& e) {
		std::cerr << "Error displaying teacher: " << e.what() << "\n";
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


