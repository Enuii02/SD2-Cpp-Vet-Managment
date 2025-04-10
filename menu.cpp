#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include "features.h"
#include "menu.h"

// Forward declarations for account functions in features.cpp
extern void createNewAccount();
extern void alreadyHaveAccount();

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
        std::string fileUsername, filePassword, fileRole;
        std::getline(ss, fileUsername, ',');
        std::getline(ss, filePassword, ',');
        std::getline(ss, fileRole, ','); // For guests, fileRole holds extra info.
        if (fileUsername == username && filePassword == password) {
            if (expectedRole == "Guest" || fileRole == expectedRole)
                return true;
        }
    }
    return false;
}

bool loginUser(const std::string& expectedRole) {
    std::string filename = (expectedRole == "Guest") ? "Data/owner.txt" : "Data/staffacc.txt";
    ensureFileExists(filename);
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    if (checkCredentials(username, password, filename, expectedRole)) {
        std::cout << "Login successful as " << expectedRole << "!" << std::endl;
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
            case 2: signUpMenu(); break;
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
            case 1: if (loginUser("Admin")) adminMenu(); break;
            case 2: if (loginUser("Staff")) staffMenu(); break;
            case 3: if (loginUser("Veterinary")) veterinaryMenu(); break;
            case 4: if (loginUser("Guest")) guestMenu(); break;
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
            case 0: std::cout << "Returning to Main Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

//-------------------------------------------------
// The following menus simply redirect to functions in features (or profiles)
//-------------------------------------------------

void adminMenu() {
    int choice;
    do {
        std::cout << "\n=== Admin Menu ===" << std::endl;
        std::cout << "1. Appointment Management" << std::endl;
        std::cout << "2. Owner Management" << std::endl;
        std::cout << "3. Pet Management" << std::endl;
        std::cout << "4. System Management" << std::endl;
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
            case 4: adminSystemManagementMenu(); break;
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
        // Here, simply redirect (actual functionality should be implemented in features)
        switch (choice) {
            case 1: std::cout << "Redirecting to Schedule Appointment..." << std::endl; break;
            case 2: std::cout << "Redirecting to Modify Appointment..." << std::endl; break;
            case 3: std::cout << "Redirecting to Cancel Appointment..." << std::endl; break;
            case 4: std::cout << "Redirecting to View Appointment Records..." << std::endl; break;
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
            case 1: std::cout << "Redirecting to View Owner Records..." << std::endl; break;
            case 2: std::cout << "Redirecting to Add Owner..." << std::endl; break;
            case 3: std::cout << "Redirecting to Update Owner Details..." << std::endl; break;
            case 4: std::cout << "Redirecting to Remove Owner..." << std::endl; break;
            case 0: std::cout << "Returning to Admin Menu..." << std::endl; break;
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
            case 1: std::cout << "Redirecting to View Pet Records..." << std::endl; break;
            case 2: std::cout << "Redirecting to Add Pet..." << std::endl; break;
            case 3: std::cout << "Redirecting to Update Pet Details..." << std::endl; break;
            case 4: std::cout << "Redirecting to Remove Pet..." << std::endl; break;
            case 0: std::cout << "Returning to Admin Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void adminSystemManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin System Management ---" << std::endl;
        std::cout << "1. Save Data" << std::endl;
        std::cout << "2. Load Data" << std::endl;
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
            case 1: std::cout << "Redirecting to Save Data..." << std::endl; break;
            case 2: std::cout << "Redirecting to Load Data..." << std::endl; break;
            case 0: std::cout << "Returning to Admin Menu..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void staffMenu() {
    int choice;
    do {
        std::cout << "\n=== Staff Menu ===" << std::endl;
        std::cout << "1. Appointment Management" << std::endl;
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
            case 0: std::cout << "Logging out of Staff account..." << std::endl; break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

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
            case 1: std::cout << "Redirecting to Schedule Appointment..." << std::endl; break;
            case 2: std::cout << "Redirecting to Modify Appointment..." << std::endl; break;
            case 3: std::cout << "Redirecting to Cancel Appointment..." << std::endl; break;
            case 4: std::cout << "Redirecting to View Appointment Records..." << std::endl; break;
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
            case 1: std::cout << "Redirecting to Schedule Appointment..." << std::endl; break;
            case 2: std::cout << "Redirecting to Modify Appointment..." << std::endl; break;
            case 3: std::cout << "Redirecting to Cancel Appointment..." << std::endl; break;
            case 4: std::cout << "Redirecting to View Appointment Records..." << std::endl; break;
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
            case 1: std::cout << "Redirecting to View Owner Records..." << std::endl; break;
            case 2: std::cout << "Redirecting to Update Owner Details..." << std::endl; break;
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
