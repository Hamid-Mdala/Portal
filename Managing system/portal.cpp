#include <map>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

struct UserDetailsUsingMap {					//is used for the user's details file
	// the key is string username;
	string password;
	string id;
	string first_name;
	string last_name;
	string sex;
	string date_of_birth;
}; map<string, UserDetailsUsingMap> userDataMap;

struct DetailsForOneCommaInLineUsingMap {		//is used for the students enroll course file, and the teachers course table file
	// the key is string details_field1;
	string details_field2;
}; map<string, DetailsForOneCommaInLineUsingMap> twoFieldsMap;

struct DetailsForTwoCommaInLineUsingMap {		//is used for the students entry form file, and the course table file
	// the key is string details_field1;
	string details_field2;
	string details_field3;
}; map<string, DetailsForTwoCommaInLineUsingMap> threeFieldsMap;
	
struct DetailsForThreeCommaInLineUsingMap {		//is used for the students grade file
	// the key is string details_field1	
	string details_field2;
	string details_field3;
	string details_field4;
}; map<string, DetailsForThreeCommaInLineUsingMap> fourFieldsMap;

class Utility {
	public:
		string single_line_from_temp;
		char delimeter = ',';
	private:
		int count;
	public:
		void setCount(int count) {
			this->count = count;
		}
		int getCount() {
			return count;
		}
		bool coutCommasInLine(string filename, int num_of_fields_on_line) {
			ifstream inFile(filename);
			ofstream outFile("temporarly_table.txt");
			//algorithm handling if the file can't/can open 
			if(!inFile.is_open()) {
				cerr<<"Error: Unable to open and cout the fields in the "<<filename<<endl;
				return false;
			} else {
				int just_count_one_line=0;
				string store_one_line;
				while(getline(inFile, store_one_line)) {
					just_count_one_line++;
					if(just_count_one_line == 1) {
						outFile<<store_one_line<<endl;
					}
				}
				//algorithm opening and reading the extracted line, so that we could count the commas/fields in the extracted single line from the temporarly file
				ifstream tempFile("temporarly_table.txt");
				if(!tempFile.is_open()) {
					cerr<<"Error: Unable to open the temporarly file."<<endl;
				} else {
					string stored_one_line;
					int comma_counts_in_line=0;
					while(getline(tempFile, stored_one_line)) {
						for(int lidx = 0; lidx < stored_one_line.size(); lidx++) {
							if(stored_one_line[lidx] == ',') {
								comma_counts_in_line++;
							}
						}
					}	
					//end of the algorithm counting the comma in the extracted single line
					this->count = comma_counts_in_line;
					//assign the count attribute member in the class Utility
				}
			} return true;
		}
	public:	
		bool handlingDuplication(string filename, int num_of_fields_in_line) {
			//algorithm calling the count fields in file, so that we could load different files with different fields in the map data structure
			bool exists;
			exists = this->coutCommasInLine(filename, num_of_fields_in_line);
			if(exists) {
				if(this->count == num_of_fields_in_line) {
					ifstream inFile(filename);
					if(!inFile.is_open()) {
						cerr<<"Error: unable to open the file."<<endl;
					} else {
						//below are if conditions used to handle the number of counted comma in the file if the above is condition is true
						if(num_of_fields_in_line == 1) {
							string details_field1;
							string details_field2;
							while(getline(inFile, details_field1, delimeter)) {
								getline(inFile, details_field2, '\n');
								twoFieldsMap[details_field1] = {details_field2};
							} 
						} else if(num_of_fields_in_line == 2) {
							string details_field1;
							string details_field2;
							string details_field3;
							while(getline(inFile, details_field1, delimeter)) {
								getline(inFile, details_field2, delimeter);
								getline(inFile, details_field3, '\n');
								threeFieldsMap[details_field1] = {details_field2, details_field3};
							} 
						} else if(num_of_fields_in_line == 3) {
							string details_field1;
							string details_field2;
							string details_field3;
							string details_field4;
							while(getline(inFile, details_field1, delimeter)) {
								getline(inFile, details_field2, delimeter);
								getline(inFile, details_field3, delimeter);
								getline(inFile, details_field4, '\n');
								fourFieldsMap[details_field1] = {details_field2, details_field3, details_field4};
							} 
						} else if(num_of_fields_in_line == 6) {
							string details_field1;
							string details_field2;
							string details_field3;
							string details_field4;
							string details_field5;
							string details_field6;
							string details_field7;
							while(getline(inFile, details_field1, delimeter)) {
								getline(inFile, details_field2, delimeter);
								getline(inFile, details_field3, delimeter);
								getline(inFile, details_field4, delimeter);
								getline(inFile, details_field5, delimeter);
								getline(inFile, details_field6, delimeter);
								getline(inFile, details_field7, '\n');
								userDataMap[details_field1] = {details_field2, details_field3, details_field4, details_field5, details_field6, details_field7};
							} 
						} else {	
							//issue might be if the user (admins) first registration of the user's or course, he/she added an extra comma inside while entering the detials
							//issue might be if the first user student entered an extra comma while enrolling the in into a program
							//issue might be if the first user teacher entered an comma while making the students grade details
							cout<<"The management system is not expecting any file with such number of fields in it."<<endl;
							cout<<"Hence it doesn't have a load mechanism in the map data structure, please contant the developers to fix the issue."<<endl;
						}
					} return true;
				} else {
					if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
					//	cout<<"The "<<filename<<" is a new file, so it doesn't have fields of data in it..."<<endl;
					//	cout<<"A reason could be that the "<<filename<<" is an empty/blank file and doesn't have any fields/comma(s)."<<endl;
					} else {
						cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
					} return false;	
				}
			} return true;
		}
		
};

class AbstractSearch {
	public:
	//abstracted function used in my code
		virtual void applySearchForStudent()=0;
		virtual bool view()=0;
		virtual bool editDetails()=0;
};

