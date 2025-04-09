#include<string>
#include"features.h"


//-------------------------------------------------
// User Blueprint
//-------------------------------------------------

// All users will follow this formula:
// username, role, password, fullName, email, phoneNumber
// The order must be kept like that
class User
{
    public:
    // constructor
    User(const std::string& uname, const std::string& r, const std::string& pwd,
        const std::string& fname, const std::string& mail, const std::string& phone);
    
    // view this user's details
    void viewSelf(const std::string& fileNameWithPath) const;

    // save user's details
    void saveSelf(std::string uname, std::string r, std::string pwd,
        std::string fname, std::string mail, std::string phone);

    private:
    std::string username;
    std::string role;
    std::string password;
    std::string fullName;
    std::string email;
    std::string phoneNumber;
    
};

//-------------------------------------------------
// Pet class
//-------------------------------------------------

class Pet
{   
    public:
    // constructor
    Pet(const std::string& name, const std::string& ownerUsername, const std::string& appointmentsHistry,
        const std::string& DOB, const std::string& breed);
    
    // view this user's details
    void viewSelf(const std::string& fileNameWithPath) const;

    // save user's details
    void saveSelf(std::string uname, std::string r, std::string pwd,
        std::string fname, std::string mail, std::string phone);


    private:
    std::string name;
    std::string ownerUsername;
    std::string appointmentsHistory;
    std::string DOB;
    std::string breed;
};

//-------------------------------------------------
// Appointment class
//-------------------------------------------------

class Appointment
{   
    public:
    // constructor
    Appointment(const std::string& petName, const std::string& ownerUsername, 
                const std::string& appointmentDate, const std::string& appointmentDescription);
    
    // view this appointment's details
    void viewSelf(const std::string& fileNameWithPath) const;

    // save appointment's details
    void saveSelf() const;

    private:
    std::string petName;
    std::string ownerUsername;
    std::string appointmentDate;
    std::string appointmentDescription;
};
