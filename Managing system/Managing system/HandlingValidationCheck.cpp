#include <string>

using namespace std;
class ValidationCheck {
	//these class ValidationCheck handles the data consistency when the user enters input im my management system
	public:
		static bool validateUsername(const string& username) {
			if(username.length() > 9 && username.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateId(const string& id) {
			if(id.length() > 9 && id.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validatePassword(const string& password) {
			if(password.length() > 9 && password.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateFirstName(const string& first_name) {
			if(first_name.length() > 2 && first_name.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateLastName(const string& last_name) {
			if(last_name.length() > 2 && last_name.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateGender(const string& sex) {
			if(sex.length() == 1) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateDOB(const string& date_of_birth) {
			if(date_of_birth.length() == 10) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateCourseId(const string& course_id) {
			if(course_id.length() > 9 && course_id.length() <= 15) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateCourseName(const string& course_name) {
			if(course_name.length() > 3 && course_name.length() <= 20) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateYear(const string& course_year) {
			if(course_year.length() == 4) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateStudentClassification(const string& student_classification) {
			if(student_classification.length() > 5 && student_classification.length() <= 9) {
				return true;
			} else {
				return false;
			}
		}
	public:
		static bool validateGpa(const string& gpa) {
			if(gpa.length() == 4) {
				return true;
			} else {
				return false;
			}
		}

};