class ReadFileThatAreExtractingASingleUserDetails {
	public:
		static bool readFromAFile(string filename, int num_of_fields_in_line) {
			/*algorithm reading from files details that the map con't handle reading because of duplication/overwritting in the map, so i used an
			array algorithm method used to to view details in those files*/
			Utility utilityConfig;
			bool exists;
			exists = utilityConfig.coutCommasInLine(filename, num_of_fields_in_line);
			//IF empty then not equal to one
			if(utilityConfig.getCount() == num_of_fields_in_line) {
				ifstream inFile(filename);
				if(!inFile.is_open()) {
					cerr<<"Error: Unable to open the file"<<endl;
				} else {
					string line;
					//these if conditions algorithm reads from files that have only one comma, but they have two fields in the file
					if(num_of_fields_in_line == 1) {
						char details_field1[100];
						char details_field2[100];
						int line_count=1;
						while(getline(inFile, line)) {
							int line_index = line_count++;
							int i=0;
							int j=0;
							int count = 0;
							for(int lidx = 0; lidx < line.size(); lidx++) {
								if(line[lidx] != utilityConfig.delimeter && count == 0) {
									details_field1[i] = line[lidx];
									i++;
								} else if(line[lidx] != utilityConfig.delimeter && count == 1) {
									details_field2[j] = line[lidx];
									j++;
								} else {
									count++;
								}
							}
							details_field1[i] = '\0';
							details_field2[j] = '\0';
							//handling/implementing the a unique view for different extracted/containing files in my management system
							if(filename == "temp_file_one.txt") {					//made an extrated file in the searchForFirstAndLastField in my code
								cout<<"USER-ID: "<<line_index<<". "<<details_field1<<endl;	
							} else if(filename == "temp_file_two.txt") {			//made an extracted file in the searchForFirstAndLastField in my code
									cout<<"COURSE-ID: "<<line_index<<". "<<details_field2<<endl;	
							} else if(filename == "students_enroll_course_table_file.txt" || filename == "teachers_table_file.txt") { 		//these is are not extracted file, they are files containing details when we register either the teacher or the student
								if(filename == "students_enroll_course_table_file") {
									cout<<"USER-ID: "<<details_field1<<endl;
									cout<<"COURSE-ID: "<<details_field2<<endl;
									cout<<endl;
									cout<<endl;
								} else if(filename == "teachers_table_file.txt" || "students_enroll_course_table_file.txt") {
									cout<<"USER-ID: "<<details_field1<<endl;
									cout<<"COURSE-ID: "<<details_field2<<endl;
									cout<<endl;
								}
							}
							 else {
								cout<<"The filename is invalid and theirs no if condition handling the view for "<<filename<<" name is our management system."<<endl;
							}
						}
						//next if conditions algorithm handles the view of the students grade file 
					} else if(num_of_fields_in_line == 3) {
						char details_field1[100];
						char details_field2[100];
						char details_field3[100];
						char details_field4[100];
						int line_count=1;
						while(getline(inFile, line)) {
							int line_index = line_count++;
							int i=0; 
							int j=0; 
							int k=0;
							int u=0;
							int count = 0;
							for(int lidx = 0; lidx < line.size(); lidx++) {
								if(line[lidx] != utilityConfig.delimeter && count == 0) {
									details_field1[i] = line[lidx];
									i++;
								} else if(line[lidx] != utilityConfig.delimeter && count == 1) {
									details_field2[j] = line[lidx];
									j++;
								} else if(line[lidx] != utilityConfig.delimeter && count == 2) {
									details_field3[k] = line[lidx];
									k++;
								} else if(line[lidx] != utilityConfig.delimeter && count == 3) {
									details_field4[u] = line[lidx];
									u++;
								} else {
									count++;
								}
							}
							details_field1[i] = '\0';
							details_field2[j] = '\0';
							details_field3[k] = '\0';
							details_field4[u] = '\0';
							cout
							<<"USER-ID: "<<details_field1<<endl
							<<"STUDENT_CLASSIFICATION: "<<details_field2<<endl
							<<"COURSE-ID: "<<details_field3<<endl
							<<"GPA: "<<details_field4<<endl
							<<endl;
						} 
					} else {
						//issue might be if the user (admins) first registration of the user's or course, he/she added an extra comma inside while entering the detials
						//issue might be if the first user student entered an extra comma while enrolling the in into a program
						//issue might be if the first user teacher entered an comma while making the students grade details
						cout<<"The management system is not expecting any file with such number of fields in it."<<endl;
						cout<<"Hence it doesn't have viewing mechanism to display details on the console, please contant the developers to fix the issue."<<endl;	
					}
				}
			} else {
				if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
					//	cout<<"The "<<filename<<" is a new file, so it doesn't have fields of data in it..."<<endl;
					//	cout<<"A reason could be that the "<<filename<<" is an empty/blank file and doesn't have any fields/comma(s)."<<endl;
				} else {
					cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
				} return false;	
			} return true;
		}
};

class DatabaseManager {
	public:
	/*
	I KNOW I DID'T USE THE CONFIG, BUT IT COULD BE USED WHEN CONFIGURING IF THE FILE IS ABLE TO OPEN OR NOT
		static bool configFile(string filename) {
			ifstream inFile(filename);
			if(!inFile.is_open()) {
				cerr<<"Error: Unable to open the file."<<endl;
				return false;				//separate fuction handling if the file doesn't open
			} return true;
		}
	*/
	public:
		static bool authenticateUserInFileManagementSystem(string username, string password, string filename, int num_of_fields_on_line) {
			//algorithm used while checking or even authenticating two details in files
			Utility utilityTools;
			utilityTools.coutCommasInLine(filename, num_of_fields_on_line);
			if(utilityTools.getCount() == num_of_fields_on_line) {
				//below are if conditions used to handle the number of counted comma in the file if the above is condition is true
				if(num_of_fields_on_line == 6) {
					utilityTools.handlingDuplication(filename, num_of_fields_on_line);
					for(auto pair : userDataMap) {
						//will search through the map until the end of the map
						if(userDataMap.find(username) != userDataMap.end() && userDataMap[username].password == password) {
							UserDetailsUsingMap userDetail = userDataMap[username];
							return true;
						} else {
							cout<<"Error: invalid password/username..."<<endl;
							return false;
						}
					} 
				} else if(num_of_fields_on_line == 1) {
					ifstream inFile(filename);
					if(!inFile.is_open()) {
						cerr<<"Error: Unable to open the file."<<endl;
					} else {
						string id_field;
						string course_field;
						string result1;
						string result2;
						while(getline(inFile, id_field, utilityTools.delimeter)) {
							getline(inFile, course_field, '\n');
							if(username == id_field && password == course_field) {
								result1 = username;
								result2 = password;
							} 	
						}
						if(result1 == username && result2 == password){
							return true;
						} else {
							return false;
						}
					}
				} else if(num_of_fields_on_line == 3) {
					utilityTools.handlingDuplication(filename, num_of_fields_on_line);
					for(auto pair : fourFieldsMap) {
						//will search through the map until the end of the map
						if(fourFieldsMap.find(username) != fourFieldsMap.end() && fourFieldsMap[username].details_field3 == password) {
							return true;
						} else {
							return false;
						}	
					}
				} else {
					//issue might be if the user (admins) first registration of the user's or course, he/she added an extra comma inside while entering the detials
					//issue might be if the first user student entered an extra comma while enrolling the in into a program
					//issue might be if the first user teacher entered an comma while making the students grade details
					cout<<"The management system is not expecting any file with such number of fields in it."<<endl;
					cout<<"Hence it doesn't have viewing mechanism to display details on the console, please contant the developers to fix the issue."<<endl;	
				}	
			} else {
				if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
					//	cout<<"The "<<filename<<" is a new file, so it doesn't have fields of data in it..."<<endl;
					//	cout<<"A reason could be that the "<<filename<<" is an empty/blank file and doesn't have any fields/comma(s)."<<endl;
				} else {
					cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
				} return false;	
			} return true;
		}
	public:	
		static void registerUser(string filename, string username, string password, string id, string first_name, 
		string last_name, string sex, string date_of_birth) {
			ofstream outFile(filename, ios_base::app);		//opening file in append mode every time use to write data
			if(!outFile.is_open()) {
				cerr<<"Error: Unable to open the user database inorder to register the user."<<endl;
			} else {
				outFile<<username<<","<<password<<","<<id<<","<<first_name<<","<<last_name<<","<<sex<<","<<date_of_birth<<endl;
				cout<<"you have successfully saved details in user's file."<<endl;
				//registration of any user in the user database system
			}
		}
	public:
		static bool deleteFileName() {
			//Delete fuction used when they edit their details
			const char* FileName = "users_File.txt";
			if(remove(FileName) == 0) {
				return true;
			} else {
				return false;
			}
			return true;
		}
	public:
		static bool renameFileName() {
			//Rename function used when they edit details 
			const char* OldFile = "temporarly_edit_table.txt";
			const char* NewFile = "users_File.txt";
			if(rename(OldFile, NewFile) == 0) {
				return true;
			} else {
				return false;
			}
			return true;
		}
	public:
		bool searchForFirstAndSecondField(string filename, string username, string field_two_details, int num_of_fields_on_line) {
			//algorithm used to verify the first field or the second field in the file
			//will help the one to many relationship inside the teacher when a teacher is being registered to a new course
			//one to many like: only one course tought by one teacher but a teacher could teach as many courses, so another teacher can't register to a course that is existng/tought by a teacher
			ofstream isNotYetMade(filename, ios_base::app);				//when the filename is not yet made open it in append 
			bool exists;
			Utility utilityTools;
			string assume;
			string assume1;
			exists = utilityTools.coutCommasInLine(filename, num_of_fields_on_line);
			if(utilityTools.getCount() == num_of_fields_on_line) {
				//below are if conditions used to handle the number of counted comma in the file if the above is condition is true
				//these if condition will verify if fields one or field2 two is existing in their appropriate fields
				if(num_of_fields_on_line == 1) {		
					ifstream inFile(filename);
					ofstream tempFileOne("temp_file_one.txt");
					ofstream tempFileTwo("temp_file_two.txt");	
					ofstream editFile("temporarly_edit_table.txt");  
					string line;
					string details_field1;
					string details_field2;
					while(getline(inFile, line)) {
						stringstream ss(line);
						while(getline(ss, details_field1, utilityTools.delimeter)) {
							getline(ss, details_field2, '\n');	
							if(username == details_field1 || field_two_details == details_field2) {
								tempFileOne<<line<<endl;
								tempFileTwo<<line<<endl;
								assume = username;
								assume1 = field_two_details;
							} else {
								editFile<<line<<endl;
							}
						}
					} 
					if(assume == username || assume1 == field_two_details) {
						return true;	
					} else {
						return false;
					}
					//next if condition will only verifying one field from files that have files either 2 or 3 and 6 only
				} else if(num_of_fields_on_line == 2 || num_of_fields_on_line == 3 || num_of_fields_on_line == 6) {
					ifstream inFile(filename);
					ofstream outFile("temporarly_table.txt");
					ofstream otherOutFile("temporarly_table2.0.txt"); //PLEASE NOTE: we are using the temporaraly_table2.0 when the student wants to view their grades cause for some reason if we only use the temporarly_table the results of the students grade wont show up.....
					ofstream editFile("temporarly_edit_table.txt");		//PLEASE NOTE: hence the temporarly_table and temporarly_table2.0 has to be bonded together, so that the view fuction for the grades works
					string line;
					string details_field1;	
					while(getline(inFile, line)) {
						size_t commaPos = line.find(",");
						if(commaPos != string::npos) {
							details_field1 = line.substr(0, commaPos);
						}
						if(username == details_field1) {
							outFile<<line<<endl;
							otherOutFile<<line<<endl;
							assume = username;
						} else {
							editFile<<line<<endl;
						} 
					}
					if(assume == username) {
						return true;
					} else {
						return false;
					}
				} else {
					//issue might be if the user (admins) first registration of the user's or course, he/she added an extra comma inside while entering the detials
					//issue might be if the first user student entered an extra comma while enrolling the in into a program
					//issue might be if the first user teacher entered an comma while making the students grade details
					cout<<"The management system is not expecting any file with such number of fields in it."<<endl;
					cout<<"Hence it doesn't have viewing mechanism to display details on the console, please contant the developers to fix the issue."<<endl;
				}
			} else {
				if(twoFieldsMap.empty() == 1 || threeFieldsMap.empty() == 1 || fourFieldsMap.empty() == 1) {
					//	cout<<"The "<<filename<<" is a new file, so it doesn't have fields of data in it..."<<endl;
					//	cout<<"A reason could be that the "<<filename<<" is an empty/blank file and doesn't have any fields/comma(s)."<<endl;
				} else {
					cout<<"The numbers of fields in file is not the equal to the fields counted in the file."<<endl;
				} return false;		 
			} return true;
		}
};
	
