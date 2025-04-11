#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include "features.h"
#include "profiles.h"
#include "menu.h"
#include <regex>
#include <limits>

Update update;
Delete deleteInstance;
View view;
Save save;

std::string loggedInUser;
//-------------------------------------------------
// Account Management Functions
//-------------------------------------------------



void createNewAccount() {
    std::string fullName, email, phone, username, password, confirmPassword;
    int accountTypeChoice;

    std::regex emailRegex(R"((\w+)(\.?[\w-]+)*@(\w+)(\.[a-zA-Z]{2,}))");
    std::regex phoneRegex(R"(^\+?\d{7,15}$)");
    std::regex usernameRegex(R"(\w{4,})");

    std::cout << "\n--- Create New Account ---" << std::endl;

    std::cout << "Enter Full Name: ";
    std::getline(std::cin, fullName);
    if (fullName.empty()) {
        std::cerr << "Full name cannot be empty.\n";
        return;
    }

    std::cout << "Enter Email Address: ";
    std::getline(std::cin, email);
    if (!std::regex_match(email, emailRegex)) {
        std::cerr << "Invalid email format.\n";
        return;
    }

    std::cout << "Enter Phone Number (optional, format: +44714567890): ";
    std::getline(std::cin, phone);
    if (!phone.empty() && !std::regex_match(phone, phoneRegex)) {
        std::cerr << "Invalid phone number format.\n";
        return;
    }

    std::cout << "Choose Username (min 4 characters): ";
    std::getline(std::cin, username);
    if (!std::regex_match(username, usernameRegex)) {
        std::cerr << "Invalid username. Must be at least 4 alphanumeric characters.\n";
        return;
    }

    std::cout << "Choose Password: ";
    std::getline(std::cin, password);

    std::cout << "Confirm Password: ";
    std::getline(std::cin, confirmPassword);
    if (password != confirmPassword) {
        std::cerr << "Passwords do not match. Account creation failed.\n";
        return;
    }

    std::cout << "\nChoose Account Type:\n1. Guest\n2. Staff (Admin/Staff/Veterinary)" << std::endl;
    std::cout << "Enter your choice: ";
    if (!(std::cin >> accountTypeChoice)) {
        std::cerr << "Invalid input. Expected an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore();

    if (accountTypeChoice == 1) {
        if (!checkForDuplicates(username, "Data/owner.txt")) {
            save.saveUser(username, "guest", password, fullName, email, phone);
            std::cout << "Guest account created successfully!" << std::endl;
        } else {
            std::cout << "Account already exists. Please login." << std::endl;
        }
    } else if (accountTypeChoice == 2) {
        int roleChoice;
        std::string role;
        std::cout << "Select Role:\n1. Admin\n2. Staff\n3. Veterinary" << std::endl;
        std::cout << "Enter your choice: ";
        if (!(std::cin >> roleChoice)) {
            std::cerr << "Invalid input. Expected an integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        std::cin.ignore();

        switch (roleChoice) {
            case 1: role = "admin"; break;
            case 2: role = "staff"; break;
            case 3: role = "vet"; break;
            default:
                std::cerr << "Invalid role choice. Account creation failed.\n";
                return;
        }

        if (!checkForDuplicates(username, "Data/staffacc.txt")) {
            save.saveUser(username, role, password, fullName, email, phone);
            std::cout << role << " account created successfully!" << std::endl;
        } else {
            std::cout << "Account already exists. Please login." << std::endl;
        }
    } else {
        std::cerr << "Invalid account type choice. Account creation failed.\n";
    }
}


void alreadyHaveAccount() {
    std::cout << "\nRedirecting to Login Menu..." << std::endl;
    loginMenu();  // Call the actual loginMenu function
}



//-------------------------------------------------
// Utility Functions
//-------------------------------------------------
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ensureFileExists(const std::string& filename) {
    std::ofstream ofs(filename, std::ios::app);
    ofs.close();
}

//-------------------------------------------------
// Login and Sign Up Menus (Redirection Only)
//-------------------------------------------------

bool checkCredentials(const std::string& username, const std::string& password, const std::string& filename, const std::string& expectedRole) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty())
            continue;
        std::stringstream ss(line);

        // std::cout << line << std::endl; // test, delete later

        std::string fileUsername, filePassword, fileRole;
        std::getline(ss, fileUsername, ',');
        if(fileUsername != username){
            continue;
        }
        std::getline(ss, fileRole, ',');
        std::getline(ss, filePassword, ',');

        if (fileUsername == username && filePassword == password) {
            if (expectedRole == "Guest" || fileRole == expectedRole)
                return true;
        }
    }
    return false;
}

