#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include<map>
#include<string>
using namespace std;
struct UserDetailsUsingMap {					//is used for the user's details file
    // the key is string username;
    string details_field2;
    string details_field3;
    string details_field4;
    string details_field5;
    string details_field6;
    string details_field7;
};

extern  map<const string, UserDetailsUsingMap> userDataMap;

struct DetailsForOneCommaInLineUsingMap { //is used for the students enroll course file, and the teachers table file
    // the key is string details_field1;
    string details_field2;
};

extern  map<const string, DetailsForOneCommaInLineUsingMap> twoFieldsMap;

struct DetailsForTwoCommaInLineUsingMap { //is used for the students entry form file, and the course table file
    // the key is string details_field1;
    string details_field2;
    string details_field3;
};

extern  map<const string, DetailsForTwoCommaInLineUsingMap> threeFieldsMap;

struct DetailsForThreeCommaInLineUsingMap { //is used for the students grade file
    // the key is string details_field1
    string details_field2;
    string details_field3;
    string details_field4;
};

extern  map<const string, DetailsForThreeCommaInLineUsingMap> fourFieldsMap;
class Utility {
    public:
        string single_line_from_temp;
        char del = ',';
    private:
        int counting_fields = 0;
    public:
        void setCount(int count);
        int getCountedFields();
        //[[nodiscard]] is used to tell the compiler to warn the user if the return value is not used
public:
        bool countCommasInLine(const string& filename);
};
class Utility2 {
public:
    static bool handlingDuplication(const string &filename, int num_of_fields_in_line);
};
class DatabaseManager {
    public:
        static bool authenticateUserInFileManagementSystem
        (const std::string& details_field1,const std::string& details_of_other_fields,
        const std::string& filename,int num_of_fields_on_line);
        static void registerUser
        (const std::string& filename,const std::string& username,
        const std::string& password,const std::string& id,const std::string& first_name,
        const std::string& last_name,const std::string& sex,const std::string& date_of_birth);
        static bool deleteFileName();
        static bool renameFileName();
        static bool searchForFirstAndSecondField
        (const std::string& filename,const std::string& details_field1,
        const std::string& details_of_other_fields,int num_of_fields_on_line);
};
class ReadFileThatAreExtractingASingleUserDetails {
    public:
        static bool readFromAFile(const string& filename, int num_of_fields_in_line);
};
#endif //DATABASEMANAGER_H
