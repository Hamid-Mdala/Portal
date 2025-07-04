#include "DatabaseManager.h"
#include <iostream>
// map<const string, UserDetailsUsingMap> userDataMap;
// map<const string, DetailsForOneCommaInLineUsingMap> twoFieldsMap;
// map<const string, DetailsForTwoCommaInLineUsingMap> threeFieldsMap;
// map<const string, DetailsForThreeCommaInLineUsingMap> fourFieldsMap;
// using namespace std;
//
//
// 		string single_line_from_temp;
// 		char del = ',';
// 		int counting_fields = 0;
// 		void Utility::setCount(const int count) {
// 			counting_fields = count;
// 		}
// 		int Utility::getCountedFields() {
// 			//[[nodiscard]] is used to tell the compiler to warn the user if the return value is not used
// 			return counting_fields;
// 		}
// 		bool Utility::countCommasInLine(const string& filename) {
// 			ifstream inFile(filename);
// 			ofstream outFile("temporarily_table.txt");
// 			//algorithm handling if the file can't/can open
// 			if(!inFile.is_open()) {
// 				cerr<<"Error: Unable to open and count the fields in the "<<filename<<endl;
// 				return false;
// 			}
// 				int just_count_one_line=0;
// 				string store_one_line;
// 				while(getline(inFile, store_one_line)) {
// 					just_count_one_line++;  //this has to be postfix
// 					if(just_count_one_line == 1) {
// 						outFile<<store_one_line<<endl;
// 					}
// 				}
// 				//algorithm opening and reading the extracted line, so that we could count the commas/
// 				//fields in the extracted single line from the temporarily file
// 				ifstream tempFile("temporarily_table.txt");
// 				if(!tempFile.is_open()) {
// 					cerr<<"Error: Unable to open the temporarily file."<<endl;
// 				} else {
// 					string stored_one_line;
// 					int comma_counts_in_line=0;
// 					while(getline(tempFile, stored_one_line)) {
// 						for(char lidx : stored_one_line) {
// 							if(lidx == ',') {
// 								comma_counts_in_line++;
// 							}
// 						} counting_fields = comma_counts_in_line;
// 					} if (counting_fields == comma_counts_in_line) {
// 						return true;
// 					} return false;
// 					//end of the algorithm counting the comma in the extracted single line
// 				} return true;
// 			}
// 		bool Utility2::handlingDuplication(const string& filename, int num_of_fields_in_line) {
// 			//algorithm calling the count fields in file, so that we could load different files with different
// 			//fields in the map data structure
// 			Utility utilityTools;
// 			bool exists;
// 			exists = utilityTools.countCommasInLine(filename);
// 			if(exists) {
// 				if(utilityTools.getCountedFields() == num_of_fields_in_line) {
// 					ifstream inFile(filename);
// 					if(!inFile.is_open()) {
// 						cerr<<"Error: unable to open the file."<<endl;
// 					} else {
// 						//below are if conditions used to handle the number of counted comma in the file if
// 						//the above is condition is true
// 						if(num_of_fields_in_line == 1) {
// 							string details_field1;
// 							string details_field2;
// 							while(getline(inFile, details_field1, del)) {
// 								getline(inFile, details_field2, '\n');
// 								twoFieldsMap[details_field1] = {details_field2};
// 							}
// 						} else if(num_of_fields_in_line == 2) {
// 							string details_field1;
// 							string details_field2;
// 							string details_field3;
// 							while(getline(inFile, details_field1, del)) {
// 								getline(inFile, details_field2, del);
// 								getline(inFile, details_field3, '\n');
// 								threeFieldsMap[details_field1] = {details_field2, details_field3};
// 							}
// 						} else if(num_of_fields_in_line == 3) {
// 							string details_field1;
// 							string details_field2;
// 							string details_field3;
// 							string details_field4;
// 							while(getline(inFile, details_field1, del)) {
// 								getline(inFile, details_field2, del);
// 								getline(inFile, details_field3, del);
// 								getline(inFile, details_field4, '\n');
// 								fourFieldsMap[details_field1] = {details_field2, details_field3, details_field4};
// 							}
// 						} else if(num_of_fields_in_line == 6) {
// 							string details_field1;
// 							string details_field2;
// 							string details_field3;
// 							string details_field4;
// 							string details_field5;
// 							string details_field6;
// 							string details_field7;
// 							while(getline(inFile, details_field1, del)) {
// 								getline(inFile, details_field2, del);
// 								getline(inFile, details_field3, del);
// 								getline(inFile, details_field4, del);
// 								getline(inFile, details_field5, del);
// 								getline(inFile, details_field6, del);
// 								getline(inFile, details_field7, '\n');
// 								userDataMap[details_field1]=
// 								{details_field2, details_field3, details_field4,
// 									details_field5, details_field6, details_field7};
// 							}
// 						} else {
// 							cout
// 							<<"The management system is not expecting any file with such number of fields in it."
// 							<<endl;
// 							cout
// 							<<"Hence it doesn't have a load mechanism in the map data structure, "
// 							<<"please contact the developers to fix the issue."
// 							<<endl;
// 							//issue might be if the user (admins) first registration of the user's or course,
// 							//he/she added an extra comma inside while entering the details
// 							//issue might be if the first user student entered an extra comma,
// 							//while enrolling the in into a program
// 							//issue might be if the first user teacher entered a comma,
// 							//while making the students grade details
// 						}
// 					}
// 					if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
// 						//	The filename is a new file, so it doesn't have fields of data in it...;
// 						//	A reason could be that the filename is an empty file and doesn't have any comma(s).;
// 					} else {
// 						cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
// 					} return false;
// 				}
// 			} return true;
// 		}
//
//
// 	/*
// 	I KNOW I DIDN'T USE THE CONFIG, BUT IT COULD BE USED WHEN CONFIGURING IF THE FILE IS ABLE TO OPEN OR NOT
// 		static bool configFile(string filename) {
// 			read from File inFile(filename);
// 			if(!inFile.is_open()) {
// 				<<"Error: Unable to open the file."<<;
// 				return false;				//separate function handling if the file doesn't open
// 			} return true;
// 		}
// 	*/
// 	bool DatabaseManager::authenticateUserInFileManagementSystem
// 	(const string& details_field1,const string& details_of_other_fields,
// 	const string& filename,int num_of_fields_on_line) {
// 		//algorithm used while checking or even authenticating two details in files
// 		Utility utilityTools;
// 		utilityTools.countCommasInLine(filename);
// 		if(utilityTools.getCountedFields() == num_of_fields_on_line){
// 			//below are if conditions used to handle the number of counted comma in file
// 			if(num_of_fields_on_line == 6) {
// 				Utility2::handlingDuplication(filename, num_of_fields_on_line);
// 				for(auto pair : userDataMap) {
// 					//will search through the map until the end of the map
// 					if(userDataMap.find(details_field1) != userDataMap.end() &&
// 					userDataMap[details_field1].details_field2 == details_of_other_fields) {
// 						return true;
// 					} else {
// 						cout<<"Error: invalid username/password."<<endl;
// 						return false;
// 					}
// 				}
// 			} else if(num_of_fields_on_line == 1) {
// 				ifstream inFile(filename);
// 				if(!inFile.is_open()) {
// 					cerr<<"Error: Unable to open the file."<<endl;
// 				} else {
// 					string id_field;
// 					string course_field;
// 					string result1;
// 					string result2;
// 					while(getline(inFile, id_field, utilityTools.del)) {
// 						getline(inFile, course_field, '\n');
// 						if(details_field1 == id_field && details_of_other_fields == course_field) {
// 							result1 = details_field1;
// 							result2 = details_of_other_fields;
// 						}
// 					}
// 					if(result1 == details_field1 && result2 == details_of_other_fields){
// 						return true;
// 					} else {
// 						return false;
// 					}
// 				}
// 			} else if(num_of_fields_on_line == 3) {
// 				Utility2::handlingDuplication(filename, num_of_fields_on_line);
// 				for(auto pair : fourFieldsMap) {
// 					//will search through the map until the end of the map
// 					if(fourFieldsMap.find(details_field1) != fourFieldsMap.end() &&
// 					fourFieldsMap[details_field1].details_field3 == details_of_other_fields) {
// 						return true;
// 					} else {
// 						return false;
// 					}
// 				}
// 			} else {
// 				//issue might be if the user (admins) first registration of the user's or course,
// 				//he/she added an extra comma inside while entering the details.
// 				//issue might be if the first user student entered a comma while enrolling the in into a program Or
// 				//issue might be if the first user teacher entered a comma while making the students grade details.
// 				cout
// 				<<"The management system is not expecting any file with such number of fields in it."
// 				<<endl
// 				<<"Hence it doesn't have viewing mechanism to display details on the console,"
// 				<<" please contact the developers to fix the issue."
// 				<<endl;
// 			}
// 		} else {
// 			if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
// 				//	The filename is a new file, so it doesn't have fields of data in it.
// 				//	A reason could be that the "<<filename<<" is a blank file and doesn't have any comma(s).
// 			} else {
// 				cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
// 			} return false;
// 		} return false;
// 	}
// 		void DatabaseManager::registerUser
// 		(const string& filename,const string& username,
// 		const string& password,const string& id,const string& first_name,
// 		const string& last_name, const string& sex,const string& date_of_birth) {
// 			ofstream outFile(filename, ios_base::app);
// 			if(!outFile.is_open()) {
// 				cerr<<"Error: Unable to open the user database inorder to register the user."<<endl;
// 			} else {
// 				outFile
// 				<<username<<","<<password<<","<<id<<","<<first_name<<","<<last_name<<","<<sex<<","<<date_of_birth
// 				<<endl;
// 				cout<<"you have successfully saved details in user's file."<<endl;
// 				//registration of any user in the user database system
// 			}
// 		}
// 		bool DatabaseManager::deleteFileName() {
// 			//Delete function used when they edit their details
// 			const char* FileName = "users_File.txt";
// 			if( remove(FileName) == 0) {
// 				return true;
// 			} else {
// 				return false;
// 			}
// 		}
// 		bool DatabaseManager::renameFileName() {
// 			//Rename function used when they edit details
// 			const char* NewFile = "users_File.txt";
// 			const char* OldFile = "temporarily_edit_table.txt";
// 			if(rename(OldFile, NewFile) == 0) {
// 				return true;
// 			} else {
// 				return false;
// 			}
// 		}
// 		bool DatabaseManager::searchForFirstAndSecondField
// 		(const string& filename,const string& details_field1,
// 		const string& details_of_other_fields,int num_of_fields_on_line) {
// 			//algorithm used to verify the first field or the second field in the file
// 			//will help the one-to-many relationship inside the teacher when a teacher is being registered to course
// 			//one to many like: only one course taught by one teacher but a teacher could teach as many courses,
// 			//so another teacher can't register to a course that is existing/taught by a teacher
// 			ofstream isNotYetMade(filename, ios_base::app); //when the filename is not yet made open it in append
// 			Utility utilityTools;
// 			utilityTools.countCommasInLine(filename);
// 			if(utilityTools.getCountedFields() == num_of_fields_on_line) {
// 				//if conditions used to handle the number of counted comma in the file if the above is condition is true
// 				//these if condition will verify if fields one or field2 two is existing in their appropriate fields.
// 				if(num_of_fields_on_line == 1) {
// 					ofstream tempFileOne("temp_file_one.txt");
// 					ofstream tempFileTwo("temp_file_two.txt");
// 					ofstream editFile("temporarily_edit_table.txt");
// 					ifstream inFile(filename);
// 					if(!inFile.is_open()) {
// 						cerr<<"Error: Unable to open the file."<<endl;
// 					} else {
// 						string assume1;
// 						string assume;
// 						string line;
// 						string first_field;
// 						string other_fields;
// 						while(getline(inFile, line)) {
// 							stringstream ss(line);
// 							while(getline(ss, first_field, utilityTools.del)) {
// 								getline(ss, other_fields, '\n');
// 								if(first_field == details_field1 || other_fields == details_of_other_fields) {
// 									tempFileOne<<line<<endl;
// 									tempFileTwo<<line<<endl;
// 									assume = details_field1;
// 									assume1 = details_of_other_fields;
// 								} else {
// 									editFile<<line<<endl;
// 								}
// 							}
// 						}
// 						if(assume == details_field1  || assume1 == details_of_other_fields) {
// 							std::cout << "Error: " << details_field1 << "already exists in our credentials" << "\n";
// 							return true;
// 						} else {
// 							return false;
// 						}
// 					}
// 					//next if condition will only verify one field from files that have files either 2 or 3 and 6 only
// 				} else if(num_of_fields_on_line == 2 || num_of_fields_on_line == 3 || num_of_fields_on_line == 6) {
// 					ofstream outFile("temporarily_table.txt");
// 					ofstream otherOutFile("temporarily_table2.0.txt");
// 					//PLEASE NOTE: we are using the temporarily_table2.0 when the student wants to view their grades
// 					//cause for some reason if we only use the temporarily_table the results of the
// 					//students grade won't show up.
// 					ofstream editFile("temporarily_edit_table.txt");
// 					//PLEASE NOTE: hence the temporarily_table and temporarily_table2.0 has to be bonded together,
// 					//so that the view function for the grades works.
// 					ifstream inFile(filename);
// 					if( !inFile.is_open()) {
// 						cerr<<"Error: Unable to open file"<<endl;
// 					} else {
// 						string assume;
// 						string line;
// 						string first_field;
// 						while(getline(inFile, line)) {
// 							size_t commaPos = line.find(utilityTools.del);
// 							if(commaPos != string::npos) {
// 								first_field = line.substr(0, commaPos);
// 							}
// 							if(first_field == details_field1) {
// 								outFile<<line<<endl;
// 								otherOutFile<<line<<endl;
// 								assume = details_field1;
// 							} else {
// 								editFile<<line<<endl;
// 							}
// 						}
// 						if(assume == details_field1) {
// 							return true;
// 						} else {
// 							return false;
// 						}
// 					}
// 				} else {
// 					cout<<num_of_fields_on_line<<endl;
// 					//issue might be if the user admin first registration of the user's or course,
// 					//he/she added an extra comma inside while entering the details.
// 					//issue might be if the first user student entered a comma while enrolling the in into a program
// 					//issue might be if the first user teacher entered a comma while making the students grade details.
// 					cout
// 					<<"The management system is not expecting any file with such number of fields in it."
// 					<<endl
// 					<<"Hence it doesn't have viewing mechanism to display details on the console,"
// 					<<" please contact the developers to fix the issue."
// 					<<endl;
// 					}
// 			} else {
// 				if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
// 					//	<<The filename is a new file, so it doesn't have fields of data in it.;
// 					//	A reason could be that the "<<filename<<" is a blank file and doesn't have any comma(s).;
// 				} else {
// 					cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
// 				} return false;
// 			} return true;
// 		}
//
DatabaseManager::DatabaseManager(const std::string &user, const std::string &password, const std::string &db)
	: user_(user), password_(password), db_(db)
{}
bool DatabaseManager::connect() {
	try {
		sql::Driver *driver = sql::mariadb::get_driver_instance();
		sql::SQLString url("jdbc:mariadb://localhost:3306/" + db_);
		sql::Properties properties({{"user",user_ }, {"password", password_}});
		//store connection as a member if needed
		conn_ = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
		//std::cout << "connected to the MariaDB" << "\n";
		return true;
	} catch (sql::SQLException& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return false;
	}
}


