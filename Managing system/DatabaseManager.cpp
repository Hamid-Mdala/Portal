#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

struct UserDetailsUsingMap {					//is used for the user's details file
	// the key is string username;
	string details_field2;
	string details_field3;
	string details_field4;
	string details_field5;
	string details_field6;
	string details_field7;
}; map<const string, UserDetailsUsingMap> userDataMap;

struct DetailsForOneCommaInLineUsingMap {		//is used for the students enroll course file, and the teachers course table file
	// the key is string details_field1;
	string details_field2;
}; map<const string, DetailsForOneCommaInLineUsingMap> twoFieldsMap;

struct DetailsForTwoCommaInLineUsingMap {		//is used for the students entry form file, and the course table file
	// the key is string details_field1;
	string details_field2;
	string details_field3;
}; map<const string, DetailsForTwoCommaInLineUsingMap> threeFieldsMap;

struct DetailsForThreeCommaInLineUsingMap {		//is used for the students grade file
	// the key is string details_field1
	string details_field2;
	string details_field3;
	string details_field4;
}; map<const string, DetailsForThreeCommaInLineUsingMap> fourFieldsMap;

class Utility {
	public:
		string single_line_from_temp;
		char del = ',';
	private:
		static int counting_fields;
	public:
		void setCount(int count) {
			this->counting_fields = count;
		}
		int getCountedFields() {
			return counting_fields;
		}
	public:
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
					this->counting_fields = comma_counts_in_line;
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
				if(this->counting_fields == num_of_fields_in_line) {
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
	static bool authenticateUserInFileManagementSystem(string details_field1, string details_other_fields, string filename, int num_of_fields_on_line) {
			//algorithm used while checking or even authenticating two details in files
			Utility utilityTools;
			utilityTools.coutCommasInLine(filename, num_of_fields_on_line);
			if(utilityTools.getCountedFields() == num_of_fields_on_line) {
				//below are if conditions used to handle the number of counted comma in the file if the above is condition is true
				if(num_of_fields_on_line == 6) {
					utilityTools.handlingDuplication(filename, num_of_fields_on_line);
					for(auto pair : userDataMap) {
						//will search through the map until the end of the map
						if(userDataMap.find(details_field1) != userDataMap.end() && userDataMap[details_field1].password == details_other_fields) {
							UserDetailsUsingMap userDetail = userDataMap[details_field1];
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
		static bool searchForFirstAndSecondField(string filename, string details_field1, string details_of_other_fields, int num_of_fields_on_line) {
			//algorithm used to verify the first field or the second field in the file
			//will help the one-to-many relationship inside the teacher when a teacher is being registered to a new course
			//one to many like: only one course taught by one teacher but a teacher could teach as many courses, so another teacher can't register to a course that is existng/tought by a teacher
			ofstream isNotYetMade(filename, ios_base::app);				//when the filename is not yet made open it in append
			bool exists;
			Utility utilityTools;
			string assume;
			string assume1;
			exists = utilityTools.coutCommasInLine(filename, num_of_fields_on_line);
			if(utilityTools.getCountedFields() == num_of_fields_on_line) {
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