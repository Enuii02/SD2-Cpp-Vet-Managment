#pragma once
#include <string>

class View {
    public:
        // Existing view functions
        void viewIndividual(std::string name, std::string fileName);
        void viewAllUsers(std::string fileName);
        void viewAllPets(std::string fileName);

        // New functions for appointments
        void viewIndividualAppointment(int appointmentID, std::string fileName);
        void viewAllAppointments(std::string fileName);
};

class Save {
    public:
        void saveUser(std::string uname, std::string r, std::string pwd, 
                      std::string fname, std::string mail, std::string phone);
        void savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
                     std::string DOB, std::string breed);
        void saveAppointment(int appointmentID, std::string petName, std::string ownerUsername, 
                             std::string appopintmentDate, std::string appointmentDescription);
};

class Update {
    public:
        void updateUser(std::string uname, std::string filename);
        void updatePet(std::string petName, std::string filename);
};

class Delete {
    public:
        void deleteProfile(std::string uname);
        void deletePet(const std::string& petName, const std::string& fileName);
};
