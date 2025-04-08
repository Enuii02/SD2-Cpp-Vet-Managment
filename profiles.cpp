#include <iostream>
#include "profiles.h"

using namespace std;
//-------------------------------------------------
// User section
//-------------------------------------------------

//constructor
User::User(const std::string& uname, const std::string& r, const std::string& pwd,
    const std::string& fname, const std::string& mail, const std::string& phone)
: username(uname), role(r), password(pwd),
fullName(fname), email(mail), phoneNumber(phone) 
{
    // void Save::saveSelf(const std::string& uname, const std::string& r, const std::string& pwd, 
    //     const std::string& fname, const std::string& mail, const std::string& phone) {
    // }
}

//uses method defined in features.cpp
void User::viewSelf(const std::string& fileNameWithPath) const {
    View v;
    v.viewIndividual(username, fileNameWithPath);
}