class ValidationCheck {
	//these class ValidationCheck handles the data consistancy when the user enters input im my management system
	public:
		static bool validateUsername(string username) {
			if(username.length() > 9 && username.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateId(string id) {
			if(id.length() > 9 && id.length() <= 15) {
				return true;	
			} else {
				return false;
			}
		}
	public:
		static bool validatePassword(string password) {
			if(password.length() > 9 && password.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateFirstName(string first_name) {
			if(first_name.length() > 2 && first_name.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateLastName(string last_name) {
			if(last_name.length() > 2 && last_name.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateGender(string sex) {
			if(sex.length() == 1) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateDOB(string date_of_birth) {
			if(date_of_birth.length() == 10) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateCourseId(string course_id) {
			if(course_id.length() > 9 && course_id.length() <= 15) {
				return true;	
			} else {
				return false;
			}
		}
	public:
		static bool validateCourseName(string course_name) {
			if(course_name.length() > 3 && course_name.length() <= 20) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateYear(string course_year) {
			if(course_year.length() == 4) {
				return true;
			} else {
				return false;
			}	
		}
	public:
		static bool validateStudentClassification(string student_classification) {
			if(student_classification.length() > 5 && student_classification.length() <= 9) {
				return true;			
			} else {
				return false;
			}
		}
	public:
		static bool validateGpa(string gpa) {
			if(gpa.length() == 4) {
				return true;
			} else {
				return false;
			}
		}
		
};

class User {
	private:
	//Attributes
		string id;	 			
		string username; 		
		string password;		
		string user_classification;
	public:
	//More attributes
		string first_name;
		string last_name;
		string sex;
		string date_of_birth;
	public:
	//Constructor
		User(string username) {
			Utility utilityTools;
			utilityTools.handlingDuplication("users_File.txt", 6);
			//will search through the map until the end of the map
			if(userDataMap.find(username) != userDataMap.end()) {			//if the username exist the constructor will initialize values into an object
				UserDetailsUsingMap userDetail = userDataMap[username];		//using the registered username and using the structure will take a particular username details
				this->username = username;
				this->password=userDetail.password;
				this->id=userDetail.id;
				this->first_name=userDetail.first_name;
				this->last_name=userDetail.last_name;
				this->sex=userDetail.sex;
				this->date_of_birth=userDetail.date_of_birth;
				string sub_string;				//sub string variable will used to extract the user's allocation in the management system
				string line = username;			//string line is equal to the username from the parameter, since it was true
				size_t underscore = line.find("_");			//finding an underscore in the string line 
				if(underscore != string::npos) {			//the underscore is surely found 
					sub_string=line.substr(0, underscore);			//now defining/intializing the sub string variable to the extracted part from the string line
				}
				this->user_classification=sub_string;          //used to easily use it in the code 
			} else {
				cout<<"Username doesn't exists in the database, thus we can't extract details."<<endl;
			}
		}		
			
	public:
	//Destructor (used when we delete the object after we use an object in a function, It will be used in local fuction and when the program executes)
		virtual ~ User() {}
	public:               
	//Handling setter and getters
		void setUsername(string username) {
			this->username = username;
		}
		string getUsername() {
			return username;
		}	
		void setId(string id) {
			this->id=id;
		}	
		string getId() {
			return id;
		}
		void setPassword(string password) {
			this->password = password;
		}
		string getPassword() {
			return password;
		}
		void setUserClassification(string user_classification) {
			this->user_classification = user_classification;
		}
		string getUserClassification() {
			return user_classification;
		}
	public:
		virtual bool view() {
			//view algorithm for user used to view all the users file in the management system, However its possible for the function to change complelety under other user's implementation
			for(auto pair : userDataMap) {
				cout
				<<"USERNAME: "<<pair.first<<endl
				<<"ID: "<<pair.second.id<<endl
				<<"FIRST_NAME: "<<pair.second.first_name<<endl
				<<"LAST_NAME: "<<pair.second.last_name<<endl
				<<"SEX: "<<pair.second.sex<<endl
				<<"DATE_OF_BIRTH: "<<pair.second.date_of_birth<<endl;
				cout<<endl;
			}
			if(userDataMap.empty() == 0) {
				if(userDataMap.size() == 1) {
					cout<<"You are the only registered user in these management system."<<endl;
				} else {
					cout<<"Those are all the user profile details in our management system."<<endl;
					cout<<"The total number is: "<<userDataMap.size()<<endl;
				} return true;
			} else {
				cout<<"The user details file is currently empty know please, inform the issue to the developers."<<endl;	
				return false;
			} return true;
		}
		
	public:
		virtual bool editDetails(string username) {
			//edit algorithm used for users to edit their password in the management system
			string new_password;   //variable storing the new password
			bool exists;
			cout<<endl;
			cout<<"To change your old password.";
			cout<<endl;
			cout<<"Please Enter New Password: ";
			cin>>new_password;
			cin.ignore();
			exists = ValidationCheck::validatePassword(password);   //validate the password
			if(exists) {
				if(new_password == this->password) {
					cout<<"You are using your recent password, its not exactly changing your password."<<endl;
				} else {
					DatabaseManager dbManager;
					exists = dbManager.searchForFirstAndSecondField("users_File.txt", this->username, this->password, 6);
					if(exists) {
						DatabaseManager::registerUser("temporarly_edit_table.txt", this->username, new_password,this->id,this->first_name, this->last_name, this->sex, this->date_of_birth);	
						DatabaseManager::deleteFileName(); //delete the user database
						DatabaseManager::renameFileName(); //rename the temporarly_edit_table to users_File
					} else {
						cout<<"The username is not found in the user database."<<endl;
					}
				}
			} else {
				cout<<"Error: the password is invalid."<<endl;
			}
			return true;
		} 
};

class Course {
	private:
	//Attribute
		string course_id;
	public:
	//Attribute
		string course_name;
		string course_year;
	public:
	//Constructor
		Course(string course_id) {
			Utility utilityTools;
			utilityTools.handlingDuplication("course_table_file.txt", 2);
			if(threeFieldsMap.find(course_id) != threeFieldsMap.end() ) {
				DetailsForTwoCommaInLineUsingMap detailsForThreeFields = threeFieldsMap[course_id];
				this->course_id=course_id;
				this->course_name=detailsForThreeFields.details_field2;
				this->course_year=detailsForThreeFields.details_field3;
			} else {
				cout<<"The course-ID doesn't is not save in the data structure map."<<endl;
			}	
		}
		~ Course() {}
	public:
	//Handling setters and getters
		void setCourseId(string course_id) {
			this->course_id=course_id;
		}
		string getCourseId() {
			return course_id;
		}			
};

class Student : public User {
	public:
	//Constructor
		Student(string username) 
		: User(username) {}
	public:
	//deconstructor 
		~Student() {}
	public:		
	//Overriding view in student
		bool view() override {	
			string student_classification;
			string course_id;
			string id;
			string course_name;	
			string details_field2;
			bool exists;
			DatabaseManager dbManager;
			Utility utilityTools;
			cout<<endl;
			cout<<"\t/1. Option to view all courses/"<<endl;
			cout<<"\t/2. Option to view your profile/"<<endl;
			cout<<"\t/3. Option to view your recent grade(s)/"<<endl;
			cout<<"\t/4. Option to view the program(s) you are enrolled into/"<<endl;
			cout<<"\t/5. Option to view other students that are learing from the same course/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			int choice;
			cin>>choice;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto pair : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<pair.first<<endl
					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"Thats the only course provided in our management system."<<endl;
					} else {
						cout<<"Those are the courses provided in our management system."<<endl;
						cout<<"The total is: "<<threeFieldsMap.size()<<endl;
					}
				} else {
					cout<<"The course details are not yet uploaded by the registrar/admin."<<endl;
				}
			} else if(choice == 2) {
				utilityTools.handlingDuplication("users_File.txt", 6);
				if(userDataMap.find(this->getUsername()) != userDataMap.end()) {   //fetch the line with the username
					UserDetailsUsingMap userDetails  = userDataMap[this->getUsername()];
					cout
					<<"USERNAME: "<<this->getUsername()<<endl
					<<"ID: "<<userDetails.id<<endl
					<<"FIRST_NAME: "<<userDetails.first_name<<endl
					<<"LAST_NAME: "<<userDetails.last_name<<endl
					<<"SEX: "<<userDetails.sex<<endl
					<<"DATE_OF_BIRTH: "<<userDetails.date_of_birth<<endl
					<<endl;
				} else {
					cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
				}
					//read my own profile
			} else if(choice == 3) {
				dbManager.searchForFirstAndSecondField("students_grade_details_table_file.txt", this->getId(), student_classification, 3);
				utilityTools.handlingDuplication("temporarly_table2.0.txt", 3);	//PLEASE VISIT THE DECLARATION IN searchForFirstAndSecondField FOR THE EXPLANATION OF THE temporarly_table2.0. file
				if(fourFieldsMap.empty() == 1) {
					cout<<"Your grades are not yet published by your teacher, just wait/call your teacher that your grade(s) are no yet published"<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temporarly_table2.0.txt", 3);
				}		
			} else if(choice == 4) {
				course_id = "EQUAL TO SOMETHING";
				dbManager.searchForFirstAndSecondField("students_enroll_course_table_file.txt", this->getId(), course_id, 1);
				utilityTools.handlingDuplication("temp_file_two.txt", 1);
				if(twoFieldsMap.empty() == 1) {
					cout<<"You have not yet enrolled into any course the management system offers."<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temp_file_two.txt", 1);
				}	
			} else if(choice == 5) {
				cout<<"Enter course-ID : "<<endl;
				cin>>course_id;
				cin.ignore();
				exists = ValidationCheck::validateCourseId(course_id);   //validate the course ID
				if(exists) {
					string details_field2;
					exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);   //check if the ID exists in the course table 
					if(exists) {
				//handling the studnets with the same course, so that the student can view his or her classmates		
						exists = DatabaseManager::authenticateUserInFileManagementSystem(this->getId(), course_id, "students_enroll_course_table_file.txt", 1);
						if(exists) {
							id = "EQUAL TO SOMETHING";
							dbManager.searchForFirstAndSecondField("students_enroll_course_table_file.txt", id, course_id, 1);
							ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temp_file_one.txt", 1);	
						} else {
							cout<<"You don't learn from the course, so you can't view other class members."<<endl;
						}	
					} else {
						cout<<"The course-ID is not found in the course details file."<<endl;
					}
				} else {
					cout<<"Error: the course-ID is invalid."<<endl;
				}
			} else {
				cout<<"Error: Invalid choice Option."<<endl;
			}
			return true;
		}
	public:
	//Making the student's enroll database when the student's enrolls into a program
		bool makeStudentsEnrollCourseTable(string course_id) {
			bool exists;
			Utility utilityTools;
			DatabaseManager dbManager;
			exists = ValidationCheck::validateCourseId(course_id);   
			//Validate the course ID
			if(exists) {
				cout<<endl;
				string course_name;
				exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
				//Check if the course ID exists in the database when the student enters the course ID in function navigate login menu
				if(exists) {
					ofstream outFile("students_enroll_course_table_file.txt", ios_base::app);
					utilityTools.handlingDuplication("students_enroll_course_table_file.txt", 1);
					//Check the student ID and course ID if they are already enrollled into a the student's enroll course table
					if(twoFieldsMap.find(this->getId()) != twoFieldsMap.end() && twoFieldsMap[this->getId()].details_field2 == course_id) {
						cout<<"You are already enrolled to the program "<<course_id<<endl;
					} else {
						ofstream outFile("students_enroll_course_table_file.txt", ios_base::app);
						if(!outFile.is_open()) {
							cerr<<"Error: Unable to open the file."<<endl;
						} else {
							Course program(course_id);
							cout
							<<"COURSE-ID: "<<program.getCourseId()<<endl
							<<"COURSE_NAME: "<<program.course_name<<endl
							<<"COURSE_YEAR: "<<program.course_year<<endl;	
							outFile<<this->getId()<<","<<course_id<<endl;
							cout<<"You have successfully enrolled/registered into a program in our management system."<<endl;
							return true;
						}
					}	
				} else {
					cout<<"The course-ID is not found in the course file."<<endl;
				} 
			} else {
				cout<<"Error: the course-ID is invalid."<<endl;
			} return true;
		} 
};

class Employee {
	public:
	//Search for a student in the management system and the string id is the making a search algorithm
	//After the admin Enter a student ID we are able to view if that id exists
		void searchForUser(string username) {
			Utility utilityTools;
			utilityTools.handlingDuplication("users_File.txt", 6);
			if(userDataMap.find(username) != userDataMap.end()) {
				cout<<"Username exists in the user database file."<<endl;
			} else {
				cout<<"Username doesn't exists in user database file."<<endl;
			}
		}
	protected:
	/*View fuction for all the employees working in the office 
	will view the student's details in our management system*/
		bool employeeView() {;
			Utility utilityTools;
			int choice;
			cout<<endl;
			cout<<"\t/1. Option to view students entry details/"<<endl;
			cout<<"\t/2. Option to view students grade details/"<<endl;
			cout<<"\t/3. Option to view students enroll course details/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			cin>>choice;
			bool exists;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				ofstream IfFileIsNotYetMade("students_entry_details_file.txt", ios_base::app);
				utilityTools.handlingDuplication("students_entry_details_file.txt", 2);	
				for(auto pair : threeFieldsMap) {
					cout
					<<"USER-ID: "<<pair.first<<endl
					<<"STUDENT_CLASSIFICATION: "<<pair.second.details_field2<<endl
					<<"YEAR_OF_REGISTRATION: "<<pair.second.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"that's the only student in our management system."<<endl;
					} else {
						cout<<"Those are all the students in our management system."<<endl;
						cout<<"The total number is: "<<threeFieldsMap.size()<<endl;
					}
				} else {
					cout<<"The students have not yet beign registered by the registrar/admin."<<endl;
				}
			} else if(choice == 2) {
				ofstream IfFileIsNotYetMade("students_grade_details_table_file.txt", ios_base::app);
				utilityTools.handlingDuplication("students_grade_details_table_file.txt", 3);
				if(fourFieldsMap.empty() == 1) {  //not empty
					cout<<"The students grade details have not yet being published by the teacher."<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("students_grade_details_table_file.txt", 3);
				}
			} else if(choice == 3) {
				ofstream IfFileIsNotYetMade("students_enroll_course_table_file.txt", ios_base::app);
				utilityTools.handlingDuplication("students_enroll_course_table_file.txt", 1);
				if(twoFieldsMap.empty() == 1) {
					cout<<"The students in our management system have not yet enrolled into a course/program."<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("students_enroll_course_table_file.txt", 1);	
				}
				
			} else {
				cout<<"Error: Invalid view Option."<<endl;
			}
			return true;
		}
	
}; 

class Teacher: public User, public Employee {
	private:
	//Attribute
		float gpa;
	public:
	//Constructor
		Teacher(string username) 
		: User(username), 
		Employee(){}
	public:
	//Handling setters and getters
		void setGpa(float gpa) {
			this->gpa=gpa;
		}
		float getGpa() {
			return gpa;
		}
	public:	
		bool readStudentsEnrolledToACourse(string course_id) {
			ofstream IfFileIsNotYetMade("students_enroll_course_table_file.txt", ios_base::app);
			bool exists;
			string id;
			string course_name;
			Utility utilityTools;
			DatabaseManager dbManager;
			exists = ValidationCheck::validateCourseId(course_id);
			//Validate the course ID
			if(exists) {
				exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
				//Check if the course table has the entered course ID
				if(exists) {
					exists = DatabaseManager::authenticateUserInFileManagementSystem(this->getId(), course_id, "teachers_table_file.txt", 1);
					if(exists) {
						id = "EQUAL TO SOMETHING";
						dbManager.searchForFirstAndSecondField("students_enroll_course_table_file.txt", id, course_id, 1);
						utilityTools.handlingDuplication("temp_file_one.txt", 1);
						if(twoFieldsMap.empty() == 1) {
							cout<<"No student learns from your course-ID."<<endl;
							return false;
						} else {
							ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temp_file_one.txt", 1);
							return true;
						}
					} else {
						cout<<"you don't teach that course in our management system."<<endl;
					}
				} else {
					cout<<"the course ID  is not found in the course table file."<<endl;
				}
			} else {
				cout<<"The course ID  is invalid."<<endl;
			} return false;
		} 
		
	public:
	//Overriding view function in teacher
		bool view() override {  
			bool exists;
			Utility utilityTools;
			int choice;
			cout<<endl;
			cout<<"\t/1. Option to view all courses/"<<endl;
			cout<<"\t/2. Option to view your profile/"<<endl;
			cout<<"\t/3. Option to view the students who are learning your program/"<<endl;
			cout<<"\t/4. Option to view student information categories within this system/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			if(choice == 1) {
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto pair : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<pair.first<<endl
					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"that is the only course provided into the management system."<<endl;
					} else {
						cout<<"thats all the courses provided into the management system."<<endl;
						cout<<"That total is: "<<threeFieldsMap.size()<<endl;
					}
				} else {
					cout<<"The course are not yet registered/made by the admin."<<endl;
				}		
			} else if(choice == 2) {
				utilityTools.handlingDuplication("users_File.txt", 6);
				if(userDataMap.find(this->getUsername()) != userDataMap.end()) {
					UserDetailsUsingMap userDetails = userDataMap[this->getUsername()];
					cout
					<<"USERNAME: "<<this->getUsername()<<endl
					<<"ID: "<<userDetails.id<<endl
					<<"FIRST_NAME: "<<userDetails.first_name<<endl
					<<"LAST_NAME: "<<userDetails.last_name<<endl
					<<"SEX: "<<userDetails.sex<<endl
					<<"DATE_OF_BIRTH: "<<userDetails.date_of_birth<<endl
					<<endl;
					cout<<"That is your profile in our management system."<<endl;
				} else {
					cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
				}
			} else if(choice == 3) {
				string course_id;
				cout<<"Enter the course-ID of the program(s) that you teach: ";
				cin>>course_id;
				cin.ignore();
				this->readStudentsEnrolledToACourse(course_id);
			} else if(choice == 4) {
				this->employeeView();
			}  else { 
				cout<<"Error: Invalid view Option."<<endl;;
			} return true;
		}
	public:
	//make the student's grade table after the exams are done with marking
		bool makeStudentsGradeTable() {
			ofstream outFile("students_grade_details_table_file.txt", ios_base::app);
			string username;
			string password;
			string course_id;
			string course_name;
			string student_classification;
			string gpa;
			bool exists;
			Utility utilityTools;
			DatabaseManager dbManager;
			cout<<"Enter course-ID of the program(s) that you teach: ";
			cin>>course_id;
			cin.ignore();
			string details_field2;
			exists = this->readStudentsEnrolledToACourse(course_id);
			if(exists) {
				string entered_username;
				//these must be together for the student, so that we could use the getter for the ID
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				exists = ValidationCheck::validateId(username);
				if(exists) {
					string details_field2;
					exists = dbManager.searchForFirstAndSecondField("users_File.txt", username, password, 6);
					if(exists) {
						Student student(username);
						exists = DatabaseManager::authenticateUserInFileManagementSystem(student.getId(), course_id, "students_enroll_course_table_file.txt", 1);
						if(exists) {
							cout<<"Enter classification/class: ";
							getline(cin>>ws, student_classification);
							exists = ValidationCheck::validateStudentClassification(student_classification);
							if(exists) {
								utilityTools.handlingDuplication("students_entry_details_file.txt", 2);
								if(threeFieldsMap.find(student.getId()) != threeFieldsMap.end() && threeFieldsMap[student.getId()].details_field2 == student_classification) {	
									exists = DatabaseManager::authenticateUserInFileManagementSystem(student.getId(), course_id, "students_grade_details_table_file.txt", 3);
									if(exists) {
										cout<<"The students grade details for the ID and the course the student learns have already beign published into the students grade details file.."<<endl;
									} else {
										cout<<"Enter grade: ";
										cin>>gpa;
										cin.ignore();
										exists = ValidationCheck::validateGpa(gpa);
										if(exists) {
											if(!outFile.is_open()) {
												cerr<<"Error: Unable to open the students grade details file."<<endl;
											} else {				
												outFile<<student.getId()<<","<<student_classification<<","<<course_id<<","<<gpa<<endl;	
												cout<<"You have successfully published the students grade in our management system."<<endl;
											}
										} else {
											cout<<"Error: the grade is invalid."<<endl;
										}
									}
								} else {
									cout<<"The student classification is not the same as the students details in the students entry details file"<<endl;
								}
							} else {
								cout<<"Error: the student classification is invalid."<<endl;
							}
						} else {
							cout<<"These student doesn't take your course in our management system."<<endl;
						}
					} else {
						cout<<"The student username doesn't exists in the user's file file."<<endl;
					} 
				} else {
					cout<<"Error: The username is invalid."<<endl;		
				}
			} else {
				cout<<"THE ERROR MESSAGE ABOVE EXPLAINS AN ISSUE, PLEASE MAKE AN FOLLOW THE CORRECT PROCEDURE OF UPLOADING GRADES."<<endl;
			} return true;
		}
};

class Admin : public User, public Employee {
	public:
	//Attribute
		string student_classification;
	public :
	//Constructor
		Admin(string username)
		: User(username),
		Employee() {}
	public: 
		bool registration() {
			//Handling registration fuction in admin
			string username;
			string password;
			string id;
			string first_name;
			string last_name;
			string sex;
			string date_of_birth;
			string course_id;
			string course_name;
			string course_year;
			string gpa;
			string year_of_entry;
			int choice;	
			bool exists;
			DatabaseManager dbManager;
			cout<<endl;
			cout<<"\t/1. Register course/"<<endl;
			cout<<"\t/2. Register teacher/"<<endl;
			cout<<"\t/3. Register student/"<<endl;
			cout<<endl;  
			cout<<"Enter the choice Option: ";
			cin>>choice;
			Utility utilityTools;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				cout<<"Enter course-ID: ";
				cin>>course_id;
				cin.ignore();
				exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);   
				//Check if the course ID Entered is already registered
				if(exists) {
					cout<<"Error: The course-ID already exists in the file."<<endl;
				} else {
					exists = ValidationCheck::validateCourseId(course_id);   
					//Validate the course ID Entered
					if(exists) {
						cout<<"Enter course name: ";
						cin>>course_name;
						cin.ignore();
						exists = ValidationCheck::validateCourseName(course_name);   
						//Validate the course name Entered
						if(exists) {
							cout<<"Enter course year: ";
							cin>>course_year;
							cin.ignore();
							exists = ValidationCheck::validateYear(course_year);   
							//Validate the course year Entered
							if(exists) {
								ofstream outFile("course_table_file.txt", ios_base::app);
								if(!outFile.is_open()) {
									cerr<<"Error: File is not found."<<endl;
								} else {
									outFile<<course_id<<","<<course_name<<","<<course_year<<endl;
									cout<<"Registration of the course was completed successfully."<<endl;
								}
							} else {
								cout<<"Error: the course year is invalid."<<endl;
							}
						} else {
							cout<<"Error: the course name is invalid."<<endl;
						}
					} else {
						cout<<"Error: the course ID is invalid"<<endl;
					}
				}
			} else if(choice == 2) {
				cout<<endl;
				cout<<"1. Use to Register a New Teacher?"<<endl;
				cout<<"2. Use to Add a New course to an Existing Teacher?"<<endl;
				cout<<endl;
				cout<<"Enter your option: ";
				cin>>choice;
				cin.ignore();
				system("CLS");
				cout<<endl;
				if(choice == 1) {
					cout<<"Enter username: ";
					cin>>username;
					cin.ignore();
					exists = ValidationCheck::validateUsername(username);
					if(exists) {
						exists = dbManager.searchForFirstAndSecondField("users_File.txt", username, password, 6);
						if(exists) {
							cout<<"The username already exists in the user's database, inorder to register to new course please go to 'register to new course'."<<endl;
						} else {
							cout<<"Enter Default Password: ";
							cin>>password;
							cin.ignore();
							exists = ValidationCheck::validatePassword(password);
							if(exists) {
								cout<<"Enter ID: ";
								cin>>id;
								cin.ignore();
								string details_field2;
								exists = ValidationCheck::validateId(id);
								if(exists) {
									course_id = "EQUAL TO SOMETHING";
									exists = dbManager.searchForFirstAndSecondField("teachers_table_file.txt", id, course_id, 1);
									if(exists) {
										cout<<"The teachers-ID belongs to another teacher in the teachers table file."<<endl;
									} else {
										cout<<"Enter First Name: ";
										cin>>first_name;
										cin.ignore();
										exists = ValidationCheck::validateFirstName(first_name);
										if(exists) {
											cout<<"Enter Last Name: ";
											cin>>last_name;
											cin.ignore();
											exists = ValidationCheck::validateLastName(last_name);
											if(exists) {	
												cout<<"Enter gender: ";
												cin>>sex;
												cin.ignore();
												exists = ValidationCheck::validateGender(sex);
												if(exists) {
													cout<<"Enter Date-Of-Birth: ";
													cin>>date_of_birth;
													cin.ignore();
													exists = ValidationCheck::validateDOB(date_of_birth);
													if(exists) {	
													cout<<endl;
													utilityTools.handlingDuplication("course_table_file.txt", 2);
													for(auto pair : threeFieldsMap) {
														cout
														<<"COURSE-ID: "<<pair.first<<endl
														<<"COURSE_NAME: "<<pair.second.details_field2<<endl
														<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
														<<endl;
													}
													cout<<endl;
													cout<<"Enter course-ID: ";
													cin>>course_id;
													cin.ignore();
													exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
													//if condition checking the entered course-ID is existing in the course table file 
													if(exists) {
														string temp_id = "EQUAL TO SOMETHING";
														exists = dbManager.searchForFirstAndSecondField("teachers_table_file.txt", temp_id, course_id, 1);
														if(exists) { //IF THE 
															cout<<"You can't register these teacher to the same course as an existing teacher."<<endl;
														} else {
															ofstream outFile("teachers_table_file.txt", ios_base::app);
															if(!outFile.is_open()) {
																cerr<<"Error: Unable to open the users file, inorder save the new entry details into the users fileDatabaseManager"<<endl;
															} else {
																DatabaseManager::registerUser("users_File.txt", username, password, id, first_name, last_name, sex, date_of_birth);
																outFile<<id<<","<<course_id<<endl;
																cout<<"Registration of the new teacher in both user's database and teachers table file completed successfully."<<endl;
															}
														}
													} else {
														cout<<"The Course-ID does't exists in the course file table."<<endl;
													}
												} else {
													cout<<"Error: The date of birth is invalid."<<endl;
												}	
											} else {
												cout<<"Error: The gender is invalid."<<endl;
											}
										} else {
											cout<<"Error: The Last Name is invalid."<<endl;
										}	
									} else {
										cout<<"Error: The First Name is invalid."<<endl;
									}
								} 
							} else {
								cout<<"Error: The Identification Number is invalid."<<endl;
							}
						}  else {
							cout<<"Error: The Password is invalid."<<endl;
						}
					}
				} else {
					cout<<"Error:The Username is invalid."<<endl;
				}
			} else if(choice == 2) {
				cout<<endl;
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto pair : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<pair.first<<endl
					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
					<<endl;
				}
				cout<<endl;
				//displaying the course table file so that would have a chance of viewing details while registration
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				string details_field2;
				exists = ValidationCheck::validateUsername(username);
				if(exists) {
					exists = dbManager.searchForFirstAndSecondField("users_File.txt", username, password, 6);
					if(exists) {
						Teacher teacher(username);
						cout<<"Enter course-ID: ";
						cin>>course_id;
						cin.ignore();
						string details_field2;
						exists = ValidationCheck::validateCourseId(course_id);
							if(exists) {
								exists = dbManager.searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2); 
								if(exists) {
									exists = DatabaseManager::authenticateUserInFileManagementSystem(teacher.getId(), course_id, "teachers_table_file.txt", 1);
									if(exists) {
										cout<<"the teacher is already registered to that course in our management system."<<endl;
									} else {
										id = "EQUAL TO SOMETHING";
										exists = dbManager.searchForFirstAndSecondField("teachers_table_file.txt", id, course_id, 1);
										if(exists) {
											cout<<"You can't register these teacher to the same course as an existing teacher."<<endl;
										} else {
											ofstream outFile("teachers_table_file.txt", ios_base::app);
											if(!outFile.is_open()) {
												cerr<<"Error: Unable to open the teachers file, inorder to save the new entry details into the teachers details table."<<endl;
											} else {
												Teacher teacher(username);
												outFile<<teacher.getId()<<","<<course_id<<endl;
												cout<<"Registration of existing teacher to the new course in the teachers table file is completed successfully."<<endl;
											}	
										}
									}	
								} else {
									cout<<"the course-ID is not found in the course file."<<endl;
								}
							} else {
								cout<<"Error: The Course-ID is invalid."<<endl;
							}	
						} else {
							cout<<"The username is not found in the user file, 'perharps try to register a new teacher'"<<endl;
						}
					} else {
						cout<<"Error: The Username is invalid."<<endl;
					}
				} else {
					cout<<"Invalid choice option."<<endl;
				}
			} else if(choice == 3) {
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				exists = ValidationCheck::validateUsername(username);
				if(exists) {
					exists = dbManager.searchForFirstAndSecondField("users_File.txt", username, password, 6);
					if(exists) {
						cout<<"The username in the user's file already is registered into the school management system."<<endl;
					} else {
						cout<<"Enter Default Password: ";
						cin>>password;
						cin.ignore();
						exists = ValidationCheck::validatePassword(password);
						if(exists) {
							cout<<"Enter ID: ";
							cin>>id;
							cin.ignore();
							exists = ValidationCheck::validateId(id);
							if(exists) {
								exists = dbManager.searchForFirstAndSecondField("students_entry_details_file.txt", id, student_classification, 2);
								if(exists) {
									cout<<"The students-ID belongs to another student in the student entry details file."<<endl;
								} else {
									cout<<"Enter First Name: ";
									cin>>first_name;
									cin.ignore();
									exists = ValidationCheck::validateFirstName(first_name);
									if(exists) {
										cout<<"Enter Last Name: ";
										cin>>last_name;
										cin.ignore();
										exists = ValidationCheck::validateLastName(last_name);
										if(exists) {
											cout<<"Enter gender: ";
											cin>>sex;
											cin.ignore();
											exists = ValidationCheck::validateGender(sex);
												if(exists) {
													cout<<"Enter Date-Of-Birth: ";
													cin>>date_of_birth;
													cin.ignore();
													exists = ValidationCheck::validateDOB(date_of_birth);
													if(exists) {
														cout<<"Enter the year of entry: ";
														cin>>year_of_entry;
														cin.ignore();
														exists = ValidationCheck::validateYear(year_of_entry);
														if(exists) {
															cout<<"Enter student classification/class: ";
															getline(cin>>ws, student_classification);
															exists = ValidationCheck::validateStudentClassification(student_classification);
															if(exists) {
																ofstream outFile("students_entry_details_file.txt", ios_base::app);
																if(!outFile.is_open()) {
																	cerr<<"Error: Unable to open the student entry details file, inorder to keep track of the students resoursfully details"<<endl;
																} else {
																	outFile<<id<<","<<student_classification<<","<<year_of_entry<<endl;
																	DatabaseManager::registerUser("users_File.txt", username, password, id, first_name, last_name, sex, date_of_birth);
																	cout<<"Registration of the student in the student entry details file is completed successfully."<<endl;
																}
															} else {
																cout<<"Error: The student classification/class is invalid."<<endl;
															}
														} else {
															cout<<"Error: The students year of entry is invalid."<<endl;
														}
													} else {
														cout<<"Error: The Data Of Birth is invalid."<<endl;
													}
												} else {
													cout<<"Error: The Gender is invalid."<<endl;
												}
											} else {
												cout<<"Error: The Last Name is invalid."<<endl;
											}
										} else {
											cout<<"Error: The First Name is invalid."<<endl;
										}	
									} 
								} else {
									cout<<"Error: The Identification Number is invalid."<<endl;
								}
							} else {
								cout<<"Error: The Password is invalid."<<endl;
							}
						} 
					} else {
						cout<<"Error: The Username is invalid."<<endl;
					}
				} else {
					cout<<"Error: Invalid choice Option."<<endl;
				}
			return true;
		}
	public:	
		bool view() override {
			//Overriding view function in the admin	
			bool exists;
			int choice;
			cout<<endl;
			cout<<"\t/1. Option to view all users/"<<endl;
			cout<<"\t/2. Option to view all courses/"<<endl;
			cout<<"\t/3. Option to view your profile/"<<endl;
			cout<<"\t/4. Option to view all teachers/"<<endl;
			cout<<"\t/5. Option to view student information categories within this system/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			cin>>choice;
			Utility utilityTools;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				utilityTools.handlingDuplication("users_File.txt", 6);
				User::view();
			} else if(choice == 2) {
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto pair : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<pair.first<<endl
					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"That is the only course that you registered in the management system."<<endl;
					} else {
						cout<<"Those are all the courses in the management system."<<endl;
						cout<<"The total is: "<<threeFieldsMap.size()<<endl;
					}
				} else {
					cout<<"The admin/registrar has not yet registered course file table in the management system."<<endl;
				}
			} else if(choice == 3) {
				utilityTools.handlingDuplication("users_File.txt", 6);
				if(userDataMap.find(this->getUsername()) != userDataMap.end()) {
					UserDetailsUsingMap userDetails = userDataMap[this->getUsername()];
					cout
					<<"USERNAME: "<<this->getUsername()<<endl
					<<"ID: "<<userDetails.id<<endl
					<<"FIRST_NAME: "<<userDetails.first_name<<endl
					<<"LAST_NAME: "<<userDetails.last_name<<endl
					<<"GENDER: "<<userDetails.sex<<endl
					<<"DATE_OF_BIRTH: "<<userDetails.date_of_birth<<endl
					<<endl;
					
				} else {
					cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
				}
				//read my own profile	
			} else if(choice == 4) {
				int choice;
				cout<<"1. Option to view how many teachers are in the management system."<<endl;
				cout<<"2. Option to view the teachers and the course they teach."<<endl;
				cout<<endl;
				cout<<"Enter the view option: ";
				cin>>choice;
				cin.ignore();
				system("CLS");
				cout<<endl;
				switch(choice) {
					case 1: {
						utilityTools.handlingDuplication("teachers_table_file.txt", 1);
						for(auto pair : twoFieldsMap) {
							cout<<"USER-ID: "<<pair.first<<endl;
						}	
						if(twoFieldsMap.empty() == 0) {
							if(twoFieldsMap.size() == 1) {
								cout<<"Thats the only teacher that you registered in the management system."<<endl;
							} else {
								cout<<"Those are all the teachers in the management system."<<endl;
								cout<<"The total is: "<<twoFieldsMap.size()<<endl;
							}
						} else {
							cout<<"The admin/registrar has not yet registered the teachers table file in the management system."<<endl;
						}	
						break;
					} 
					case 2: {
						ReadFileThatAreExtractingASingleUserDetails::readFromAFile("teachers_table_file.txt", 1);
						break;
					}
					default: {
						cout<<"Error: invalid view option."<<endl;
						break;
					}
				}
	
			} else if(choice == 5) {
				this->employeeView();
			} else {
				cout<<"Error: Invalid view Option"<<endl;
			}
			return true;
		}
	public:

		bool editDetails(string username) override {
			//Overriding edit fuction in the admin 
			string password;
			string new_first_name;
			string new_last_name;
			bool exists;
			int choice;
			DatabaseManager dbManager;
			cout<<"Enter username: ";
			cin>>username;
			cin.ignore();
			exists = ValidationCheck::validateUsername(username);     
			//Validate the username
			if(exists) {
				exists = dbManager.searchForFirstAndSecondField("users_File.txt", username, password, 6);
				if(exists) {
					User user(username);
					if(userDataMap.find(username) != userDataMap.end()) {
						cout<<endl;
						cout<<"\t/1. Option edit First Name/"<<endl;
						cout<<"\t/2. Option edit Last Name/"<<endl;
						cout<<"\t/3. Option edit All the above details/"<<endl;
						cout<<endl;
						cout<<"Enter the edit Option: ";
						cin>>choice;
						cin.ignore();
						system("CLS");
						if(choice == 1) {
							cout<<"Enter New First Name: ";
							cin>>new_first_name;
							cin.ignore();
							exists = ValidationCheck::validateFirstName(new_first_name);    
							if(exists) {
								DatabaseManager::registerUser("temporarly_edit_table.txt", username, user.getPassword(), 
								user.getId(), new_first_name, user.last_name, user.sex, user.date_of_birth);
								DatabaseManager::deleteFileName();      
								DatabaseManager::renameFileName();      
							} else {
								cout<<"Error: the first name is invalid."<<endl;
							}
						} else if(choice == 2) {
							cout<<"Enter New Last Name: ";
							cin>>new_last_name;
							cin.ignore();
								exists = ValidationCheck::validateLastName(new_last_name);    
								if(exists) {
									DatabaseManager::registerUser("temporarly_edit_table.txt", username, user.getPassword(), 
									user.getId(), user.first_name, new_last_name, user.sex, user.date_of_birth);
									DatabaseManager::deleteFileName();      
									DatabaseManager::renameFileName();      
								} else {
									cout<<"Error: the last name is invalid."<<endl;	
								}
						} else if(choice == 3) {
							cout<<"Enter New First Name: ";
							cin>>new_first_name;
							cin.ignore();
							exists = ValidationCheck::validateFirstName(new_first_name);     
							if(exists) {
								cout<<"Enter New Last Name: ";
								cin>>new_last_name;
								cin.ignore();
								exists = ValidationCheck::validateLastName(new_last_name);     
								if(exists) {
									DatabaseManager::registerUser("temporarly_edit_table.txt", username, user.getPassword(), 
									user.getId(), new_first_name, new_last_name, user.sex, user.date_of_birth);
									DatabaseManager::deleteFileName();     
									DatabaseManager::renameFileName();     
								} else {
									cout<<"Error: the last name is invalid."<<endl;
								}
							} else {
								cout<<"Error: the first name is invalid."<<endl;
							}
						} else {
							cout<<"Error: Invalid edit Option."<<endl;
						}
					}
				} else {
					cout<<"The username doesn't exits in the user file"<<endl;
				}
			} else {
				cout<<"Error: the username is invalid."<<endl;
			}
			return true;		
		}	
};

