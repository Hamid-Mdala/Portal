#include "PortalUsers.h"
#include <iostream>
using namespace std;
//int main() function will handle a case when the files are not yet made on a server: else take them to the logging page
int main() {
	const string admin_username = "Admin_User1";
	//const admin username is used when to check if the system is still running on a server with the Admin_User 1
	string password = "EQUAL TO SOMETHING";
	if(bool exists = DatabaseManager::searchForFirstAndSecondField
	("admin_table_file.txt", admin_username, password, 1)) {
		//Check in the admin table if the constant variable exists, it's true call the handlingLogin() function
		while (true) {
			ofstream outFile("temp_file_one.txt");
			ofstream otherOutFile("temp_file_two.txt");
			outFile.close();
			otherOutFile.close();
			if (login::handlingLogin()) {
                break;
            }
			system("CLS");
		}
	} else {
		//if else then register an admin in the admin table as well as the user's file
		string username;
		cout<<"Before you could go to login, please ensure the admin is not yet registered to make any operation"<<endl;
		cout<<"Please ensure that the username you enter is: 'Admin_User1'"<<endl;
		cout<<"Enter username: ";
		cin>>username;
		cin.ignore();
		exists = ValidationCheck::validateUsername(username);
		if(exists) {
			if(username == admin_username) {
				cout<<"Enter Password: ";
				cin>>password;
				cin.ignore();
				//Validate the password
				exists = ValidationCheck::validatePassword(password);
				if(exists) {
					string id;
					cout<<"Enter admin-ID: ";
					cin>>id;
					cin.ignore();
					//Validate the ID
					exists = ValidationCheck::validateId(id);
					if(exists) {
						string first_name;
						cout<<"Enter First Name: ";
						cin>>first_name;
						cin.ignore();
						//Validate the first name
						exists = ValidationCheck::validateFirstName(first_name);
						if(exists) {
							string last_name;
							cout<<"Enter Last Name: ";
							cin>>last_name;
							cin.ignore();
							//Validate the last name
							exists = ValidationCheck::validateLastName(last_name);
							if(exists) {
								string sex;
								cout<<"Enter Gender: ";
								cin>>sex;
								cin.ignore();
								//Validate the gender
								exists = ValidationCheck::validateGender(sex);
								if(exists) {
									string date_of_birth;
									cout<<"Enter Date-Of_Birth: ";
									cin>>date_of_birth;
									cin.ignore();
									//Validate the date of birth
									exists = ValidationCheck::validateDOB(date_of_birth);
									if(exists) {
										DatabaseManager::registerUser("users_File.txt", username,
										password, id, first_name, last_name, sex, date_of_birth);
										ofstream outputFile("admin_table_file.txt", ios::app);
										if(!outputFile.is_open()) {
											cerr<<"Error: Unable to open the admin table file."<<endl;
										} else {
											outputFile<<username<<","<<id<<endl;
											cout<<"The right details have being saved in admin table file is saved."
											<<endl;
										}
									} else {
										cout<<"Error: the date 0f birth is invalid."<<endl;
									}
								} else {
									cout<<"Error: the gender is invalid."<<endl;
								}
							} else {
								cout<<"Error: the last name is invalid."<<endl;
							}
						} else {
							cout<<"Error: the first name is invalid."<<endl;
						}
					} else {
						cout<<"Error: the ID is invalid."<<endl;
					}
				} else {
					cout<<"Error: the password is invalid."<<endl;
				}
			} else {
				cout<<"The username you entered is not the same as to our requirements in our management system."<<endl;
			}
		} else {
			cout<<"Error: the username is invalid."<<endl;;
		}
	}
	return 0;
}