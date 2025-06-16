#include "HandlingValidationCheck.h"
#include <iostream>
#include <ctime>
using namespace std;

bool ValidationCheck::validateUsername(const string &username) {
	if (username.length() > 9 && username.length() <= 15) {
		return true;
	}
	printf("Error: Invalid username length\n");
	return false;
}
bool ValidationCheck::validatePassword(const string& password) {
	if(password.length() > 9 && password.length() <= 15) {
		return true;
	}
	printf("Error: Invalid password length\n");
	return false;
}
bool ValidationCheck::validateId(const string& id) {
	if(id.length() > 9 && id.length() <= 15) {
		return true;
	}
	printf("Error: Invalid ID length\n");
	return false;
}
bool ValidationCheck::validateFirstName(const string& first_name) {
	if(first_name.length() > 2 && first_name.length() <= 15) {
		return true;
	}
	printf("Error: Invalid first name length\n");
	return false;
}
bool ValidationCheck::validateLastName(const string& last_name) {
	if(last_name.length() > 2 && last_name.length() <= 15) {
		return true;
	}
	printf("Error: Invalid last name length\n");
	return false;
}
bool ValidationCheck::validateGender(const string& sex) {
	if(sex == "Male" || sex == "Female") {
		return true;
	}
	printf("Error: Invalid gender\n");
	return false;
}
bool ValidationCheck::validateDOB(const int& day, const int& month, const int& year) {
	const time_t t = time(nullptr);   //set a timer to null
	const tm* now = localtime(&t);         //get a range of years pasted from the year 1900 to now
	if(const int current_year = now->tm_year + 1900; year < 1900 || year > current_year) {
		printf("Error: The year is out of range\n");
		return false;
	}

	if(month < 1 || month > 12) {
		printf("Error: The month is out of range\n");
		return false;
	}
	//normal number of days in each month
	int day_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//if the year was a leap year
	//this means the year is divisible by 4 but not divisible by 100 or just divisible by 400 when not divisible by 4
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
		day_in_month[1] = 29;
	}
	if(day < 1 || day > day_in_month[month-1]) {
		printf("Error: The day is out of range\n");
		return false;
	}

	return true;
}
bool ValidationCheck::validateCourseId(const string& course_id) {
	if(course_id.length() > 9 && course_id.length() <= 15) {
		return true;
	} else {
		return false;
	}
}
bool ValidationCheck::validateCourseName(const string& course_name) {
		if(course_name.length() > 3 && course_name.length() <= 20) {
			return true;
		} else {
			return false;
		}
}
bool ValidationCheck::validateYear(const string& course_year) {
	if(course_year.length() == 4) {
		return true;
	} else {
		return false;
	}
}
bool ValidationCheck::validateStudentClassification(const string& student_classification) {
	if(student_classification.length() > 5 && student_classification.length() <= 9) {
		return true;
	} else {
		return false;
	}
}
bool ValidationCheck::validateGpa(const string& gpa) {
	if(gpa.length() == 4) {return true;
	} else {
		return false;
	}
}