//Function handling the users allocation the aim is after logged in by the system during runtime they will have their own menu.
bool allocateUserLoginClassification(string username) {
	string course_id;
	bool exists;
	int choice;
	User user(username);
		cout<<endl;
		if(user.getUserClassification() == "student") {
			Student student(username);
			cout<<"\t/1. Option to enroll into a course/"<<endl;
			cout<<"\t/2. Option to view details/"<<endl;
			cout<<"\t/3. Option to edit password/"<<endl;
			cout<<endl;
			cout<<"Enter your Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			if(choice == 1) {			
				Utility utilityTools;
				cout<<"Here is the course details we offer in our schools management system."<<endl<<endl;
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto pair : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<pair.first<<endl
					<<"COURSE_NAME: "<<pair.second.details_field2<<endl
					<<"COURSE_YEAR: "<<pair.second.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					cout<<endl;
					cout<<"Enter course-ID: ";
					cin>>course_id;
					cin.ignore();
					Course program(course_id);
					exists = student.makeStudentsEnrollCourseTable(course_id);	
				} else {
					cout<<"You can't enroll into a course because the file containing the course/programm is not yet registered/made by the admin/register in the management system."<<endl;
				}
			} else if(choice == 2) {
				Student *ptr = &student;
				ptr->view();
			} else if(choice == 3) {
				student.editDetails(student.getUsername());
			} else {
				cout<<"Error: Invalid choice Option."<<endl;
			}
		} else if(user.getUserClassification() == "teacher") {
			Teacher teacher(username);
			cout<<"\t/1. Option to upload grades/"<<endl;
			cout<<"\t/2. Option to view details/"<<endl;
			cout<<"\t/3. Option to edit password/"<<endl;
			cout<<endl;
			cout<<"Enter your Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			if(choice == 1) {
				teacher.makeStudentsGradeTable();
			} else if(choice == 2) {
				Teacher *ptr = &teacher;
				ptr->view();
			} else if(choice == 3) {	
				teacher.editDetails(teacher.getUsername());
			} else {
				cout<<"Error: Invalid choice of Option."<<endl;
			}
		} else if(user.getUserClassification() == "Admin") {
			Admin admin(username);
			cout<<"\t/1. Option used for registration of new details in files/"<<endl;
			cout<<"\t/2. Option to view details/"<<endl;
			cout<<"\t/3. Option to edit user details/"<<endl;
			cout<<"\t/4. Option to search for the username in the user's file/"<<endl;
			cout<<endl;
			cout<<"Enter your Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			if(choice == 1) {
				admin.registration();			
			} else if(choice == 2) {
				Admin *ptr1 = &admin;
				ptr1->view();
			} else if(choice == 3) {
				Admin *ptr2 = &admin;
				ptr2->editDetails(username);
			} else if(choice == 4){
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				admin.searchForUser(username);	
			} else {
				cout<<"Error: Invalid choice option."<<endl;
			}
		} else {
			cout<<"You are not classified/group into any user classification in our management system, please inform the registrar to fix the issue."<<endl;
		} return true;
}

