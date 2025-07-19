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
bool ValidationCheck::validateId(const int& id) {
	if(id > 0 || id != '\0') {
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
bool ValidationCheck::validateCategory(const string& category) {
	if(category == "student" || category == "teacher" || category == "admin") {
		return true;
	}
	printf("Error: Invalid category\n");
	printf("please make sure the category is either 'student, teacher, admin'");
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
	//this means the year is divisible by 4 but not divisible by 100 or just divisible by 400
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
	}
	printf("Error: Invalid course code length\n");
	return false;
}
bool ValidationCheck::validateCourseName(const string& course_name) {
	if(course_name.length() > 3 && course_name.length() <= 20) {
		return true;
	}
	printf("Error: Invalid course name length\n");
	return false;
}

bool ValidationCheck::validateAllString(const string& any_string) {
	if(any_string.empty()) {
		printf("Error: The string value is invalid\n");
		return false;
	}

	return true;
}
bool ValidationCheck::validateGpa(const float& gpa) {
	if (gpa >= 0.0 && gpa <= 4.0) {
		return true;
	}
	printf("Error: The GPA value is out of range\n");
	return false;
}
bool ValidationCheck::validateAllInt(const int &any_int) {
	if (any_int > 0) {
		return true;
	}
	printf("Error: The int value is invalid\n");
	return false;
}

bool ValidationCheck::validateYear(const string& year) {
	if (year == "fresh-man" || year == "sophomore" || year == "junior" || year == "senior") {
		//Fresh-man, Sophomore, Junior or Senior
		return true;
	}
	printf("please make sure the year is either 'fresh-man, sophomore, junior, senior'");
	return false;
}