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
    //uses defined in features.cpp under save section
    Save save;
    save.saveUser(uname, r, pwd, fname, mail, phone);
};


//uses method defined in features.cpp works also for pets
void User::viewSelf(const std::string& fileNameWithPath) const {
    View v;
    v.viewIndividual(username, fileNameWithPath);
}

//-------------------------------------------------
// Pet section
//-------------------------------------------------


Pet::Pet(const std::string& name, const std::string& ownerUsername,
          const std::string& appointmentsHistory,
          const std::string& DOB, const std::string& breed)
    : name(name), ownerUsername(ownerUsername), appointmentsHistory(appointmentsHistory),
      DOB(DOB), breed(breed)
    {
        Save save;
        save.savePet(name, ownerUsername, appointmentsHistory, DOB, breed);
    }