//Fuction handling the login in our management system
int handlingLogin() {
	const char* FileName = "temp_file_two.txt";
	if(remove(FileName) == 0) {
	//	cout<<"the temp_file_two has successfully beign deleted."<<endl;
	} else {
	//	perror("Error: the temp_file_two failed to delete from our files.");
	}
	
	const char* otherFileName = "temp_file_one.txt";
	if(remove(otherFileName) == 0) {
	//	cout<<"the temp_file_one has successfully biegn deleted."<<endl;
	} else {
	//	perror("Error: the temp_file_one failed to delete from our files.");
	}
	string username;
	string password;
	bool exists;
	cout<<"\t\t\t\t\t\t\t\t\tHIE WELCOME TO THE LOGIN PAGE"<<endl;
	cout<<"To login"<<endl;
	cout<<"Please Enter your username: ";
	cin>>username;
	cin.ignore();
	exists = ValidationCheck::validateUsername(username);
	if(exists) {
		cout<<"Please Enter your password: ";	
		cin>>password;
		cin.ignore();
		system("CLS");
		DatabaseManager dbManager;
		exists = ValidationCheck::validatePassword(password);
		if(exists) {
			bool check;
			check = dbManager.authenticateUserInFileManagementSystem(username, password, "users_File.txt", 6);
			if(check) {
				//if logged in these fuction will handle their menu on regards to what their logged in as
				User user(username);
				cout<<"HIE USER "<<user.getId()<<" BY THE NAMES OF: "<<user.first_name<<" "<<user.last_name<<" TO THE FREE LEARNINGS MANAGEMENT SYSTEM"<<endl; 
				allocateUserLoginClassification(username);
			} else {
				//User failed to authenticate the account			
				cout<<"Our records don't have these credentials stored in the file."<<endl;
			}
		} else {
			cout<<"Error: the password is invalid."<<endl;
		}
	} else {
		cout<<"Error: the username is invalid."<<endl;
	} return 0;
}

