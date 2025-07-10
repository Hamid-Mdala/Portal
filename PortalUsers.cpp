#include "PortalUsers.h"
#include "DatabaseManager.h"
#include "HandlingValidationCheck.h"
#include <mariadb/conncpp.hpp>
#include <memory>

//static std::string user_name;

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
		//user_name = username; // Store the username for later use
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
		while (f_name == first_name) {
			std::cout << "You entered your old first name." << "\n";
			std::cout << "Please Enter New first Name: ";
			std::cin >> f_name;
		}
		exists = ValidationCheck::validateFirstName(f_name);
	} while (!exists);

	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.updateUser(username_, password_, f_name, last_name, category, birth_date);
		std::cout << "First name updated successfully." << "\n";
	}
	return true;
}

bool User::editLastName() {
	bool exists;
	std::string l_name;
	do {
		std::cout << "Please Enter New Last Name: ";
		std::cin >> l_name;
		while (l_name == last_name) {
			std::cout << "You entered your old Last Name." << "\n";
			std::cout << "Please Enter New Last Name: ";
			std::cin >> l_name;
		}
		exists = ValidationCheck::validateFirstName(l_name);

	} while (!exists);

	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.updateUser(username_, password_, l_name, last_name, category, birth_date);
		std::cout << "Last name updated successfully." << "\n";
	}
	return true;
}

bool User::editDOB() {
	bool exists;
	int day, month, year;
	do {
		std::cout << "Enter your new date of birth (DD MM YYYY)";
		std::cout << "Day(DD): ";
		std::cin >> day;
		std::cout << "Month(MM): ";
		std::cin >> month;
		std::cout << "Year(YYYY): ";
		std::cin >> year;
		exists = ValidationCheck::validateDOB(day, month, year);

	} while (!exists);

	std::string birth_date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
	{
		DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
		dbManager.updateUser(username_, password_, first_name, last_name, category, birth_date);
		std::cout << "Date Of Birth updated successfully." << "\n";
	}
	return true;
}

// Course::Course(const string& code) {
// 	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
// 	sql::Connection& conn_ = dbManager.getConnectionRef();
//
// 	std::unique_ptr<sql::PreparedStatement> stmt(
// 		conn_.prepareStatement("SELECT COLUMNS course_code, name, department FROM Course WHERE code = ?"));
// 	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
// 	if (res->next() && res->getInt(	1)) {
// 		name = res->getString("name");
// 		department = res->getString("department");
// 	} else {
// 		std::cout << "Error: Course not found." << "\n";
// 	}
// }
//
// void Course::setCourseId(const string& code_) {code=code_;}
// string Course::getCourseId() {return code;}

// Student::Student(const int& student_id) : User(user_name) {
// 	//Constructor for Student class, it initializes the User class with the username
// 	//and can be used to fetch student-specific details if needed.
// 	DatabaseManager dbManager("portal_user", "HVM1D1234", "portal_db");
// 	sql::Connection& conn_ = dbManager.getConnectionRef();
//
// 	std::unique_ptr<sql::PreparedStatement> stmt(
// 		conn_.prepareStatement("SELECT COLUMN class, user_id, gpa, enrollment_date FROM Course WHERE student_id = ?"));
// 	stmt->setInt(1, student_id);
//
// 	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
// 	if (res->next() && res->getInt(1)) {
// 		// Assuming student_classification is a field in the Users table
// 		this->student_classification = res->getString("student_classification");
// 	} else {
// 		std::cout << "Error: student is not found." << "\n";
// 	}
// }

