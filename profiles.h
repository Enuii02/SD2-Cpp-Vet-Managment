#include<string>

class User
{
    public:
    int ID;
    std::string TypeOfUser;
    std::string FirstName;
    std::string LastName;
    std::string login;
    std::string password;
    std::string DOB;
    std::string ContactInfo;
    void DisplaySelfInfo();
    void SaveToDB();
};

class Pet
{
    int PetID;
    std::string Name;
    std::string OwnderId;
    std::string LastAppointment;
    std::string MedicalHistory;
    void SaveToDB();
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