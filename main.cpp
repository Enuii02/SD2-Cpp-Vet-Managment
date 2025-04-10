#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "profiles.h"
#include "menu.h"

using namespace std;

int main() {

    // Ensure that the necessary files exist.
    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    ensureFileExists("Data/appointments.txt");

    // ----------------------------------------------------------------
    // Test the new View functions for appointment records.
    // ----------------------------------------------------------------
    View viewObj;

    // Test: Display all appointments.
    cout << "\n=== Testing viewAllAppointments ===\n";
    viewObj.viewAllAppointments("Data/appointments.txt");

    // Test: Display an individual appointment using an appointment ID.
    // Replace '101' with an appointmentID that exists in your appointments.txt.
    int testAppointmentID = 1;
    cout << "\n=== Testing viewIndividualAppointment for appointment ID " << testAppointmentID << " ===\n";
    viewObj.viewIndividualAppointment(testAppointmentID, "Data/appointments.txt");

    // ----------------------------------------------------------------
    // Uncomment the next line if you wish to start the menu system.
    // mainMenu();

    // -----------------------------------------------------------------
    // Testing all of appointments.txt
    // -----------------------------------------------------------------

        // Test data for Save
        std::string username = "john_doe";
        std::string role = "admin";
        std::string password = "password123";
        std::string fullName = "John Doe";
        std::string email = "john.doe@example.com";
        std::string phone = "123-456-7890";
    
        std::string petName = "Fluffy";
        std::string ownerUsername = "john_doe";
        std::string appointmentHistory = "Checkup on 2025-04-01";
        std::string DOB = "2020-05-01";
        std::string breed = "Labrador";
    
        int appointmentID = 1001;
        std::string appointmentDate = "2025-04-01";
        std::string appointmentDescription = "Routine Checkup";
    
        // Test: Save User
        Save save;
        save.saveUser(username, role, password, fullName, email, phone);
    
        // Test: Save Pet
        save.savePet(petName, ownerUsername, appointmentHistory, DOB, breed);
    
        // Test: Save Appointment
        save.saveAppointment(appointmentID, petName, ownerUsername, appointmentDate, appointmentDescription);
    
        // Test: View All Users
        View view;
        view.viewAllUsers("Data/staffacc.txt");
    
        // Test: View All Pets
        view.viewAllPets("Data/pets.txt");
    
        // Test: View All Appointments
        view.viewAllAppointments("Data/appointments.txt");
    
        // Test: View Individual User
        view.viewIndividual(username, "Data/staffacc.txt");
    
        // Test: View Individual Pet
        view.viewIndividual(petName, "Data/pets.txt");
    
        // Test: View Individual Appointment
        view.viewIndividualAppointment(appointmentID, "Data/appointments.txt");
    
        // Test: Update User
        Update update;
        update.updateUser(username, "Data/staffacc.txt");
    
        // Test: Update Pet
        update.updatePet(petName, "Data/pets.txt");
    
        // Test: Delete User
        Delete del;
        del.deleteEntry(username, "Data/staffacc.txt", "User");
    
        // Test: Delete Pet
        del.deleteEntry(petName, "Data/pets.txt", "Pet");
    
        // Test: Delete Appointment
        del.deleteEntry(std::to_string(appointmentID), "Data/appointments.txt", "Appointment");

    return 0;
}