// bool Student::view() {
// 	Utility utilityTools;
// 			while(true) {
// 				system("CLS");
// 				cout<<endl;
// 				cout<<"\t/1. Option to view all courses/"<<endl;
// 				cout<<"\t/2. Option to view your profile/"<<endl;
// 				cout<<"\t/3. Option to view your recent grade(s)/"<<endl;
// 				cout<<"\t/4. Option to view the program(s) you are enrolled into/"<<endl;
// 				cout<<"\t/5. Option to view other students that are learning from the same course/"<<endl;
// 				cout<<"\t/6. Exit these navigation menu"<<endl;
// 				cout<<"\t/7. cancel/"<<endl;
// 				cout<<endl;
// 				cout<<"Enter the view Option: ";
// 				int choice;
// 				cin>>choice;
// 				cin.ignore();
// 				system("CLS");
// 				cout<<endl;
// 				if(choice == 1) {
// 					Utility2::handlingDuplication("course_table_file.txt", 2);
// 					for(auto& pair : threeFieldsMap) {
// 						cout
// 						<<"COURSE-ID: "<<pair.first<<endl
// 						<<"COURSE_NAME: "<<pair.second.details_field2<<endl
// 						<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
// 						<<endl;
// 					}
// 					if(threeFieldsMap.empty() == 0) {
// 						if(threeFieldsMap.size() == 1) {
// 							cout<<"That's the only course provided in our management system."<<endl;
// 						} else {
// 							cout<<"Those are the courses provided in our management system."<<endl;
// 							cout<<"The total is: "<<threeFieldsMap.size()<<endl;
// 						}
// 					} else {
// 						cout<<"The course details are not yet uploaded by the registrar/admin."<<endl;
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit these view navigation menu"<<endl;
// 					cout<<"2. cancel"<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					if(choice == 1) {
// 						Student::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 2) {
// 					Utility2::handlingDuplication("users_File.txt", 6);
// 					if (userDataMap.find(this->getUsername()) != userDataMap.end()) {   //fetch the line with the username
// 						const UserDetailsUsingMap userDetails  = userDataMap[this->getUsername()];
// 						cout
// 						<<"USERNAME: "<<this->getUsername()<<endl
// 						<<"ID: "<<userDetails.details_field3<<endl
// 						<<"FIRST_NAME: "<<userDetails.details_field4<<endl
// 						<<"LAST_NAME: "<<userDetails.details_field5<<endl
// 						<<"SEX: "<<userDetails.details_field6<<endl
// 						<<"DATE_OF_BIRTH: "<<userDetails.details_field7<<endl
// 						<<endl;
// 					} else {
// 						cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit these view navigation menu"<<endl;
// 					cout<<"2. cancel"<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					if(choice == 1) {
// 						Student::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 3) {
// 					const string student_classification;
// 					DatabaseManager::searchForFirstAndSecondField("students_grade_details_table_file.txt",
// 					this->getId(), student_classification, 3);
// 					Utility2::handlingDuplication("temporarily_table2.0.txt", 3);
// 					//PLEASE VISIT THE DECLARATION IN searchForFirstAndSecondField FOR
// 					//THE EXPLANATION OF THE temporarily_table2.0. file
// 					if(fourFieldsMap.empty() == 1) {
// 						cout
// 						<<"Your grades are not yet published by your teacher, "
// 						<<"just wait/call your teacher that your grade(s) are no yet published"
// 						<<endl;
// 					} else {
// 						ReadFileThatAreExtractingASingleUserDetails::readFromAFile
// 						("temporarily_table2.0.txt", 3);
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit these view navigation menu"<<endl;
// 					cout<<"2. cancel"<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					if(choice == 1) {
// 						Student::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 4) {
// 					const string course_id = "EQUAL TO SOMETHING";
// 					DatabaseManager::searchForFirstAndSecondField("students_enroll_course_table_file.txt",
// 					this->getId(), course_id, 1);
// 					Utility2::handlingDuplication("temp_file_two.txt", 1);
// 					if(twoFieldsMap.empty() == 1) {
// 						cout<<"You have not yet enrolled into any course the management system offers."<<endl;
// 					} else {
// 						ReadFileThatAreExtractingASingleUserDetails::
// 						readFromAFile("temp_file_two.txt", 1);
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit these view navigation menu"<<endl;
// 					cout<<"2. cancel"<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					if(choice == 1) {
// 						Student::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 5) {
// 					string course_id;
// 					cout<<"Enter course-ID : ";
// 					cin>>course_id;
// 					cin.ignore();
// 					if(bool exists = ValidationCheck::validateCourseId(course_id)) {
// 						string course_name;
// 						exists = DatabaseManager::searchForFirstAndSecondField
// 						("course_table_file.txt", course_id,
// 						course_name, 2);
// 						if(exists) {
// 							//check if the ID exists in the course table
// 							//handling the students with the same course, so that the student can view his or her classmates
// 							exists = DatabaseManager::authenticateUserInFileManagementSystem
// 							(this->getId(), course_id,
// 							"students_enroll_course_table_file.txt", 1);
// 							if(exists) {
// 								const string id = "EQUAL TO SOMETHING";
// 								DatabaseManager::searchForFirstAndSecondField
// 								("students_enroll_course_table_file.txt", id,
// 								course_id, 1);
// 								ReadFileThatAreExtractingASingleUserDetails::
// 								readFromAFile("temp_file_one.txt", 1);
// 							} else {
// 								cout<<"You don't learn from the course, so you can't view other class members."<<endl;
// 							}
// 						} else {
// 							cout<<"The course-ID is not found in the course details file."<<endl;
// 						}
// 					} else {
// 						cout<<"Error: the course-ID is invalid."<<endl;
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit these view navigation menu"<<endl;
// 					cout<<"2. cancel"<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					if(choice == 1) {
// 						Student::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if (choice == 6) {
// 					AllocateUser::allocateUserLoginClassification(this->getUsername());
// 				} else if (choice == 7) {
//                     return false;
// 				} else {
// 					cout<<"Error: Invalid choice Option."<<endl;
// 					return false;
// 				}
// 			}
// 		}
// 	//Making the student's enroll database when the student's enrolls into a program
// 		bool Student::enrollCourse(const string& course_id) {
// 			ofstream outFile("students_enroll_course_table_file.txt", ios_base::app);
// 			if (bool exists = ValidationCheck::validateCourseId(course_id)) {
// 				cout<<endl;
// 				string course_name;
// 				exists = DatabaseManager::searchForFirstAndSecondField
// 				("course_table_file.txt", course_id,
// 				course_name, 2);
// 				if(exists) {
// 					//Check if the course ID exists in the database when the student enters the course ID in function navigate login menu
// 					Utility utilityTools;
// 					Utility2::handlingDuplication
// 					("students_enroll_course_table_file.txt", 1);
// 					//Check the student ID and course ID if they are already enrolled into the student's enroll course
// 					if(twoFieldsMap.find(this->getId()) != twoFieldsMap.end() &&
// 					twoFieldsMap[this->getId()].details_field2 == course_id) {
// 						cout<<"You are already enrolled to the program "<<course_id<<endl;
// 					} else {
// 						if (!outFile.is_open()) {
// 							cerr<<"Error: Unable to open the file."<<endl;
// 						} else {
// 							Course program(course_id);
// 							cout
// 							<<"COURSE-ID: "<<program.getCourseId()<<endl
// 							<<"COURSE_NAME: "<<program.course_name<<endl
// 							<<"COURSE_YEAR: "<<program.course_year<<endl;
// 							cout<<endl;
// 							outFile<<this->getId()<<","<<course_id<<endl;
// 							cout<<"You have successfully enrolled into a program in our management system."<<endl;
// 							return true;
// 						}
// 					}
// 				} else {
// 					cout<<"The course-ID is not found in the course file."<<endl;
// 				}
// 			} else {
// 				cout<<"Error: the course-ID is invalid."<<endl;
// 			} return false;
// 		}
//
// 	//Search for a student in the management system and the string id is the making a search algorithm
// 	//After the admin Enter a student ID we are able to view if that id exists
// 		bool Employee::searchForUsername(const string& username) {
// 			Utility utilityTools;
// 			Utility2::handlingDuplication("users_File.txt", 6);
// 			if(userDataMap.find(username) != userDataMap.end()) {
// 				cout<<"Username exists in the user database file."<<endl;
// 			} else {
// 				cout<<"Username doesn't exists in user database file."<<endl;
// 			} return true;
//         }
//
// 	/*View function for all the employees working in the office
// 	will view the student's details in our management system*/
// 		bool Employee::employeeView() {;
// 			Utility utilityTools;
// 			int choice;
// 			cout<<endl;
// 			cout<<"\t/1. Option to view students entry details/"<<endl;
// 			cout<<"\t/2. Option to view students grade details/"<<endl;
// 			cout<<"\t/3. Option to view students enroll course details/"<<endl;
// 			cout<<endl;
// 			cout<<"Enter the view Option: ";
// 			cin>>choice;
// 			cin.ignore();
// 			system("CLS");
// 			cout<<endl;
// 			if(choice == 1) {
// 				ofstream IfFileIsNotYetMade("students_entry_details_file.txt", ios_base::app);
// 				Utility2::handlingDuplication("students_entry_details_file.txt", 2);
// 				for(auto& pair : threeFieldsMap) {
// 					cout
// 					<<"USER-ID: "<<pair.first<<endl
// 					<<"STUDENT_CLASSIFICATION: "<<pair.second.details_field2<<endl
// 					<<"YEAR_OF_REGISTRATION: "<<pair.second.details_field3<<endl
// 					<<endl;
// 				}
// 				if(threeFieldsMap.empty() == 0) {
// 					if(threeFieldsMap.size() == 1) {
// 						cout<<"that's the only student in our management system."<<endl;
// 					} else {
// 						cout<<"Those are all the students in our management system."<<endl;
// 						cout<<"The total number is: "<<threeFieldsMap.size()<<endl;
// 					}
// 				} else {
// 					cout<<"The students have not yet registered by the registrar/admin."<<endl;
// 				}
// 				cout<<endl;
// 				cout<<"1. Exit the student view navigation menu."<<endl;
// 				cout<<"2. cancel."<<endl;
// 				cout<<"Enter your choice option: ";
// 				cin>>choice;
// 				if(choice == 1) {
// 					Employee::employeeView();
// 				} else if(choice == 2) {
// 					return false;
// 				} else {
// 					cout<<"Error: Invalid choice option."<<endl;
// 					return false;
// 				}
// 			} else if(choice == 2) {
// 				ofstream IfFileIsNotYetMade("students_grade_details_table_file.txt", ios_base::app);
// 				Utility2::handlingDuplication("students_grade_details_table_file.txt", 3);
// 				if(fourFieldsMap.empty() == 1) {  //not empty
// 					cout<<"The students grade details have not yet being published by the teacher."<<endl;
// 				} else {
// 					ReadFileThatAreExtractingASingleUserDetails::
// 					readFromAFile("students_grade_details_table_file.txt", 3);
// 				}
// 				cout<<endl;
// 				cout<<"1. Exit the view navigation menu."<<endl;
// 				cout<<"2. cancel."<<endl;
// 				cout<<"Enter your choice option: ";
// 				cin>>choice;
// 				if(choice == 1) {
// 					Employee::employeeView();
// 				} else if(choice == 2) {
// 					return false;
// 				} else {
// 					cout<<"Error: Invalid choice option."<<endl;
// 					return false;
// 				}
// 			} else if(choice == 3) {
// 				ofstream IfFileIsNotYetMade("students_enroll_course_table_file.txt", ios_base::app);
// 				Utility2::handlingDuplication("students_enroll_course_table_file.txt", 1);
// 				if(twoFieldsMap.empty() == 1) {
// 					cout<<"The students in our management system have not yet enrolled into a course/program."<<endl;
// 				} else {
// 					ReadFileThatAreExtractingASingleUserDetails::
// 					readFromAFile("students_enroll_course_table_file.txt", 1);
// 				}
// 				cout<<endl;
// 				cout<<"1. Exit the view navigation menu."<<endl;
// 				cout<<"2. cancel."<<endl;
// 				cout<<"Enter your choice option: ";
// 				cin>>choice;
// 				if(choice == 1) {
// 					Employee::employeeView();
// 				} else if(choice == 2) {
// 					return false;
// 				} else {
// 					cout<<"Error: Invalid choice option."<<endl;
// 					return false;
// 				}
// 			} else {
// 				cout<<"Error: Invalid view Option."<<endl;
// 			}
// 			return true;
// 		}
//
//
//
// 		bool Teacher::readStudentsEnrolledToACourse(const string& course_id) {
// 			ofstream IfFileIsNotYetMade("students_enroll_course_table_file.txt", ios_base::app);
// 			if (bool exists = ValidationCheck::validateCourseId(course_id)) {
// 				//Check if the course table has the entered course ID
// 				string course_name;
// 				exists = DatabaseManager::searchForFirstAndSecondField
// 				("course_table_file.txt",course_id,
// 				course_name, 2);
// 				if(exists) {
// 					exists = DatabaseManager::authenticateUserInFileManagementSystem
// 					(this->getId(), course_id,
// 					"teachers_table_file.txt", 1);
// 					if(exists) {
// 						const string id = "EQUAL TO SOMETHING";
// 						DatabaseManager::
// 						searchForFirstAndSecondField("students_enroll_course_table_file.txt",
// 						id, course_id, 1);
// 						Utility utilityTools;
// 						Utility2::handlingDuplication("temp_file_one.txt", 1);
// 						if(twoFieldsMap.empty() == 1) {
// 							cout<<"No student learns from your course-ID."<<endl;
// 							return false;
// 						} else {
// 							ReadFileThatAreExtractingASingleUserDetails::
// 							readFromAFile("temp_file_one.txt", 1);
// 							return true;
// 						}
// 					} else {
// 						cout<<"you don't teach that course in our management system."<<endl;
// 					}
// 				} else {
// 					cout<<"the course ID  is not found in the course table file."<<endl;
// 				}
// 			} else {
// 				cout<<"The course ID  is invalid."<<endl;
// 			} return false;
// 		}
//
// 	//Overriding view function in teacher
// 		bool Teacher::view() {
// 			while(true) {
//
// 				Utility utilityTools;
// 				int choice;
// 				cout<<endl;
// 				cout<<"\t/1. Option to view all courses/"<<endl;
// 				cout<<"\t/2. Option to view your profile/"<<endl;
// 				cout<<"\t/3. Option to view the students who are learning your program/"<<endl;
// 				cout<<"\t/4. Option to view student information categories within this system/"<<endl;
// 				cout<<endl;
// 				cout<<"Enter the view Option: ";
// 				cin>>choice;
// 				cin.ignore();
// 				system("CLS");
// 				if(choice == 1) {
// 					Utility2::handlingDuplication("course_table_file.txt", 2);
// 					for(auto& pair: threeFieldsMap) {
// 						cout
// 						<<"COURSE-ID: "<<pair.first<<endl
// 						<<"COURSE_NAME: "<<pair.second.details_field2<<endl
// 						<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
// 						<<endl;
// 					}
// 					if(threeFieldsMap.empty() == 0) {
// 						if(threeFieldsMap.size() == 1) {
// 							cout<<"that is the only course provided into the management system."<<endl;
// 						} else {
// 							cout<<"that's all the courses provided into the management system."<<endl;
// 							cout<<"That total is: "<<threeFieldsMap.size()<<endl;
// 						}
// 					} else {
// 						cout<<"The course are not yet registered/made by the admin."<<endl;
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit the view navigation menu."<<endl;
// 					cout<<"2. cancel."<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					if(choice == 1) {
// 						Teacher::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 2) {
// 					Utility2::handlingDuplication("users_File.txt", 6);
// 					if(userDataMap.find(this->getUsername()) != userDataMap.end()) {
// 						const UserDetailsUsingMap userDetails = userDataMap[this->getUsername()];
// 						cout
// 						<<"USERNAME: "<<this->getUsername()<<endl
// 						<<"ID: "<<userDetails.details_field3<<endl
// 						<<"FIRST_NAME: "<<userDetails.details_field4<<endl
// 						<<"LAST_NAME: "<<userDetails.details_field5<<endl
// 						<<"SEX: "<<userDetails.details_field6<<endl
// 						<<"DATE_OF_BIRTH: "<<userDetails.details_field7<<endl
// 						<<endl;
// 						cout<<"That is your profile in our management system."<<endl;
// 					} else {
// 						cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
// 					}
// 					cout<<endl;
// 					cout<<"1. Exit the view navigation menu."<<endl;
// 					cout<<"2. cancel."<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					if(choice == 1) {
// 						Teacher::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 3) {
// 					string course_id;
// 					cout<<"Enter the course-ID of the program(s) that you teach: ";
// 					cin>>course_id;
// 					cin.ignore();
// 					this->readStudentsEnrolledToACourse(course_id);
// 					cout<<endl;
// 					cout<<"1. Exit the view navigation menu."<<endl;
// 					cout<<"2. cancel."<<endl;
// 					cout<<"Enter your choice option: ";
// 					cin>>choice;
// 					if(choice == 1) {
// 						Teacher::view();
// 					} else if(choice == 2) {
// 						return false;
// 					} else {
// 						cout<<"Error: Invalid choice option."<<endl;
// 						return false;
// 					}
// 				} else if(choice == 4) {
// 					Employee::employeeView();
// 				}  else {
// 					cout<<"Error: Invalid view Option."<<endl;;
// 				}
// 			}
// 		}
// 	//make the student's grade table after the exams are done with marking
// 		bool Teacher::makeStudentsGradeTable() {
// 			while(true) {
// 				ofstream outFile("students_grade_details_table_file.txt", ios_base::app);
// 				string course_id;
// 				cout<<"Enter course-ID of the program(s) that you teach: ";
// 				cin>>course_id;
// 				cin.ignore();
// 				string details_field2;
// 				if (bool exists = this->readStudentsEnrolledToACourse(course_id)) {
// 					//these must be together for the student, so that we could use the getter for the ID
// 					string username;
// 					cout<<"Enter username: ";
// 					cin>>username;
// 					cin.ignore();
// 					exists = ValidationCheck::validateId(username);
// 					if(exists) {
// 						string password;
// 						exists = DatabaseManager::searchForFirstAndSecondField
// 						("users_File.txt", username,
// 						password, 6);
// 						if(exists) {
// 							Student student(username);
// 							exists = DatabaseManager::authenticateUserInFileManagementSystem
// 							(student.getId(), course_id,
// 							"students_enroll_course_table_file.txt", 1);
// 							if(exists) {
// 								string student_classification;
// 								cout<<"Enter classification/class: ";
// 								getline(cin>>ws, student_classification);
// 								exists = ValidationCheck::validateStudentClassification(student_classification);
// 								if(exists) {
// 									Utility utilityTools;
// 									Utility2::handlingDuplication("students_entry_details_file.txt",2);
// 									if(threeFieldsMap.find(student.getId()) != threeFieldsMap.end() &&
// 										threeFieldsMap[student.getId()].details_field2 == student_classification) {
// 										exists = DatabaseManager::authenticateUserInFileManagementSystem
// 										(student.getId(), course_id,
// 										"students_grade_details_table_file.txt", 3);
// 										if (exists) {
// 											cout
// 											<<"The students grade details for the ID and the course the student learns "
// 											"have already ben published into the students grade details file"
// 											<<endl;
// 										} else {
// 											string gpa;
// 											cout<<"Enter grade: ";
// 											cin>>gpa;
// 											cin.ignore();
// 											exists = ValidationCheck::validateGpa(gpa);
// 											if(exists) {
// 												if(!outFile.is_open()) {
// 													cerr<<"Error: Unable to open the students grade details file."<<endl;
// 												} else {
// 													outFile
// 													<<student.getId()<<","<<student_classification
// 													<<","<<course_id<<","<<gpa<<endl;
// 													cout
// 													<<"You have successfully published the students grade in"
// 													<<" our management system."
// 													<<endl;
// 												}
// 											} else {
// 												cout<<"Error: the grade is invalid."<<endl;
// 											}
// 										}
// 									} else {
// 										cout
// 										<<"The student classification is not the same as the students details"
// 										<<" in the students entry details file"
// 										<<endl;
// 									}
// 								} else {
// 									cout<<"Error: the student classification is invalid."<<endl;
// 								}
// 							} else {
// 								cout<<"These student doesn't take your course in our management system."<<endl;
// 							}
// 						} else {
// 							cout<<"The student username doesn't exists in the user's file file."<<endl;
// 						}
// 					} else {
// 						cout<<"Error: The username is invalid."<<endl;
// 					}
// 				} else {
// 					cout
// 					<<"THE ERROR MESSAGE ABOVE EXPLAINS AN ISSUE, "
// 					<<"PLEASE MAKE AN FOLLOW THE CORRECT PROCEDURE OF UPLOADING GRADES."
// 					<<endl;
// 				}
// 				cout<<endl;
// 				int choice;
// 				cout<<"1. Exit the upload students grade page"<<endl;
// 				cout<<"2. cancel"<<endl;
// 				cout<<"Enter your choice option: ";
// 				cin>>choice;
// 				cin.ignore();
// 				if(choice == 1) {
// 					AllocateUser::allocateUserLoginClassification(this->getUsername());
// 				} else if(choice == 2) {
// 					return false;
// 				} else {
// 					cout<<"Error: Invalid choice option."<<endl;
// 					return false;
// 				}
// 			}
// 		}
// 		bool Admin::registration() {
// 			//Handling registration function in admin
// 			int choice;
// 			printf("\n");
// 			cout<<"\t1. Register course"<< "\n";
// 			cout<<"\t2. Register teacher"<< "\n";
// 			cout<<"\t3. Register student"<< "\n";
// 			printf("\n");
// 			cout<<"Enter the choice Option: ";
// 			cin>>choice;
//
// 			if(choice == 1) {
// 				bool exists;
// 				std::string course_id;
// 				std::string course_name;
// 				std::string course_year;
// 				do {
// 					cout<<"Enter course-ID: ";
// 					cin>>course_id;
// 					exists = ValidationCheck::validateCourseId(course_id);
// 				} while (!exists);  //when its false goes into the loop
//
// 				do {
// 					exists = DatabaseManager::searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
// 				} while (exists);  //when its true goes into the loop
//
// 				do {
// 					//Validate the course ID Entered
// 					cout<<"Enter course name: ";
// 					cin>>course_name;
// 					exists = ValidationCheck::validateCourseName(course_name);
// 				} while (!exists);
//
// 				do {
// 					//Validate the course name Entered
// 					cout<<"Enter course year: ";
// 					cin>>course_year;
// 					cin.ignore();
// 					exists = ValidationCheck::validateYear(course_year);
// 				} while (!exists);
//
// 				{ //Validate the course year Entered
// 					ofstream outFile("course_table_file.txt", ios_base::app);
// 					if(!outFile.is_open()) {
// 						cerr<<"Error: File is not found."<<endl;
// 					} else {
// 						outFile<<course_id<<","<<course_name<<","<<course_year<<endl;
// 						cout<<"Registration of the course was completed successfully."<<endl;
// 					}
// 				}
// 			} else if(choice == 2) {
// 				cout<<endl;
// 				cout<<"1. Use to Register a New Teacher?"<<endl;
// 				cout<<"2. Use to Add a New course to an Existing Teacher?"<<endl;
// 				cout<<endl;
// 				cout<<"Enter your option: ";
// 				cin>>choice;
// 				cin.ignore();
// 				system("CLS");
// 				cout<<endl;
// 				if(choice == 1) {
// 					string username;
// 					cout<<"Enter username: ";
// 					cin>>username;
// 					cin.ignore();
// 					if(bool exists = ValidationCheck::validateUsername(username)) {
// 						string password;
// 						 exists = DatabaseManager::searchForFirstAndSecondField
// 						("users_File.txt", username,
// 						password, 6);
// 						if(exists) {
// 							cout
// 							<<"The username already exists in the user's database, inorder to register to new course"
// 							<<" please go to 'register to new course'."
// 							<<endl;
// 						} else {
// 							cout<<"Enter Default Password: ";
// 							cin>>password;
// 							cin.ignore();
// 							exists = ValidationCheck::validatePassword(password);
// 							if(exists) {
// 								string id;
// 								cout<<"Enter ID: ";
// 								cin>>id;
// 								cin.ignore();
// 								exists = ValidationCheck::validateId(id);
// 								if(exists) {
// 									string course_id = "EQUAL TO SOMETHING";
// 									exists = DatabaseManager::searchForFirstAndSecondField
// 									("teachers_table_file.txt", id,
// 									course_id, 1);
// 									if(exists) {
// 										cout
// 										<<"The teachers-ID belongs to another teacher in the teachers table file."
// 										<<endl;
// 									} else {
// 										string first_name;
// 										cout<<"Enter First Name: ";
// 										cin>>first_name;
// 										cin.ignore();
// 										exists = ValidationCheck::validateFirstName(first_name);
// 										if(exists) {
// 											string last_name;
// 											cout<<"Enter Last Name: ";
// 											cin>>last_name;
// 											cin.ignore();
// 											exists = ValidationCheck::validateLastName(last_name);
// 											if(exists) {
// 												string sex;
// 												cout<<"Enter gender: ";
// 												cin>>sex;
// 												cin.ignore();
// 												exists = ValidationCheck::validateGender(sex);
// 												if(exists) {
// 													string date_of_birth;
// 													cout<<"Enter Date-Of-Birth: ";
// 													cin>>date_of_birth;
// 													cin.ignore();
// 													exists = ValidationCheck::validateGender(sex);
// 													if(exists) {
// 														cout<<endl;
// 														Utility utilityTools;
// 														Utility2::handlingDuplication
// 														("course_table_file.txt", 2);
// 														for(auto& pair :
// 														threeFieldsMap) {
// 															cout
// 															<<"COURSE-ID: "<<pair.first<<endl
// 															<<"COURSE_NAME: "<<pair.second.details_field2<<endl
// 															<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
// 															<<endl;
// 														}
// 														cout<<endl;
// 														cout<<"Enter course-ID: ";
// 														cin>>course_id;
// 														cin.ignore();
// 														string course_name;
// 														exists = DatabaseManager::searchForFirstAndSecondField
// 														("course_table_file.txt",course_id,
// 															course_name, 2);
// 														if(exists) {
// 															string temporarily_id = "EQUAL TO SOMETHING";
// 															exists = DatabaseManager::searchForFirstAndSecondField
// 															("teachers_table_file.txt",
// 															temporarily_id,
// 															course_id, 1);
// 															if(exists) {
// 																cout
// 																<<"You can't register these teacher to the same "
// 																<<"course as an existing teacher."
// 																<<endl;
// 															} else {
// 																ofstream outFile("teachers_table_file.txt",
// 																ios_base::app);
// 																if(!outFile.is_open()) {
// 																	cerr
// 																	<<"Error: Unable to open the teachers table file."
// 																	<<endl;
// 																} else {
// 																	DatabaseManager::registerUser
// 																	("users_File.txt", username,
// 																	password, id, first_name,
// 																	last_name, sex, date_of_birth);
// 																	outFile<<id<<","<<course_id<<endl;
// 																	cout
// 																	<<"Registration of the new teacher in both user's "
// 																	<<"database and teachers table file completed "
// 																	<<"successfully."
// 																	<<endl;
// 																}
// 															}
// 														} else {
// 															cout
// 															<<"The Course-ID doesn't exists in the course table."
// 															<<endl;
// 														}
// 													} else {
// 														cout<<"Error: The date of birth is invalid."<<endl;
// 													}
// 												} else {
// 													cout<<"Error: The gender is invalid."<<endl;
// 												}
// 											} else {
// 												cout<<"Error: The Last Name is invalid."<<endl;
// 											}
// 										} else {
// 											cout<<"Error: The First Name is invalid."<<endl;
// 										}
// 									}
// 								} else {
// 									cout<<"Error: The Identification Number is invalid."<<endl;
// 								}
// 							}  else {
// 								cout<<"Error: The Password is invalid."<<endl;
// 							}
// 						}
// 					} else {
// 						cout<<"Error:The Username is invalid."<<endl;
// 					}
// 				} else if(choice == 2) {
// 					cout<<endl;
// 					Utility utilityTools;
// 					Utility2::handlingDuplication("course_table_file.txt", 2);
// 					for(auto& pair: threeFieldsMap) {
// 						cout
// 						<<"ID: "<<pair.first<<endl
// 						<<"COURSE_NAME: "<<pair.second.details_field2<<endl
// 						<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
// 						<<endl;
// 					}
// 					cout<<endl;
// 					//displaying the course table file so that would have a chance of viewing details while registration
// 					string username;
// 					cout<<"Enter username: ";
// 					cin>>username;
// 					cin.ignore();
// 					if(bool exists = ValidationCheck::validateUsername(username)) {
// 						string password;
// 						exists = DatabaseManager::searchForFirstAndSecondField
// 						("users_File.txt", username,
// 						password, 6);
// 						if(exists) {
// 							Teacher teacher(username);
// 							string course_id;
// 							cout<<"Enter course-ID: ";
// 							cin>>course_id;
// 							cin.ignore();
// 							exists = ValidationCheck::validateCourseId(course_id);
// 							if(exists) {
// 								string course_name;
// 								exists = DatabaseManager::searchForFirstAndSecondField
// 								("course_table_file.txt", course_id,
// 								course_name, 2);
// 								if(exists) {
// 									exists = DatabaseManager::authenticateUserInFileManagementSystem
// 									(teacher.getId(), course_id,
// 									"teachers_table_file.txt", 1);
// 									if(exists) {
// 										cout
// 										<<"the teacher is already registered to that course in our management system."
// 										<<endl;
// 									} else {
// 										string id = "EQUAL TO SOMETHING";
// 										exists = DatabaseManager::searchForFirstAndSecondField
// 										("teachers_table_file.txt", id,
// 										course_id, 1);
// 										if(exists) {
// 											cout
// 											<<"You can't register these teacher to the same course as an "
// 											<<"existing teacher."
// 											<<endl;
// 										} else {
// 											ofstream outFile("teachers_table_file.txt", ios_base::app);
// 											if(!outFile.is_open()) {
// 												cerr
// 												<<"Error: Unable to open the teachers file, inorder to save the new"
// 												<<" entry details into the teachers details table."
// 												<<endl;
// 											} else {
// 												outFile<<teacher.getId()<<","<<course_id<<endl;
// 												cout
// 												<<"Registration of existing teacher to the new course in the "
// 												<<"teachers table file is completed successfully."
// 												<<endl;
// 											}
// 										}
// 									}
// 								} else {
// 									cout<<"the course-ID is not found in the course file."<<endl;
// 								}
// 							} else {
// 								cout<<"Error: The Course-ID is invalid."<<endl;
// 							}
// 						} else {
// 							cout<<"The username is not found in the user file, *perhaps try to register a new teacher*"
// 							<<endl;
// 						}
// 					} else {
// 						cout<<"Error: The Username is invalid."<<endl;
// 					}
// 				} else {
// 					cout<<"Invalid choice option."<<endl;
// 				}
// 			} else if(choice == 3) {
// 				string username;
// 				cout<<"Enter username: ";
// 				cin>>username;
// 				cin.ignore();
// 				if(bool exists = ValidationCheck::validateUsername(username)) {
// 					string password;
// 					exists = DatabaseManager::searchForFirstAndSecondField
// 					("users_File.txt", username, password, 6);
// 					if(exists) {
// 						cout
// 						<<"The username in the user's file already is registered into the school management system."
// 						<<endl;
// 					} else {
// 						cout<<"Enter Default Password: ";
// 						cin>>password;
// 						cin.ignore();
// 						exists = ValidationCheck::validatePassword(password);
// 						if(exists) {
// 							string id;
// 							cout<<"Enter ID: ";
// 							cin>>id;
// 							cin.ignore();
// 							exists = ValidationCheck::validateId(id);
// 							if(exists) {
//                                 string student_classification;
// 								exists = DatabaseManager::searchForFirstAndSecondField
// 								("students_entry_details_file.txt", id,
// 								student_classification, 2);
// 								if(exists) {
// 									cout
// 									<<"The students-ID belongs to another student in the student entry details file."
// 									<<endl;
// 								} else {
// 									cout<<"Enter First Name: ";
// 									cin>>first_name;
// 									cin.ignore();
// 									exists = ValidationCheck::validateFirstName(first_name);
// 									if(exists) {
// 										cout<<"Enter Last Name: ";
// 										cin>>last_name;
// 										cin.ignore();
// 										exists = ValidationCheck::validateLastName(last_name);
// 										if(exists) {
// 											cout<<"Enter gender: ";
// 											cin>>sex;
// 											cin.ignore();
// 											exists = ValidationCheck::validateGender(sex);
// 											if(exists) {
// 												cout<<"Enter Date-Of-Birth: ";
// 												cin>>date_of_birth;
// 												cin.ignore();
// 												exists = ValidationCheck::validateGender(sex);
// 												if(exists) {
// 													string year_of_entry;
// 													cout<<"Enter the year of entry: ";
// 													cin>>year_of_entry;
// 													cin.ignore();
// 													exists = ValidationCheck::validateYear(year_of_entry);
// 													if(exists) {
// 														cout<<"Enter student classification/class: ";
// 														getline(cin>>ws, student_classification);
// 														exists = ValidationCheck::
// 														validateStudentClassification(student_classification);
// 														if(exists) {
// 															ofstream outFile("students_entry_details_file.txt",
// 															ios_base::app);
// 															if(!outFile.is_open()) {
// 																cerr
// 																<<"Error: Unable to open the student entry details"
// 																<<endl;
// 															} else {
// 																outFile
// 																<<id<<","<<student_classification<<","<<year_of_entry
// 																<<endl;
// 																DatabaseManager::registerUser
// 																("users_File.txt", username, password,
// 																id, first_name, last_name,
// 																sex, date_of_birth);
// 																cout
// 																<<"Registration of the student in the student entry "
// 																<<"details file is completed successfully."
// 																<<endl;
// 															}
// 														}
// 														cout
// 														<<"Error: The student classification/class is invalid."
// 														<<endl;
// 													} else {
// 														cout<<"Error: The students year of entry is invalid."<<endl;
// 													}
// 												} else {
// 													cout<<"Error: The Data Of Birth is invalid."<<endl;
// 												}
// 											} else {
// 												cout<<"Error: The Gender is invalid."<<endl;
// 											}
// 										} else {
// 											cout<<"Error: The Last Name is invalid."<<endl;
// 										}
// 									} else {
// 										cout<<"Error: The First Name is invalid."<<endl;
// 									}
// 								}
// 							} else {
// 								cout<<"Error: The Identification Number is invalid."<<endl;
// 							}
// 						} else {
// 							cout<<"Error: The Password is invalid."<<endl;
// 						}
// 					}
// 				} else {
// 					cout<<"Error: The Username is invalid."<<endl;
// 				}
// 			} else {
// 				cout<<"Error: Invalid choice Option."<<endl;
// 			} return true;
// 		}
// 		bool Admin::view(){
// 			int choice;
// 			cout<<endl;
// 			cout<<"\t/1. Option to view all users/"<<endl;
// 			cout<<"\t/2. Option to view all courses/"<<endl;
// 			cout<<"\t/3. Option to view your profile/"<<endl;
// 			cout<<"\t/4. Option to view all teachers/"<<endl;
// 			cout<<"\t/5. Option to view student information categories within this system/"<<endl;
// 			cout<<endl;
// 			cout<<"Enter the view Option: ";
// 			cin>>choice;
// 			Utility utilityTools;
// 			cin.ignore();
// 			system("CLS");
// 			cout<<endl;
// 			if(choice == 1) {
// 				Utility2::handlingDuplication("users_File.txt", 6);
// 				User::view();
// 			} else if(choice == 2) {
// 				Utility2::handlingDuplication("course_table_file.txt", 2);
// 				for(auto& pair : threeFieldsMap) {
// 					cout
// 					<<"COURSE-ID: "<<pair.first<<endl
// 					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
// 					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
// 					<<endl;
// 				}
// 				if(threeFieldsMap.empty() == 0) {
// 					if(threeFieldsMap.size() == 1) {
// 						cout<<"That is the only course that you registered in the management system."<<endl;
// 					} else {
// 						cout<<"Those are all the courses in the management system."<<endl;
// 						cout<<"The total is: "<<threeFieldsMap.size()<<endl;
// 					}
// 				} else {
// 					cout
// 					<<"The admin/registrar has not yet registered course file table in the management system."<<endl;
// 				}
// 			} else if(choice == 3) {
// 				Utility2::handlingDuplication("users_File.txt", 6);
// 				if(userDataMap.find(this->getUsername()) != userDataMap.end()) {
// 					const UserDetailsUsingMap userDetails = userDataMap[this->getUsername()];
// 					cout
// 					<<"USERNAME: "<<this->getUsername()<<endl
// 					<<"ID: "<<userDetails.details_field3<<endl
// 					<<"FIRST_NAME: "<<userDetails.details_field4<<endl
// 					<<"LAST_NAME: "<<userDetails.details_field5<<endl
// 					<<"GENDER: "<<userDetails.details_field6<<endl
// 					<<"DATE_OF_BIRTH: "<<userDetails.details_field7<<endl
// 					<<endl;
//
// 				} else {
// 					cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
// 				}
// 				//read my own profile
// 			} else if(choice == 4) {
// 				cout<<"1. Option to view how many teachers are in the management system."<<endl;
// 				cout<<"2. Option to view the teachers and the course they teach."<<endl;
// 				cout<<endl;
// 				cout<<"Enter the view option: ";
// 				cin>>choice;
// 				cin.ignore();
// 				system("CLS");
// 				cout<<endl;
// 				switch(choice) {
// 					case 1: {
// 						Utility2::handlingDuplication("teachers_table_file.txt", 1);
// 						for(auto& pair : twoFieldsMap) {
// 							cout<<"USER-ID: "<<pair.first<<endl;
// 						}
// 						if(twoFieldsMap.empty() == 0) {
// 							if(twoFieldsMap.size() == 1) {
// 								cout<<"That's the only teacher that you registered in the management system."<<endl;
// 							} else {
// 								cout<<"Those are all the teachers in the management system."<<endl;
// 								cout<<"The total is: "<<twoFieldsMap.size()<<endl;
// 							}
// 						} else {
// 							cout
// 							<<"The registrar has not yet registered the teachers table file in the management system."
// 							<<endl;
// 						}
// 						break;
// 					}
// 					case 2: {
// 						ReadFileThatAreExtractingASingleUserDetails::readFromAFile
// 						("teachers_table_file.txt", 1);
// 						break;
// 					}
// 					default: {
// 						cout<<"Error: invalid view option."<<endl;
// 						break;
// 					}
// 				}
//
// 			} else if(choice == 5) {
// 				Employee::employeeView();
// 			} else {
// 				cout<<"Error: Invalid view Option"<<endl;
// 			}
// 			return true;
// 		}
// 		bool Admin::editPassword() {
// 			//Overriding edit function in the admin
// 			string username;
// 			cout<<"Enter username: ";
// 			cin>>username;;
// 			cin.ignore();
// 			if(bool exists = ValidationCheck::validateUsername(username)) {
// 			//Validate the username
// 				string password;
// 			exists = DatabaseManager::searchForFirstAndSecondField ("users_File.txt", username,
// 			password, 6);
// 				if(exists == true) {
// 					User user(username);
// 					string new_last_name;
// 					string new_first_name;
// 					int choice;
// 					cout<<endl;
// 					cout<<"\t/1. Option edit First Name/"<<endl;
// 					cout<<"\t/2. Option edit Last Name/"<<endl;
// 					cout<<"\t/3. Option edit All the above details/"<<endl;
// 					cout<<endl;
// 					cout<<"Enter the edit Option: ";
// 					cin>>choice;
// 					cin.ignore();
// 					system("CLS");
// 					if(choice == 1) {
// 						cout<<"Enter New First Name: ";
// 						cin>>new_first_name;
// 						cin.ignore();
// 						exists = ValidationCheck::validateFirstName(new_first_name);
// 						if(exists == true) {
// 							DatabaseManager::registerUser
// 							("temporarily_edit_table.txt", username, user.getPassword(), user.getId(),
// 							new_first_name, user.last_name, user.sex, user.date_of_birth);
// 							DatabaseManager::deleteFileName();
// 							DatabaseManager::renameFileName();
// 						} else {
// 							cout<<"Error: the first name is invalid."<<endl;
// 						}
// 					} else if(choice == 2) {
// 						cout<<"Enter New Last Name: ";
// 						cin>>new_last_name;
// 						cin.ignore();
// 						exists = ValidationCheck::validateLastName(new_last_name);
// 						if(exists == true) {
// 							DatabaseManager::registerUser("temporarily_edit_table.txt", username,
// 							user.getPassword(), user.getId(), user.first_name, new_last_name, user.sex,
// 							user.date_of_birth);
// 							DatabaseManager::deleteFileName();
// 							DatabaseManager::renameFileName();
// 						} else {
// 							cout<<"Error: the last name is invalid."<<endl;
// 						}
// 					} else if(choice == 3) {
// 						cout<<"Enter New First Name: ";
// 						cin>>new_first_name;
// 						cin.ignore();
// 						exists = ValidationCheck::validateFirstName(new_first_name);
// 						if(exists) {
// 							cout<<"Enter New Last Name: ";
// 							cin>>new_last_name;
// 							cin.ignore();
// 							exists = ValidationCheck::validateLastName(new_last_name);
// 							if(exists == true) {
// 								DatabaseManager::registerUser("temporarily_edit_table.txt", username,
// 								user.getPassword(), user.getId(), new_first_name, new_last_name, user.sex,
// 								user.date_of_birth);
// 								DatabaseManager::deleteFileName();
// 								DatabaseManager::renameFileName();
// 							} else {
// 								cout<<"Error: the last name is invalid."<<endl;
// 							}
// 						} else {
// 							cout<<"Error: the first name is invalid."<<endl;
// 						}
// 					} else {
// 						cout<<"Error: Invalid edit Option."<<endl;
// 					}
// 				} else {
// 					cout<<"The username doesn't exits in the user file"<<endl;
// 				}
// 			} else {
// 				cout<<"Error: the username is invalid."<<endl;
// 			} return true;
// 		}