//int main() function will handle a case when the files are not yet made on a server: else take them to the logging page 
int main() {
	const string admin_username = "Admin_User1";		//const admin username is used when to check if the system is still running on a server with the Admin_User 1 
	DatabaseManager dbManager;
	bool exists;
	string password = "EQUAL TO SOMETHING";
	exists = dbManager.searchForFirstAndSecondField("admin_table_file.txt", admin_username, password, 1);		//Check in the admin table if the constant variable exists 
	if(exists) {     
		//if its true call the handlingLogin() fuction
		handlingLogin();
	} else {        
		//if else then register an admin in the admin table as well as the user's file	
		string username;
		string password;
		string id;
		string first_name;
		string last_name;
		string sex;
		string date_of_birth;
		cout<<"Before you could go to login, please ensure the admin is registered in the user's file and the admins file"<<endl;
		cout<<"Please ensure that the username you enter is: 'Admin_User1'"<<endl;
		cout<<"Enter Username: ";
		cin>>username;
		cin.ignore();
		exists = ValidationCheck::validateUsername(username);	
		//Validate the username			
		if(exists) {
			if(username == admin_username) {
				cout<<"Enter Password: ";
				cin>>password;
				cin.ignore();
				exists = ValidationCheck::validatePassword(password);
				//Validate the password
				if(exists) {
					cout<<"Enter admin-ID: ";
					cin>>id;
					cin.ignore();
					exists = ValidationCheck::validateId(id);
					//Validate the ID
					if(exists) {
						cout<<"Enter First Name: ";
						cin>>first_name;
						cin.ignore();
						exists = ValidationCheck::validateFirstName(first_name);
						//Validate the first name
						if(exists) {
							cout<<"Enter Last Name: ";
							cin>>last_name;	
							cin.ignore();
							exists = ValidationCheck::validateLastName(last_name);
							//Validate the last name
							if(exists) {
								cout<<"Enter Gender: ";
								cin>>sex;		
								cin.ignore();			
								exists = ValidationCheck::validateGender(sex);
								//Validate the gender
								if(exists) {
									cout<<"Enter Date-Of_Birth: ";
									cin>>date_of_birth;
									cin.ignore();
									exists = ValidationCheck::validateDOB(date_of_birth);
									//Validate the date of birth
									if(exists) {
										DatabaseManager::registerUser("users_File.txt", username, password, id, first_name, last_name, sex, date_of_birth);
										ofstream outFile("admin_table_file.txt", ios::app);
										if(!outFile.is_open()) {
											cerr<<"Error: Unable to open the admin table file."<<endl;
										} else {
											outFile<<username<<","<<id<<endl;
											cout<<"The right details have being saved in admin table file is saved."<<endl;
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