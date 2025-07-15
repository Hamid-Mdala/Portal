#pragma once

#include<string>
using namespace std;

class ValidationCheck {
    public:
        static bool validateUsername(const string& username);
        static bool validatePassword(const string& password);
        static bool validateId(const int& id);
        static bool validateFirstName(const string& first_name);
        static bool validateLastName(const string& last_name);
        static bool validateCategory(const string& category);
        static bool validateDOB(const int& day, const int& month, const int& year);
        static bool validateCourseId(const string& course_id);
        static bool validateCourseName(const string& course_name);
        static bool validateGpa(const float& gpa);
        static bool validateAllString(const string& any_string);
        static bool validateAllInt(const int& any_int);
        static bool validateYear(const std::string& year);
};


