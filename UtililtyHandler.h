#pragma once
#include <string>

class Category {
    public:
        std::string username_;
        std::string course_code;

        Category(const std::string& username);
        bool updateProfile();
        bool deleteProfile();
};
class CategoryStudent : public Category {
    public:
        CategoryStudent(const std::string& username): Category(username) {};
        bool enrollCourse();
        bool getResults();
    private:
        int student_id, user_id;
        std::string year;
};
class CategoryTeacher : public Category {
    public:
        CategoryTeacher(const std::string& username) : Category(username) {};
        bool teacherView();
        bool uploadGPA();
    public:
        int user_id, teacher_id;
        float gpa_;
};
class CategoryAdmin : public Category {
    public:
        CategoryAdmin(const std::string& username) : Category(username) {};
        bool makeCourseInDB();
        bool removeCourseInDB();
        bool updateCourseInDB();
        bool adminView();
    public:
        int semester;
        std::string course_name, department;
};
