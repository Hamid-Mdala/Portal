#ifndef HANDLINGVALIDATIONCHECK_H
#define HANDLINGVALIDATIONCHECK_H

#include<string>
using namespace std;

class ValidationCheck {
    public:
        static bool validateUsername(const string& username);
        static bool validatePassword(const string& password);
        static bool validateId(const string& id);
        static bool validateFirstName(const string& first_name);
        static bool validateLastName(const string& last_name);
        static bool validateGender(const string& sex);
        static bool validateDOB(const int& day, const int& month, const int& year);
        static bool validateCourseId(const string& course_id);
        static bool validateCourseName(const string& course_name);
        static bool validateYear(const string& course_year);
        static bool validateGpa(const string& gpa);
        static bool validateStudentClassification(const string& student_classification);
};

#endif //HANDLINGVALIDATIONCHECK_H