bool loginUser(const std::string& expectedRole) {
    std::string filename = (expectedRole == "guest") ? "Data/owner.txt" : "Data/staffacc.txt";
    ensureFileExists(filename);
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    if (checkCredentials(username, password, filename, expectedRole)) {
        std::cout << "Login successful as " << expectedRole << "!" << std::endl;
        loggedInUser = username;
        return true;
    }
    else {
        std::cout << "Login failed. Invalid credentials." << std::endl;
        return false;
    }
}

//-------------------------------------------------
// Main Menu
//-------------------------------------------------
void mainMenu() {
    int choice;
    do {
        std::cout << "\n=== Main Menu ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: loginMenu(); break;
            case 2: signUpMenu();
            case 3: std::cout << "Exiting program. Goodbye!" << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 3);
}

//-------------------------------------------------
// Login Menu
//-------------------------------------------------
void loginMenu() {
    int choice;
    do {
        std::cout << "\n=== Login Menu ===" << std::endl;
        std::cout << "1. Admin" << std::endl;
        std::cout << "2. Staff" << std::endl;
        std::cout << "3. Veterinary" << std::endl;
        std::cout << "4. Guest" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: if (loginUser("admin")) adminMenu(); break;
            case 2: if (loginUser("staff")) staffMenu(); break;
            case 3: if (loginUser("vet")) veterinaryMenu(); break;
            case 4: if (loginUser("guest")) guestMenu(); break;
            case 0: std::cout << "Returning to Main Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Sign Up Menu
//-------------------------------------------------
void signUpMenu() {
    int choice;
    do {
        std::cout << "\n=== Sign Up Menu ===" << std::endl;
        std::cout << "1. Create New Account" << std::endl;
        std::cout << "2. Already Have an Account?" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: createNewAccount(); break;
            case 2: alreadyHaveAccount(); break;
            case 0: std::cout << "Returning to Main Menu..." << std::endl;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

//---------------------------------------------------------------------------
// User menus
//---------------------------------------------------------------------------

void adminMenu() {
    int choice;
    do {
        std::cout << "\n=== Admin Menu ===" << std::endl;
        std::cout << "1. Appointment Management" << std::endl;
        std::cout << "2. Owner Management" << std::endl;
        std::cout << "3. Pet Management" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: adminAppointmentManagementMenu(); break;
            case 2: adminOwnerManagementMenu(); break;
            case 3: adminPetManagementMenu(); break;
            case 0: std::cout << "Logging out of Admin account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void adminAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Appointment Management ---" << std::endl;
        std::cout << "1. Schedule Appointment" << std::endl;
        std::cout << "2. Modify Appointment" << std::endl;
        std::cout << "3. Cancel Appointment" << std::endl;
        std::cout << "4. View Appointment Records" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess(); break;
            case 0: std::cout << "Returning to Admin Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void adminOwnerManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Owner Management ---" << std::endl;
        std::cout << "1. View Owner Records" << std::endl;
        std::cout << "2. Add Owner" << std::endl;
        std::cout << "3. Update Owner Details" << std::endl;
        std::cout << "4. Remove Owner" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: viewOwnerRecords(); break;
            case 2: addOwner(); break;
            case 3: updateOwner(); break;
            case 4: removeOwner(); break;
            case 0: std::cout << "Logging out of Admin account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void adminPetManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Pet Management ---" << std::endl;
        std::cout << "1. View Pet Records" << std::endl;
        std::cout << "2. Add Pet" << std::endl;
        std::cout << "3. Update Pet Details" << std::endl;
        std::cout << "4. Remove Pet" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: viewPetRecord(); break;
            case 2: addPetRecord(); break;
            case 3: updatePetRecord(); break;
            case 4: removePetRecord(); break;
            case 0: std::cout << "Returning to Admin Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

// Owner stuff----------------------------------------------------------------------------
void viewOwnerRecords() {
    std::string username;
    std::cout << "Enter the username of the owner to view: ";
    std::cin >> username;

    View view;
    std::cout << "Test";
    view.viewIndividual(username, "Data/owner.txt");  // adjust path if different
}

void addOwner() {
    std::string uname, role = "guest", pwd, fname, mail, phone;

    std::cout << "Enter new owner's username: ";
    std::cin >> uname;
    std::cout << "Enter password: ";
    std::cin >> pwd;
    std::cout << "Enter full name: ";
    std::cin.ignore(); // flush newline
    std::getline(std::cin, fname);
    std::cout << "Enter email: ";
    std::cin >> mail;
    std::cout << "Enter phone number: ";
    std::cin >> phone;

    Save save;
    save.saveUser(uname, role, pwd, fname, mail, phone);
    std::cout << "Owner profile added successfully.\n";
}

void updateOwner() {
    std::string username;
    std::cout << "Enter the username of the owner to update: ";
    std::cin >> username;

    Update update;
    update.updateUser(username, "data/users.txt");  // adjust path if needed
}

void removeOwner() {
    std::string username;
    std::cout << "Enter the username of the owner to delete: ";
    std::cin >> username;

    Delete del;
    del.deleteEntry(username, "Data/owner.txt", "Owner");
    std::cout << "Owner profile deleted successfully.\n";
}

void staffMenu() {
    int choice;
    do {
        std::cout << "\n=== Staff Menu ===" << std::endl;
        std::cout << "1. Appointment Management" << std::endl;
        std::cout << "2. View Pet Records" << std::endl;
        std::cout << "3. View Owner Records" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: staffAppointmentManagementMenu(); break;
            case 2: viewPetRecord(); break;
            case 3: viewOwnerRecords(); break;
            case 0: std::cout << "Logging out of Staff account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}
// --------------------------------------------------------------------------------

void staffAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Staff Appointment Management ---" << std::endl;
        std::cout << "1. Schedule Appointment" << std::endl;
        std::cout << "2. Modify Appointment" << std::endl;
        std::cout << "3. Cancel Appointment" << std::endl;
        std::cout << "4. View Appointment Records" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess; break;
            case 0: std::cout << "Returning to Staff Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void veterinaryMenu() {
    int choice;
    do {
        std::cout << "\n=== Veterinary Menu ===" << std::endl;
        std::cout << "1. Appointment Management" << std::endl;
        std::cout << "2. Owner Management" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: veterinaryAppointmentManagementMenu(); break;
            case 2: veterinaryOwnerManagementMenu(); break;
            case 0: std::cout << "Logging out of Veterinary account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void veterinaryAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Veterinary Appointment Management ---" << std::endl;
        std::cout << "1. Schedule Appointment" << std::endl;
        std::cout << "2. Modify Appointment" << std::endl;
        std::cout << "3. Cancel Appointment" << std::endl;
        std::cout << "4. View Appointment Records" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess(); break;
            case 0: std::cout << "Returning to Veterinary Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}



void veterinaryOwnerManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Veterinary Owner Management ---" << std::endl;
        std::cout << "1. View Owner Records" << std::endl;
        std::cout << "2. Update Owner Details" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: viewOwnerRecords(); break;
            case 2: updateOwner(); break;
            case 0: std::cout << "Returning to Veterinary Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void guestMenu() {
    int choice;
    do {
        std::cout << "\n=== Guest Menu ===" << std::endl;
        std::cout << "1. View Pet Records" << std::endl;
        std::cout << "2. View Owner Records" << std::endl;
        std::cout << "3. View Appointment Records" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input." << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: std::cout << "Redirecting to View Pet Records..." << std::endl; break;
            case 2: std::cout << "Redirecting to View Owner Records..." << std::endl; break;
            case 3: std::cout << "Redirecting to View Appointment Records..." << std::endl; break;
            case 0: std::cout << "Logging out of Guest account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Utility functions, these are connected to features.cpp
//-------------------------------------------------


void scheduleAppointment() {

    int appointmentID;
    std::string petName;
    std::string ownerUsername;
    std::string appointmentDescription;

    std::cout << "\n--- Schedule Appointment ---\n";

    // Get Appointment ID
    std::cout << "Enter Appointment ID (integer): ";
    while (!(std::cin >> appointmentID)) {
        std::cout << "Invalid input. Please enter a valid integer for Appointment ID: ";
        return
        clearInput();
    }

    std::string stringID = std::to_string(appointmentID);
    if(checkForDuplicates(stringID, "Data/appointments")) {
        return;
    }
    clearInput();

    // Get Pet Name
    std::cout << "Enter Pet Name: ";
    std::getline(std::cin, petName);

    // Get Owner Username
    std::cout << "Enter Owner Username: ";
    std::getline(std::cin, ownerUsername);

    // Get Appointment Date
    std::string appointmentDate;
    std::regex dateRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");

    std::cout << "Enter Appointment Date (e.g., 2025-04-12): ";
    std::getline(std::cin, appointmentDate);

    if (std::regex_match(appointmentDate, dateRegex)) {
        std::cout << "Valid date format.\n";
    } else {
        std::cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        return;
    }

    // Get Appointment Description
    std::cout << "Enter Appointment Description: ";
    std::getline(std::cin, appointmentDescription);

    Appointment appointment(appointmentID, petName, ownerUsername, appointmentDate, appointmentDescription);

}

void modifyAppointment() {
    int appointmentID;
    std::string filePath = "Data/appointments.txt";

    // Ask the user for the Appointment ID
    std::cout << "\n--- Modify Appointment ---\n";
    std::cout << "Please enter the Appointment ID of the appointment you want to modify: ";

    // Input validation for the Appointment ID
    while (!(std::cin >> appointmentID)) {
        std::cout << "Invalid input. Please enter a valid integer for Appointment ID: ";
        std::cin.clear();  // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
    }

    // Proceed to update the appointment using the given ID
    update.updateAppointment(appointmentID, filePath);

    std::cout << "Exiting to menu..." << std::endl;
}

void cancelAppointment(){
    std::cout << "\n--- Delete Appointment ---\n";

    std::string identifier;
    std::string fileName = "Data/appointments.txt";
    std::string entryType = "Appointment";

    std::cout << "Please enter appointment ID you would like to delete:";
    std::cin >> identifier;

    if (identifier.empty()) {
        std::cout << "Invalid input. Please enter a valid appointment ID." << std::endl;
        return;
    }

    deleteInstance.deleteEntry(identifier, fileName, entryType);
};

void viewAppointmentRecordsFullAcess() {
    int choice;
    std::string pathToFile = "Data/appointments.txt";
    std::cout << "\n--- View Appointment Records ---\n";
    std::cout << "1. View All Appointment Records\n";
    std::cout << "2. View a Specific Appointment Record\n";
    std::cout << "0. Back\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid choice." << std::endl;
        clearInput();  // Clear invalid input
        return;
    }

    // Handle the user choice
    switch (choice) {
        case 1: {
            view.viewAllAppointments(pathToFile);
            break;
        }
        case 2: {
            // Display a specific record
            int identifier;
            std::cout << "Enter Appointment ID: ";
            std::cin >> identifier;
            
            view.viewIndividualAppointment(identifier, pathToFile);
            break;
        }
        case 0:
            std::cout << "Returning to previous menu...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

//-------------------------------------------------------
// Pets
//-------------------------------------------------------

void viewPetRecord(){
    int choice;
    std::string pathToFile = "Data/pets.txt";
    std::cout << "\n--- View Pets Records ---\n";
    std::cout << "1. View All Pets Records\n";
    std::cout << "2. View a Specific Pet Record\n";
    std::cout << "0. Back\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a valid choice." << std::endl;
        clearInput();  // Clear invalid input
        return;
    }

    // Handle the user choice
    switch (choice) {
        case 1: {
            view.viewAllPets(pathToFile);
            break;
        }
        case 2: {
            // Display a specific record
            std::string identifier;
            std::cout << "Enter Pet Name: ";
            std::cin >> identifier;
            
            view.viewIndividual(identifier, pathToFile);
            break;
        }
        case 0:
            std::cout << "Returning to previous menu...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void addPetRecord(){
    std::string name;
    std::string ownerUsername;
    std::string appointmentsHistory = "None"; 
    std::string DOB;
    std::string breed;

    std::cout << "\n--- Add Pet Record ---\n";

    // Get Appointment ID
    std::cout << "Enter Pet Name: ";
    while (!(std::cin >> name)) {
        std::cout << "Invalid input. Please eneter a valid pet name: ";
        clearInput();
    }

    if(checkForDuplicates(name, "Data/appointments")) {
        return;
    }
    clearInput();

    std::cout << "Enter Owner Username: ";
    std::getline(std::cin, ownerUsername);

    std::cout << "Enter DOB: ";
    std::getline(std::cin, DOB);

    std::cout << "Enter Breed: ";
    std::getline(std::cin, breed);

    Pet pet(name, ownerUsername, appointmentsHistory, DOB, breed);
};

void updatePetRecord(){

    std::string petName;
    std::string filePath = "Data/pets.txt";

    std::cout << "\n--- Update Pet Record ---\n";
    std::cout << "Please enter the Pet's name you want to modify: ";

    // Input validation for the Appointment ID
    while (!(std::cin >> petName)) {
        std::cout << "Invalid input. ";
        std::cin.clear();  // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
    }

    update.updatePet(petName, filePath);

    std::cout << "Appointment with name: " << petName << " has been successfully modified!" << std::endl;

}

void removePetRecord(){
    std::cout << "\n--- Delete Pet Record ---\n";

    std::string identifier;
    std::string fileName = "Data/pets.txt";
    std::string entryType = "Pet";

    std::cout << "Please enter pet name you would like to delete:";
    std::cin >> identifier;

    if (identifier.empty()) {
        std::cout << "Invalid input. Please enter a valid pet name." << std::endl;
        return;
    }

    deleteInstance.deleteEntry(identifier, fileName, entryType);
}

// limited acess funcitons for the Guest

void viewOwnerRecordsLimitedAccess(){
    view.viewIndividual(loggedInUser, "Data/owner.txt");  // adjust path if different
}

void viewPetRecordsLimitedAccess(){
    std::string petName;
    std::cout << "Enter the your pet's name: ";
    std::cin >> petName;

    View view;
    view.viewIndividual(petName, "Data/pets.txt"); 
}

void viewAppointmentLimitedAcess(){
    int identifier;
    std::cout << "Enter Appointment ID: ";
    std::cin >> identifier;
    
    view.viewIndividualAppointment(identifier, "Data/appointments.txt");
}
