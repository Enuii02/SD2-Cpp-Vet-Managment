#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "profiles.h"
#include "menu.h"


using namespace std;

//-------------------------------------------------
// Main Function
//-------------------------------------------------

int main() {

    //-------------------------------------------------
    // For Testing, delete later
    //-------------------------------------------------

    Pet myPet("Buddy", "john_doe", "2024-05-01, 2025-01-15", "2020-08-12", "Golden Retriever");

    User user1("john_doe", "admin", "secure_password", "John Doe", "john.doe@example.com", "555-1234");

    User user2("jane_smith", "staff", "password123", "Jane Smith", "jane.smith@email.com", "555-5678");

    // User user3("alex_brown", "staff", "alexpass456", "Alex Brown", "alex.brown@mail.net", "555-8765");


    // Save save;
    // save.saveUser("john_doe", "admin", "secure_password", "John Doe", "john.doe@example.com", "555-1234");

    // View view;
    // view.viewAllUsers("Data/staffacc.txt");
    // view.viewAllPets("Data/pets.txt");

    // Update update;
    // update.updateUser("john_doe", "Data/staffacc.txt");

    Appointment a1(1, "Bella", "user1", "2025-04-11", "Annual checkup");
    Appointment a2(2, "Max", "user2", "2025-04-12", "Vaccination");
    Appointment a3(3, "Luna", "user3", "2025-04-13", "Dental cleaning");
    Appointment a4(4, "Charlie", "user4", "2025-04-14", "Skin allergy consultation");
    Appointment a5(5, "Rocky", "user5", "2025-04-15", "Follow-up visit");


    Delete delete_;
    delete_.deleteEntry("3", "Data/appointments.txt", "Appointment");
    delete_.deleteEntry("john_doe", "Data/staffacc.txt", "User");
    delete_.deleteEntry("Buddy", "Data/pets.txt", "Pet");



    //-------------------------------------------------

    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    // mainMenu();
    return 0;
}
