#pragma once
#include <string>
//I have to store student category details
class category {
    public:
        std::string username_;     //the admin, student and teacher user_id is used as a key in the table
        int user_id;
        std::string course_code;   //the course_code is made by the admin and used by the student and teacher
        std::string semester;     //the semester is made by the admin and used by student and teacher
};

class CategoryEmployee: category {
    protected:
        std::string department;
        std::string hire_date;
        std::string office_num;

};
class CategoryStudent : category {
    public:
        std::string year;      //the year the student is in
    private:
        int student_id;  //Used as a key in the table
    public:
        CategoryStudent(const std::string& username);   //this will give us all the needed requirements

        bool enrollCourse();   //use the student_id to enroll into the course
        bool getResults();     //use the student_id to get the results in gpa column
        bool updateProfile();
    public:
        void setId(const int& id);
        int getId();
        //once they are logged in the student is able to either
        /* 1. enroll into course(input class, course_code, student_id)
         * using the username we will get the user_id,
         * 2. get results(teacher will give the student gpa)
         * 3. update profile (inside this the student is able to update their details
         */
};

class CategoryAdmin : CategoryEmployee {
    public:
        std::string course_code; //the role of admin to make the course_code
    private:
        std::string admin_id; //Used as a key in the table
    public:
        //fill in the course tables fields


};

class CategoryTeacher : CategoryEmployee {
    private:
        std::string teacher_id; //Used as the key in the table
        std::string gpa_;  //the role of teacher to make the students gpa

};