#include "HandleMenus.h"
#include "UtililtyHandler.h"
#include <utility>

#include "DatabaseManager.h"

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
				return false;
			}
		} while (choice != 0 || !false);
	}
	return true;
}

bool Menu::teacherMenu() {
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
		std::cout << "Username is " << username_ << std::endl;

		if (bool exists = dbManager.searchUser(username_)) {
			int user_id;
			std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
			user_id = res->getInt("id");

			stmt.reset(conn_.prepareStatement("SELECT * FROM Admin WHERE user_id = ?"));
			stmt->setInt(1, user_id);

			if (int affected_rows = stmt->executeUpdate(); affected_rows > 0) {
				int choice;
				do {
					std::cout << "1. View" << "\n";
					std::cout << "2. Create course" << "\n";
					std::cout << "3. Delete course" << "\n";
					std::cout << "Enter your choice: " << "\n";
					std::cin >> choice;
					switch (choice) {
						case 1: //viewing details in the database

							break;
						case 2: //Create the course
								adminUser.makeCourseInDB();
							break;
						case 3: //Delete the course

							break;
						default:
							std::cout << "Invalid choice. Please enter value between(1-3)" << "\n";
					}
				} while (choice > 3 || choice < 1);
			} else {
				int admin_id;
				std::string department_;
				int day, month, year;
				std::string hire_date;
				std::string office_number;

				std::cout << "What is your Identification Number(ID): " << "\n";
				std::cin >> admin_id;
				std::cout << "What is your office (room number): " << "\n";
				std::cin >> office_number;
				std::cout << "Which department do you work-in this corporation: " << "\n";
				std::cin >> department_;

				dbManager.createAdmin(admin_id, user_id, department_, office_number, hire_date);
			}
		} else {
			std::cout << "Couldn't find user" << "\n";
			std::cout << "Please report to the software engineer teem to fix your issue" << "\n";
			std::exit(EXIT_FAILURE);
		}
	}
	return true;
}













