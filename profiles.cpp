#include <iostream>
#include "profiles.h"

using namespace std;

//-------------------------------------------------
// User Section
//-------------------------------------------------

User::User(const std::string& uname, const std::string& r, const std::string& pwd,
           const std::string& fname, const std::string& mail, const std::string& phone)
    : username(uname), role(r), password(pwd), fullName(fname), email(mail), phoneNumber(phone)
{
    Save save;
    save.saveUser(uname, r, pwd, fname, mail, phone);
}

void User::viewSelf(const std::string& fileNameWithPath) const {
    View v;
    v.viewIndividual(username, fileNameWithPath);
}

//-------------------------------------------------
// Pet Section
//-------------------------------------------------

Pet::Pet(const std::string& name, const std::string& ownerUsername,
         const std::string& appointmentsHistory, const std::string& DOB, const std::string& breed)
    : name(name), ownerUsername(ownerUsername), appointmentsHistory(appointmentsHistory),
      DOB(DOB), breed(breed)
{
    Save save;
    save.savePet(name, ownerUsername, appointmentsHistory, DOB, breed);
}

void Pet::viewSelf(const std::string& fileNameWithPath) const {
    View v;
    v.viewIndividual(name, fileNameWithPath);
}

//-------------------------------------------------
// Appointment Section
//-------------------------------------------------

Appointment::Appointment(int appointmentID, const std::string& petName, const std::string& ownerUsername,
                         const std::string& appointmentDate, const std::string& appointmentDescription)
    : appointmentID(appointmentID), petName(petName), ownerUsername(ownerUsername),
      appointmentDate(appointmentDate), appointmentDescription(appointmentDescription)
{
    Save save;
    save.saveAppointment(appointmentID, petName, ownerUsername, appointmentDate, appointmentDescription);
}
