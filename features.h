#pragma once // With this the compiler won't open and read the file again after the first #include of the file
#include<string>

class View{
    public:

    void viewIndividual(std::string name, std::string fileName);

    void viewAllUsers(std::string fileName);

    void viewAllPets(std::string fileName);

    //TODO: viewIndividualAppointment
    //TODO: viewAllAppointments
};


class Save{
    public:

    void saveUser(std::string uname, std::string r, std::string pwd, 
        std::string fname, std::string mail, std::string phone);

    void savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
        std::string DOB, std::string breed);

    void saveAppointment(int appointmentID, std::string petName, std::string ownerUsername, std::string appopintmentDate, std::string appointmentDescription);
};

class Update{
    public:

    void updateUser(std::string uname, std::string filename);

    void updatePet(std::string petName, std::string filename); //WILL PROPERLY CHECK ON THURSDAY - owen
    
};

class Delete{
    public:

    void deleteEntry(const std::string& identifier, const std::string& fileName, const std::string& entryType);
};