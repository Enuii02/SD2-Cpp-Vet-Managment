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

class Pet
{
    std::string Name;
    std::string OwnderId;
    std::string LastAppointment;
    std::string MedicalHistory;
    void saveToDB();
};

/*
Classes needed:

-Pet

-User [Blueprint]
-Admin
-Veterinary
-Staff
-Guest

-------------------

Classes structure

PET:
ID
Name
Owner
Last appointment

USER:

ID
TypeOfUser
FirstName
LastName
Login
Password
DOB
ContactINfo

methods:

DisplaySelfInfo() - will allow users to display their information
SaveToDB() - will save user to the database when making a new one

ALL USER UNDER WILL INHERIT FROM USER

ADMIN:
methods:
*These will be imported from the features*

addPet
viewPetData
updatePetData
deletePetData

addOwner
viewOwnerData
updateOwnerData
deleteOwnerData

scheduleAppointment
modifyAppointment
cancelAppointment
viewAppointments

saveFIle()

VETERINARY:

addPet
viewPetData
updatePetData
deletePetData

scheduleAppointment
modifyAppointment
cancelAppointment
viewAppointments

viewOwnerData
updateOwnerData

STAFF:

scheduleAppointment
modifyAppointment
cancelAppointment
viewAppointments

viewOwnerData
viewPetData


all of these will functionalities will be their own seperate classes, check features.h
*/