// #include "PortalUsers.h"
// using namespace std;
//     //Function handling the users allocation the aim is after logged in by the system during runtime they will have their own menu.
//     bool AllocateUser::allocateUserLoginClassification(const string& username) {
//      	int choice;
// 			User user(username);
// 			cout<<endl;
// 			if(user.getUserClassification() == "student") {
// 				Student student(username);
// 				cout<<"\t/1. Option to enroll into a course/"<<endl;
// 				cout<<"\t/2. Option to view details/"<<endl;
// 				cout<<"\t/3. Option to edit password/"<<endl;
//                 cout<<"\t/4. Exit"<<endl;
// 				cout<<endl;
// 				cout<<"Enter your Option: ";
// 				cin>>choice;
// 				cin.ignore();
// 				system("CLS");
// 				if(choice == 1) {
// 		// 			Utility utilityTools;
// 		// 			cout<<"Here is the course details we offer in our schools management system."<<endl<<endl;
// 		// 			Utility2::handlingDuplication("course_table_file.txt", 2);
// 		// 			for(auto& pair: threeFieldsMap) {
// 		// 				cout
// 		// 				<<"COURSE-ID: "<<pair.first<<endl
		// 				<<"COURSE_NAME: "<<pair.second.details_field2<<endl
		// 				<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
		// 				<<endl;
		// 			}
		// 			if(threeFieldsMap.empty() == 0) {
		// 				string course_id;
  //                       system("CLS");
		// 				while(true) {
		// 					cout<<"1. Enroll into a course"<<endl;
		// 					cout<<"2. Exit these students enroll course page"<<endl;
  //                           cout<<"3. cancel"<<endl;
		// 					cout<<"Enter your Option: ";
		// 					cin>>choice;
		// 					cin.ignore();
		// 					system("CLS");
		// 					if (choice == 1) {
		// 						cout<<endl;
		// 						cout<<"Enter course-ID: ";
		// 						cin>>course_id;
		// 						cin.ignore();
		// 						Course program(course_id);
		// 						student.makeStudentsEnrollCourseTable(course_id);
		// 					} else if (choice == 2) {
		// 						AllocateUser::allocateUserLoginClassification(username);
		// 					} else if(choice == 3) {
		// 						return false;
		// 					} else {
		// 						cout<<"Error: Invalid choice Option."<<endl;
  // 								return false;
		// 					}
		// 				}
		// 			} else {
		// 				cout
		// 				<<"You can't enroll into a course because the file containing the course is not yet made by the "
		// 				<<"admin/register in the management system."
		// 				<<endl;
		// 			}
		// 		} else if(choice == 2) {
		// 			Student *ptr = &student;
		// 			ptr->view();
		// 		} else if(choice == 3) {
		// 			Student *ptr = &student;
		// 			ptr->editDetails();
		// 		} else if(choice == 4) {
  //               	return false;
  //               } else {
		// 			cout<<"Error: Invalid choice Option."<<endl;
  //                   return false;
		// 		}
		// 	} else if(user.getUserClassification() == "teacher") {
		// 		Teacher teacher(username);
		// 		cout<<"\t/1. Option to upload grades/"<<endl;
		// 		cout<<"\t/2. Option to view details/"<<endl;
		// 		cout<<"\t/3. Option to edit password/"<<endl;
		// 		cout<<"\t/4. Exit"<<endl;
  //               cout<<endl;
		// 		cout<<"Enter your Option: ";
		// 		cin>>choice;
		// 		cin.ignore();
		// 		system("CLS");
		// 		if(choice == 1) {
		// 			teacher.makeStudentsGradeTable();
		// 		} else if(choice == 2) {
		// 			Teacher *ptr = &teacher;
		// 			ptr->view();
		// 		} else if(choice == 3) {
		// 			teacher.editDetails();
		// 		} else if(choice == 4) {
  //                   return false;
		// 		} else {
		// 			cout<<"Error: Invalid choice of Option."<<endl;
		// 			return false;
  //               }
		// 	} else if(user.getUserClassification() == "Admin") {
		// 		Admin admin(username);
		// 		cout<<"\t/1. Option used for registration of new details in files/"<<endl;
		// 		cout<<"\t/2. Option to view details/"<<endl;
		// 		cout<<"\t/3. Option to edit user details/"<<endl;
		// 		cout<<"\t/4. Option to search for the username in the user's file/"<<endl;
		// 		cout<<"\t/5. Exit"<<endl;
  //               cout<<endl;
		// 		cout<<"Enter your Option: ";
		// 		cin>>choice;
		// 		cin.ignore();
		// 		system("CLS");
		// 		if(choice == 1) {
		// 			admin.registration();
		// 		} else if(choice == 2) {
		// 			Admin *ptr1 = &admin;
		// 			ptr1->view();
		// 		} else if(choice == 3) {
		// 			Admin *ptr2 = &admin;
		// 			ptr2->editDetails();
		// 		} else if(choice == 4){
		// 			string search_for_username;
		// 			cout<<"Enter username: ";
		// 			cin>>search_for_username;
		// 			cin.ignore();
		// 			Employee::searchForUsername(search_for_username);
		// 		} else if(choice == 5) {
  //               	return false;
		// 		} else {
		// 			cout<<"Error: Invalid choice option."<<endl;
		// 			return false;
  //               }
		// 	} else {
		// 		cout
		// 		<<"You are not classified/group into any user classification in our management system, "
		// 		<<"please inform the registrar to fix the issue."
		// 		<<endl;
		// 	} return true;
		// }
  //  bool login::handlingLogin() {
  //   	const char* FileName = "temp_file_two.txt";
  //   	if(remove(FileName) == 0) {
  //   		//"The memory in the temp file two text file has being cleaned/deleted.";
  //   	} else {
  //   		perror("Error: the temp file two failed to be released/deleted.");
  //   	}
  //   	const char* otherFileName = "temp_file_one.txt";
  //   	if(remove(otherFileName) == 0) {
  //   		//"The memory in the temp file one text file has being cleaned/deleted.";
  //   	} else {
  //   		perror("Error: the temp file one failed to be released/deleted.");
  //   	}
  //   	string username;
  //   	cout<<"\t\t\t\t\t\t\t\t\tHIE WELCOME TO THE LOGIN PAGE"<<endl;
  //   	cout<<"To login"<<endl;
  //   	cout<<"Please Enter your username: ";
  //   	cin>>username;
  //   	cin.ignore();
  //   	if(bool exists = ValidationCheck::validateUsername(username)) {
  //   		string password;
  //   		cout<<"Please Enter your password: ";
  //   		cin>>password;
  //   		cin.ignore();
  //   		system("CLS");
  //   		exists = ValidationCheck::validatePassword(password);
  //   		if(exists) {
  //   			exists = DatabaseManager::authenticateUserInFileManagementSystem(username,
		// 		password, "users_File.txt", 6);
  //   			if(exists) {
  //   				//if logged in these function will handle their menu on regards to what their logged in as
  //   				User user(username);
  //   				cout
		// 			<<"HIE USER "<<user.getId()<<" User INFO: "<<user.first_name<<" "<<user.last_name
		// 			<<" TO THE FREE LEARNINGS MANAGEMENT SYSTEM"<<endl;
  //   				AllocateUser::allocateUserLoginClassification(username);
  //   			} else {
  //   				//User failed to authenticate the account
  //   				cout<<"Our records don't have these credentials stored in the file."<<endl;
  //   				return false;
  //   			}
  //   		} else {
  //   			cout<<"Error: the password is invalid."<<endl;
  //   		}
  //   	} else {
  //   		cout<<"Error: the username is invalid."<<endl;
  //   	} return true;
  //   }
