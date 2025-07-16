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
class CategoryAdmin : public Category {
    private:
        int admin_id, semester;
        std::string course_name, department;
    public:
        CategoryAdmin(const std::string& username) : Category(username) {};
        bool makeCourseInDB();
        bool removeCourseInDB();
        bool updateCourseInDB();
        bool adminView();
    public:
};
class CategoryTeacher : public Category {
    private:
        int teacher_id;
        float gpa_;
    public:
    CategoryTeacher(const std::string& username) : Category(username) {};
    bool teacherView();
    bool uploadGPA();
};