#pragma once
#include <string>

class View {
public:
    // View functions (for users, pets, and appointments)
    void viewIndividual(std::string name, std::string fileName); // works for pets and users
    void viewAllUsers(std::string fileName);
    void viewAllPets(std::string fileName);
    void viewIndividualAppointment(int appointmentID, std::string fileName);
    void viewAllAppointments(std::string fileName);
};

class Save {
public:
    // Save functions for each object type.
    void saveUser(std::string uname, std::string r, std::string pwd,
                  std::string fname, std::string mail, std::string phone);
    void savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory,
                 std::string DOB, std::string breed);
    void saveAppointment(int appointmentID, std::string petName, std::string ownerUsername,
                         std::string appopintmentDate, std::string appointmentDescription);
};

class Update {
public:
    // Update functions for each object type.
    void updateUser(std::string uname, std::string filename);
    void updatePet(std::string petName, std::string filename);
    void updateAppointment(int appointmentID, const std::string& fileName);
};

class Delete {
public:
    // Delete function: identifier is a unique key (for user, pet, or appointment)
    void deleteEntry(const std::string& identifier, const std::string& fileName, const std::string& entryType);
};

// Account management functions (for sign up)
void createNewAccount();
void alreadyHaveAccount();
bool checkForDuplicates(const std::string& identifier, const std::string& pathToFile);
