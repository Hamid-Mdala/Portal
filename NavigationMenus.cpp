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
