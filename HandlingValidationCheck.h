#pragma once
#include<string>

class ValidationCheck {
    public:
        static bool validateUsername(const std::string& username);
        static bool validatePassword(const std::string& password);
        static bool validateId(const int& id);
        static bool validateFirstName(const std::string& first_name);
        static bool validateLastName(const std::string& last_name);
        static bool validateCategory(const std::string& category);
        static bool validateDOB(const int& day, const int& month, const int& year);
        static bool validateCourseId(const std::string& course_id);
        static bool validateCourseName(const std::string& course_name);
        static bool validateGpa(const float& gpa);
        static bool validateAllString(const std::string& any_string);
        static bool validateAllInt(const int& any_int);
        static bool validateYear(const std::string& year);
};


