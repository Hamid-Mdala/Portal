#ifndef NAVIGATIONMENUS_H
#define NAVIGATIONMENUS_H

#include <string>
using namespace std;

class AllocateUser {
public:
    //Function handling the users allocation the aim is after logged in by the system during runtime they will have their own menu.
    static bool allocateUserLoginClassification(const string& username);
};
class login {
    public:
        //Function handling the login in our management system
        static bool handlingLogin();
};


#endif //NAVIGATIONMENUS_H