bool DatabaseManager::createUser(const std::string &username, const std::string &password,
	const std::string &first_name, const std::string &last_name,
	const std::string &category, const std::string &dob)
{
	
}

bool DatabaseManager::authenticateUser(const std::string& username, const std::string& password) {
	if (!conn_) return false;
	std::unique_ptr<sql::PreparedStatement> stmt(
		conn_->prepareStatement("SELECT COUNT(*) FROM Users WHERE username =? AND password=?"));
	stmt->setString(1, username);
	stmt->setString(2, password);
	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next() && res->getInt(1)) {
		std::cout << "Login successful" << "\n";
		return true;
	}
	int count = 0;
	std::cout << "Invalid credentials, please try again." << "\n";
	++count; if (count == 3) return true;   //this will break the traversal in the while loop

	return false;
}
bool DatabaseManager::searchUser(const std::string &username) {
	if (!conn_) return false;
	//make a statement
	std::unique_ptr<sql::PreparedStatement> stmt(
	conn_->prepareStatement("SELECT COUNT(*) FROM Users WHERE username =?"));
	stmt->setString(1, username);
	std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
	if (res->next()) {
		return true;
	}

	return false;
}

//
//
// 		bool ReadFileThatAreExtractingASingleUserDetails::readFromAFile(const string& filename, const int num_of_fields_in_line) {
// 			/*algorithm reading from files details that the map can't handle reading because of
// 			duplication/overwritting in the map, so I used an
// 			array algorithm method used to view details in those files*/
// 			Utility utilityConfig;
// 			utilityConfig.countCommasInLine(filename);
// 			//IF empty then not equal to one
// 			if(utilityConfig.getCountedFields() == num_of_fields_in_line) {
// 				ifstream inFile(filename);
// 				if(!inFile.is_open()) {
// 					cerr<<"Error: Unable to open the file."<<endl;
// 				} else {
// 					string line;
// 					//these if conditions algorithm reads from files that have only one comma,
// 					//but they have two fields in the file
// 					if(num_of_fields_in_line == 1) {
// 						char details_field1[100];
// 						char details_field2[100];
// 						int line_count=1;
// 						while(getline(inFile, line)) {
// 							const int line_index = line_count++;
// 							int i=0;
// 							int j=0;
// 							int count = 0;
// 							for(const char lidx : line) {
// 								if(lidx != utilityConfig.del && count == 0) {
// 									details_field1[i] = lidx;
// 									i++;
// 								} else if(lidx != utilityConfig.del && count == 1) {
// 									details_field2[j] = lidx;
// 									j++;
// 								} else {
// 									count++;
// 								}
// 							}
// 							details_field1[i] = '\0';
// 							details_field2[j] = '\0';
// 							//handling the view for different file containing the duplicated key word
// 							if(filename == "temp_file_one.txt") {
// 								//made an extracted file in the searchForFirstAndLastField in my code
// 								cout<<"USER-ID: "<<line_index<<". "<<details_field1<<endl;
// 							} else if(filename == "temp_file_two.txt") {
// 								//made an extracted file in the searchForFirstAndLastField in my code
// 								cout<<"COURSE-ID: "<<line_index<<". "<<details_field2<<endl;
// 							} else if(filename == "students_enroll_course_table_file.txt" ||
// 							filename == "teachers_table_file.txt") {
// 								//this is are not extracted file,
// 								//they are files containing details when we register either the teacher or the student
// 								if(filename == "teachers_table_file.txt" || "students_enroll_course_table_file.txt") {
// 									cout<<"USER-ID: "<<details_field1<<endl;
// 									cout<<"COURSE-ID: "<<details_field2<<endl;
// 									cout<<endl;
// 								} cout<<endl;
// 							} else {
// 								cout
// 								<<"The filename is invalid and theirs no if condition handling the view."
// 								<<"for "<<filename<<" name is our management system."
// 								<<endl;
// 							}
// 						}
// 						//next if conditions algorithm handles the view of the students grade file
// 					} else if(num_of_fields_in_line == 3) {
// 						char details_field1[100];
// 						char details_field2[100];
// 						char details_field3[100];
// 						char details_field4[100];
// 						while(getline(inFile, line)) {
// 							int i=0;
// 							int j=0;
// 							int k=0;
// 							int u=0;
// 							int count = 0;
// 							for(char lidx : line) {
// 								if(lidx != utilityConfig.del && count == 0) {
// 									details_field1[i] = lidx;
// 									i++;
// 								} else if(lidx != utilityConfig.del && count == 1) {
// 									details_field2[j] = lidx;
// 									j++;
// 								} else if(lidx != utilityConfig.del && count == 2) {
// 									details_field3[k] = lidx;
// 									k++;
// 								} else if(lidx != utilityConfig.del && count == 3) {
// 									details_field4[u] = lidx;
// 									u++;
// 								} else {
// 									count++;
// 								}
// 							}
// 							details_field1[i] = '\0';
// 							details_field2[j] = '\0';
// 							details_field3[k] = '\0';
// 							details_field4[u] = '\0';
// 							cout
// 							<<"USER-ID: "<<details_field1<<endl
// 							<<"STUDENT_CLASSIFICATION: "<<details_field2<<endl
// 							<<"COURSE-ID: "<<details_field3<<endl
// 							<<"GPA: "<<details_field4<<endl
// 							<<endl;
// 						}
// 					} else {
// 						//issue might be if the user (admins) first registration of the user's or course,
// 						//he/she added an extra comma inside while entering the details.
// 						//issue might be the first user student entered a comma while enrolling the in into a program
// 						//issue might be the first user teacher entered a comma while making the students grade details
// 						cout<<"The management system is not expecting any file with such number of fields in it."<<endl;
// 						cout
// 						<<"Hence it doesn't have viewing mechanism to display details on the console,"
// 						<<" please contact the developers to fix the issue."
// 						<<endl;
// 					}
// 				}
// 			} else {
// 				if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
// 					//	The filename is a new file, so it doesn't have fields of data in it.
// 					//	A reason could be that the "<<filename<<" is a blank file and doesn't have any comma(s).
// 				} else {
// 					cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
// 				} return false;
// 			} return true;
// 		}
