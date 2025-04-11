#ifndef PROFILES_H
#define PROFILES_H

#include <string>
#include "features.h"

//-------------------------------------------------
// User Blueprint
//-------------------------------------------------

class User {
public:
    // Constructor: creates a user and saves data via Save
    User(const std::string& uname, const std::string& r, const std::string& pwd,
         const std::string& fname, const std::string& mail, const std::string& phone);
    // View this user's details
    void viewSelf(const std::string& fileNameWithPath) const;
    // (Optional) Additional functions for saving/updating user data can be added here.
private:
    std::string username;
    std::string role;
    std::string password;
    std::string fullName;
    std::string email;
    std::string phoneNumber;
};

//-------------------------------------------------
// Pet Class
//-------------------------------------------------

class Pet {
public:
    // Constructor: creates a pet and saves data via Save
    Pet(const std::string& name, const std::string& ownerUsername,
        const std::string& appointmentsHistory, const std::string& DOB, const std::string& breed);
    // View this pet's details
    void viewSelf(const std::string& fileNameWithPath) const;
private:
    std::string name;
    std::string ownerUsername;
    std::string appointmentsHistory;
    std::string DOB;
    std::string breed;
};

//-------------------------------------------------
// Appointment Class
//-------------------------------------------------

class Appointment {
public:
    // Constructor: creates an appointment and saves data via Save
    Appointment(int appointmentID, const std::string& petName, const std::string& ownerUsername,
                const std::string& appointmentDate, const std::string& appointmentDescription);
private:
    int appointmentID;
    std::string petName;
    std::string ownerUsername;
    std::string appointmentDate;
    std::string appointmentDescription;
};
// test
#endif
