
#include <string>
#include <cstdio>
#include <iostream>
#include "DatabaseManager.cpp"
#include "HandlingValidationCheck.cpp"
using namespace std;

class AbstractClass {
	public:
		virtual ~AbstractClass() = default;
	public:
		//abstracted function used in my code
		virtual void applySearchForStudent()=0;
		virtual bool view()=0;
		virtual bool editDetails()=0;
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
		char del = '_';
	public:
	//Constructor
		explicit User(const string& username) {
			Utility utilityTools;
			utilityTools.handlingDuplication("users_File.txt", 6);
			//will search through the map until the end of the map
			if(userDataMap.find(username) != userDataMap.end()) {			                                            //if the username exist the constructor will initialize values into an object
				UserDetailsUsingMap userDetail = userDataMap[username];		                                            //using the registered username and using the structure will take a particular username details
				this->username = username;
				this->password=userDetail.details_field2;
				this->id=userDetail.details_field3;
				this->first_name=userDetail.details_field4;
				this->last_name=userDetail.details_field5;
				this->sex=userDetail.details_field6;
				this->date_of_birth=userDetail.details_field7;
				string sub_string;
				//sub string variable will used to extract the user's allocation in the management system
				//string line is equal to the username from the parameter, since it was true
				if(size_t underscore = username.find(this->del); underscore != string::npos) {			                //the underscore is surely found
					sub_string=username.substr(0, underscore);			                                        //now defining/intializing the sub string variable to the extracted part from the string line
				}
				this->user_classification=sub_string;          //used to easily use it in the code 
			} else {
				cout<<"Username doesn't exists in the database, thus we can't extract details."<<endl;
			}
		}		
			
	public:
	/* Trivial Destructor (main purpose only destroying the object created nothing else */
		virtual ~ User() = default;
	public:               
	//Handling setter and getters
		void setUsername(string existing_username) {
			this->username = move(existing_username);
		}
		string getUsername() {
			return username;
		}
		void setId(string existing_username_id) {
			this->id= move(existing_username_id);
		}	
		string getId() {
			return id;
		}
		void setPassword(string existing_username_password) {
			this->password = move(existing_username_password);
		}
		string getPassword() {
			return password;
		}
		void setUserClassification(string existing_username_classification) {
			this->user_classification = move(existing_username_classification);
		}
		string getUserClassification() {
			return user_classification;
		}
	public:
		virtual bool view() {
			//view algorithm for user used to view all the users file in the management system,
			//However its possible for the function to change complelety under other user's implementation
			for(auto&[fst, snd]: userDataMap) {
				cout
				<<"USERNAME: "<<fst<<endl
				<<"ID: "<<snd.details_field3<<endl
				<<"FIRST_NAME: "<<snd.details_field4<<endl
				<<"LAST_NAME: "<<snd.details_field5<<endl
				<<"SEX: "<<snd.details_field6<<endl
				<<"DATE_OF_BIRTH: "<<snd.details_field7<<endl;
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
			}
		}
		
