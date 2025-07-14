#pragma once
#include <string>
//I have to store student category details
class Category {
    public:
        Category(const std::string& username);   //this will give us all the needed requirements
        std::string username_;     //the admin, student and teacher user_id is used as a key in the table
        int user_id;  //user_id
        std::string course_code;   //the course_code is made by the admin and used by the student and teacher
        std::string semester;     //the semester is made by the admin and used by student and teacher
    public:
        bool updateProfile();
        bool deleteProfile();
};


class CategoryEmployee {
    protected:
        std::string department;
        std::string hire_date;
        std::string office_num;

};

class CategoryStudent : public Category {
    public:
        std::string year;      //the year the student is in like fresh-man
    private:
        int student_id;  //Used as a key in the table
    public:
        CategoryStudent(const std::string& username): Category(username) {};
        bool enrollCourse();   //use the student_id to enroll into the course
        bool getResults();     //use the student_id to get the results in gpa column
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

class CategoryAdmin : public CategoryEmployee, public Category {
    private:
        std::string admin_id; //Used as a key in the table
        std::string course_name;
    public:
        CategoryAdmin(const std::string& username): CategoryEmployee(), Category(username) {};
        std::string makeCourseInDB();
        bool removeCourseInDB();
        bool updateCourseInDB();
        bool adminView();
    public:
};

extern  std::string global_course;  //used in teacher and student

class CategoryTeacher : public CategoryEmployee, public Category {
    private:
        std::string teacher_id; //Used as the key in the table
        std::string gpa_;  //the role of teacher to make the students gpa
    public:
    CategoryTeacher(const std::string& username): CategoryEmployee(), Category(username) {};
};