	public:
		virtual bool editDetails(string& username) {
			//edit algorithm used for users to edit their password in the management system
			string new_password;   //variable storing the new password
			cout<<endl;
			cout<<"To change your old password.";
			cout<<endl;
			cout<<"Please Enter New Password: ";
			cin>>new_password;
			cin.ignore();
			if(bool exists = ValidationCheck::validatePassword(password)) {
				if(new_password == this->password) {
					cout<<"You are using your recent password, its not exactly changing your password."<<endl;
				} else {
					exists = DatabaseManager::searchForFirstAndSecondField("users_File.txt",
					this->username, this->password, 6);
					if(exists) {
						DatabaseManager::registerUser("temporarily_edit_table.txt", this->username,
						new_password,this->id,this->first_name, this->last_name,
						this->sex, this->date_of_birth);
						DatabaseManager::deleteFileName(); //delete the user database
						DatabaseManager::renameFileName(); //rename the temporarily_edit_table to users_File
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
		explicit Course(const string& course_id) {
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
		~ Course () = default;
	public:
	//Handling setters and getters
		void setCourseId(string entered_course_id) {
			this->course_id=move(entered_course_id);
		}
		string getCourseId() {
			return course_id;
		}			
};

class Student final: public User {
	public:
	//Constructor
		explicit Student(const string& username)
		: User(username) {}
	public:
	//destructor
		~ Student () override = default;
	public:		
	//Overriding view in student
		bool view() override {
			Utility utilityTools;
			cout<<endl;
			cout<<"\t/1. Option to view all courses/"<<endl;
			cout<<"\t/2. Option to view your profile/"<<endl;
			cout<<"\t/3. Option to view your recent grade(s)/"<<endl;
			cout<<"\t/4. Option to view the program(s) you are enrolled into/"<<endl;
			cout<<"\t/5. Option to view other students that are learning from the same course/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			int choice;
			cin>>choice;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto& [fst, snd] : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<fst<<endl
					<<"COURSE_NAME: "<<snd.details_field2<<endl
					<<"COURSE_YEAR: "<<snd.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"That's the only course provided in our management system."<<endl;
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
					<<"ID: "<<userDetails.details_field3<<endl
					<<"FIRST_NAME: "<<userDetails.details_field4<<endl
					<<"LAST_NAME: "<<userDetails.details_field5<<endl
					<<"SEX: "<<userDetails.details_field6<<endl
					<<"DATE_OF_BIRTH: "<<userDetails.details_field7<<endl
					<<endl;
				} else {
					cout<<"Cant find the username so that we could fetch the details in the line."<<endl;
				}
					//read my own profile
			} else if(choice == 3) {
				string student_classification;
				DatabaseManager::searchForFirstAndSecondField("students_grade_details_table_file.txt",
					this->getId(), student_classification, 3);
				utilityTools.handlingDuplication("temporarily_table2.0.txt", 3);
				//PLEASE VISIT THE DECLARATION IN searchForFirstAndSecondField FOR THE EXPLANATION OF THE temporarily_table2.0. file
				if(fourFieldsMap.empty() == 1) {
					cout<<"Your grades are not yet published by your teacher, just wait/call your teacher that your grade(s) are no yet published"<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temporarily_table2.0.txt", 3);
				}		
			} else if(choice == 4) {
				const string course_id = "EQUAL TO SOMETHING";
				DatabaseManager::searchForFirstAndSecondField("students_enroll_course_table_file.txt",
					this->getId(), course_id, 1);
				utilityTools.handlingDuplication("temp_file_two.txt", 1);
				if(twoFieldsMap.empty() == 1) {
					cout<<"You have not yet enrolled into any course the management system offers."<<endl;
				} else {
					ReadFileThatAreExtractingASingleUserDetails::readFromAFile("temp_file_two.txt", 1);
				}	
			} else if(choice == 5) {
				string course_id;
				cout<<"Enter course-ID : "<<endl;
				cin>>course_id;
				cin.ignore();
				if(bool exists = ValidationCheck::validateCourseId(course_id)) {
					const string course_name;
					exists = DatabaseManager::searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);   //check if the ID exists in the course table
					if(exists) {
						//handling the students with the same course, so that the student can view his or her classmates
						exists = DatabaseManager::authenticateUserInFileManagementSystem(this->getId(), course_id, "students_enroll_course_table_file.txt", 1);
						if(exists) {
							const string id = "EQUAL TO SOMETHING";
							DatabaseManager::searchForFirstAndSecondField("students_enroll_course_table_file.txt", id, course_id, 1);
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
		bool makeStudentsEnrollCourseTable(const string& course_id) {
			Utility utilityTools;
			if (bool exists = ValidationCheck::validateCourseId(course_id)) {
				cout<<endl;
				const string course_name;
				exists = DatabaseManager::searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
				//Check if the course ID exists in the database when the student enters the course ID in function navigate login menu
				if(exists) {
					utilityTools.handlingDuplication("students_enroll_course_table_file.txt", 1);
					//Check the student ID and course ID if they are already enrollled into a the student's enroll course table
					if(twoFieldsMap.find(this->getId()) != twoFieldsMap.end() && twoFieldsMap[this->getId()].details_field2 == course_id) {
						cout<<"You are already enrolled to the program "<<course_id<<endl;
					} else {
						if(ofstream outFile("students_enroll_course_table_file.txt", ios_base::app); !outFile.is_open()) {
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
			} return false;
		} 
};

class Employee {
	public:
	//Search for a student in the management system and the string id is the making a search algorithm
	//After the admin Enter a student ID we are able to view if that id exists
		static void searchForUser(const string& username) {
			Utility utilityTools;
			utilityTools.handlingDuplication("users_File.txt", 6);
			if(userDataMap.find(username) != userDataMap.end()) {
				cout<<"Username exists in the user database file."<<endl;
			} else {
				cout<<"Username doesn't exists in user database file."<<endl;
			}
		}
	protected:
	/*View function for all the employees working in the office 
	will view the student's details in our management system*/
		static bool employeeView() {;
			Utility utilityTools;
			int choice;
			cout<<endl;
			cout<<"\t/1. Option to view students entry details/"<<endl;
			cout<<"\t/2. Option to view students grade details/"<<endl;
			cout<<"\t/3. Option to view students enroll course details/"<<endl;
			cout<<endl;
			cout<<"Enter the view Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				ofstream IfFileIsNotYetMade("students_entry_details_file.txt", ios_base::app);
				utilityTools.handlingDuplication("students_entry_details_file.txt", 2);	
				for(auto& [fst, snd] : threeFieldsMap) {
					cout
					<<"USER-ID: "<<fst<<endl
					<<"STUDENT_CLASSIFICATION: "<<snd.details_field2<<endl
					<<"YEAR_OF_REGISTRATION: "<<snd.details_field3<<endl
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
					cout<<"The students have not yet registered by the registrar/admin."<<endl;
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

class Teacher final : public User, public Employee {
	public:
		//Constructor
		explicit Teacher(const string& username)
		: User(username), 
		Employee(){}
	public:
		bool readStudentsEnrolledToACourse(const string& course_id) {
			ofstream IfFileIsNotYetMade("students_enroll_course_table_file.txt", ios_base::app);
			if (bool exists = ValidationCheck::validateCourseId(course_id)) {
				const string course_name;
				exists = DatabaseManager::searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
				//Check if the course table has the entered course ID
				if(exists) {
					exists = DatabaseManager::authenticateUserInFileManagementSystem(this->getId(), course_id, "teachers_table_file.txt", 1);
					if(exists) {
						const string id = "EQUAL TO SOMETHING";
						DatabaseManager::searchForFirstAndSecondField("students_enroll_course_table_file.txt", id, course_id, 1);
						Utility utilityTools;
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
				for(auto&[fst, snd] : threeFieldsMap) {
					cout
					<<"COURSE-ID: "<<fst<<endl
					<<"COURSE_NAME: "<<snd.details_field2<<endl
					<<"COURSE_YEAR: "<<snd.details_field3<<endl
					<<endl;
				}
				if(threeFieldsMap.empty() == 0) {
					if(threeFieldsMap.size() == 1) {
						cout<<"that is the only course provided into the management system."<<endl;
					} else {
						cout<<"that's all the courses provided into the management system."<<endl;
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
					<<"ID: "<<userDetails.details_field3<<endl
					<<"FIRST_NAME: "<<userDetails.details_field4<<endl
					<<"LAST_NAME: "<<userDetails.details_field5<<endl
					<<"SEX: "<<userDetails.details_field6<<endl
					<<"DATE_OF_BIRTH: "<<userDetails.details_field7<<endl
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
				Employee::employeeView();
			}  else { 
				cout<<"Error: Invalid view Option."<<endl;;
			} return true;
		}
	public:
	//make the student's grade table after the exams are done with marking
		bool makeStudentsGradeTable() {
			ofstream outFile("students_grade_details_table_file.txt", ios_base::app);
			string course_id;
			cout<<"Enter course-ID of the program(s) that you teach: ";
			cin>>course_id;
			cin.ignore();
			string details_field2;
			if (bool exists = this->readStudentsEnrolledToACourse(course_id)) {
				//these must be together for the student, so that we could use the getter for the ID
				string username;
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				exists = ValidationCheck::validateId(username);
				if(exists) {
					const string password;
					exists = DatabaseManager::searchForFirstAndSecondField("users_File.txt", username, password, 6);
					if(exists) {
						Student student(username);
						exists = DatabaseManager::authenticateUserInFileManagementSystem(student.getId(), course_id, "students_enroll_course_table_file.txt", 1);
						if(exists) {
							string student_classification;
							cout<<"Enter classification/class: ";
							getline(cin>>ws, student_classification);
							exists = ValidationCheck::validateStudentClassification(student_classification);
							if(exists) {
								Utility utilityTools;
								utilityTools.handlingDuplication("students_entry_details_file.txt", 2);
								if(threeFieldsMap.find(student.getId()) != threeFieldsMap.end() &&
									threeFieldsMap[student.getId()].details_field2 == student_classification) {
									if (exists == DatabaseManager::authenticateUserInFileManagementSystem
										(student.getId(), course_id,
										"students_grade_details_table_file.txt", 3)) {
										cout<<"The students grade details for the ID and the course the student learns have already beign published into the students grade details file.."<<endl;
									} else {
										string gpa;
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

class Admin final : public User, public Employee {
	public:
		//Attribute
		string student_classification;
	public :
		//Constructor
		explicit Admin(const string& username)
		: User(username),
		Employee() {}
	public: 
		bool registration() {
			//Handling registration function in admin
			string gpa;
			bool exists;
			int choice;
			cout<<endl;
			cout<<"\t/1. Register course/"<<endl;
			cout<<"\t/2. Register teacher/"<<endl;
			cout<<"\t/3. Register student/"<<endl;
			cout<<endl;  
			cout<<"Enter the choice Option: ";
			cin>>choice;
			cin.ignore();
			system("CLS");
			cout<<endl;
			if(choice == 1) {
				string course_id;
				string course_name;
				cout<<"Enter course-ID: ";
				cin>>course_id;
				cin.ignore();
				if(exists == DatabaseManager::searchForFirstAndSecondField
					("course_table_file.txt", course_id,
					course_name, 2)) { //Check if the course ID exists
					cout<<"Error: The course-ID already exists in the file."<<endl;
				} else {
					if(exists == ValidationCheck::validateCourseId(course_id)) { //Validate the course ID Entered
						cout<<"Enter course name: ";
						cin>>course_name;
						cin.ignore();
						if(exists == ValidationCheck::validateCourseName(course_name)) { //Validate the course name Entered
							string course_year;
							cout<<"Enter course year: ";
							cin>>course_year;
							cin.ignore();
							if(exists == ValidationCheck::validateYear(course_year)) { //Validate the course year Entered
								if(ofstream outFile("course_table_file.txt", ios_base::app); !outFile.is_open()) {
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
					string username;
					string password;
					cout<<"Enter username: ";
					cin>>username;
					cin.ignore();
					if(exists == ValidationCheck::validateUsername(username)) {
						if(exists == DatabaseManager::searchForFirstAndSecondField
							("users_File.txt", username,
							password, 6)) {
							cout<<"The username already exists in the user's database, inorder to register to new course please go to 'register to new course'."<<endl;
						} else {
							cout<<"Enter Default Password: ";
							cin>>password;
							cin.ignore();
							if(exists == ValidationCheck::validatePassword(password)) {
								string id;
								cout<<"Enter ID: ";
								cin>>id;
								cin.ignore();
								if(exists == ValidationCheck::validateId(id)) {
									string course_id = "EQUAL TO SOMETHING";
									if(exists == DatabaseManager::searchForFirstAndSecondField
										("teachers_table_file.txt", id,
										course_id, 1)) {
										cout<<"The teachers-ID belongs to another teacher in the teachers table file."<<endl;
									} else {
										string first_name;
										cout<<"Enter First Name: ";
										cin>>first_name;
										cin.ignore();
										if(exists == ValidationCheck::validateFirstName(first_name)) {
											string last_name;
											cout<<"Enter Last Name: ";
											cin>>last_name;
											cin.ignore();
											if(exists = ValidationCheck::validateLastName(last_name)) {
												string sex;
												cout<<"Enter gender: ";
												cin>>sex;
												cin.ignore();
												if(exists == ValidationCheck::validateGender(sex)) {
													string date_of_birth;
													cout<<"Enter Date-Of-Birth: ";
													cin>>date_of_birth;
													cin.ignore();
													if(exists == ValidationCheck::validateDOB(date_of_birth)) {
														cout<<endl;
														Utility utilityTools;
														utilityTools.handlingDuplication
														("course_table_file.txt", 2);
														for(auto&[fst, snd] :
														threeFieldsMap) {
															cout
															<<"COURSE-ID: "<<fst<<endl
															<<"COURSE_NAME: "<<snd.details_field2<<endl
															<<"COURSE_YEAR: "<<snd.details_field3<<endl
															<<endl;
														}
														cout<<endl;
														cout<<"Enter course-ID: ";
														cin>>course_id;
														cin.ignore();
														if(string course_name;
															exists == DatabaseManager::searchForFirstAndSecondField
															("course_table_file.txt",
																course_id,
															course_name, 2)) {
															if(string temporarily_id = "EQUAL TO SOMETHING";
																exists == DatabaseManager::searchForFirstAndSecondField
																("teachers_table_file.txt",
																	temporarily_id,
																course_id, 1)) {
																cout<<"You can't register these teacher "
																<<"to the same course as an existing teacher."<<endl;
															} else {
																if(ofstream outFile("teachers_table_file.txt",
																	ios_base::app); !outFile.is_open()) {
																	cerr
																	<<"Error: Unable to open the teachers table file."
																	<<endl;
																} else {
																	DatabaseManager::registerUser
																	("users_File.txt", username,
																	password, id, first_name,
																	last_name, sex, date_of_birth);
																	outFile<<id<<","<<course_id<<endl;
																	cout
																	<<"Registration of the new teacher in both user's "
																	<<"database and teachers table file completed "
																	<<"successfully."
																	<<endl;
																}
															}
														} else {
															cout
															<<"The Course-ID doesn't exists in the course table."
															<<endl;
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
				Utility utilityTools;
				utilityTools.handlingDuplication("course_table_file.txt", 2);
				for(auto&[fst, snd] : threeFieldsMap) {
					cout
					<<"ID: "<<fst<<endl
					<<"COURSE_NAME: "<<snd.details_field2<<endl
					<<"COURSE_YEAR: "<<snd.details_field3<<endl
					<<endl;
				}
				cout<<endl;
				//displaying the course table file so that would have a chance of viewing details while registration
				string username;
				cout<<"Enter username: ";
				cin>>username;
				cin.ignore();
				if(exists == ValidationCheck::validateUsername(username)) {
					string password;
					if(exists == DatabaseManager::searchForFirstAndSecondField
					("users_File.txt", username,
					password, 6)) {
						Teacher teacher(username);
						string course_id;
						cout<<"Enter course-ID: ";
						cin>>course_id;
						cin.ignore();
						if(exists = ValidationCheck::validateCourseId(course_id);
							if(exists) {
								exists = DatabaseManager::searchForFirstAndSecondField("course_table_file.txt", course_id, course_name, 2);
								if(exists) {
									exists = DatabaseManager::authenticateUserInFileManagementSystem(teacher.getId(), course_id, "teachers_table_file.txt", 1);
									if(exists) {
										cout<<"the teacher is already registered to that course in our management system."<<endl;
									} else {
										id = "EQUAL TO SOMETHING";
										exists = DatabaseManager::searchForFirstAndSecondField("teachers_table_file.txt", id, course_id, 1);
										if(exists) {
											cout<<"You can't register these teacher to the same course as an existing teacher."<<endl;
										} else {
											ofstream outFile("teachers_table_file.txt", ios_base::app);
											if(!outFile.is_open()) {
												cerr<<"Error: Unable to open the teachers file, inorder to save the new entry details into the teachers details table."<<endl;
											} else {
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
				if (exists == ValidationCheck::validateUsername(username)) {
					if (exists == DatabaseManager::searchForFirstAndSecondField
						("users_File.txt", username, password, 6)) {
						cout<<"The username in the user's file already is registered into the school management system."<<endl;
					} else {
						cout<<"Enter Default Password: ";
						cin>>password;
						cin.ignore();
						if (exists == ValidationCheck::validatePassword(password)) {
							cout<<"Enter ID: ";
							cin>>id;
							cin.ignore();
							if (exists == ValidationCheck::validateId(id)) {
								exists = DatabaseManager::searchForFirstAndSecondField("students_entry_details_file.txt", id, student_classification, 2);
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
														string year_of_entry;
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

		bool editDetails(string& username) override {
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
bool allocateUserLoginClassification(const string& username) {
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
				string ptr* = student.getUsername();
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
	int num = 1;
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
	do {
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
	} while (num > 0);
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