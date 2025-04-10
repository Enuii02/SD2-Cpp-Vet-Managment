#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include "features.h"
#include "menu.h"

// Forward declarations for account functions now in features.cpp
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
// Account Handling and Login (Menu only redirects)
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
        std::getline(ss, fileRole, ','); // For guest, fileRole holds extra info.
        if (fileUsername == username && filePassword == password) {
            if (expectedRole == "Guest" || fileRole == expectedRole)
                return true;
        }
    }
    return false;
}

bool loginUser(const std::string& expectedRole) {
    std::string filename = (expectedRole == "Guest") ? "owner.txt" : "Data/staffacc.txt";
    ensureFileExists(filename);
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    if (checkCredentials(username, password, filename, expectedRole)) {
        std::cout << "Login successful as " << expectedRole << "!\n";
        return true;
    }
    else {
        std::cout << "Login failed. Invalid credentials.\n";
        return false;
    }
}

//-------------------------------------------------
// Main Menu
//-------------------------------------------------
void mainMenu() {
    int choice;
    do {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Login [1]\n";
        std::cout << "2. Sign Up [2]\n";
        std::cout << "3. Exit [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            loginMenu();
            break;
        case 2:
            signUpMenu();
            break;
        case 0:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Login Menu
//-------------------------------------------------
void loginMenu() {
    int choice;
    do {
        std::cout << "\n=== Login Menu ===\n";
        std::cout << "1. Admin [1]\n";
        std::cout << "2. Staff [2]\n";
        std::cout << "3. Veterinary [3]\n";
        std::cout << "4. Guest [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            if (loginUser("Admin"))
                adminMenu();
            break;
        case 2:
            if (loginUser("Staff"))
                staffMenu();
            break;
        case 3:
            if (loginUser("Veterinary"))
                veterinaryMenu();
            break;
        case 4:
            if (loginUser("Guest"))
                guestMenu();
            break;
        case 0:
            std::cout << "Returning to Main Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Sign Up Menu (Now simply redirects to Features functions)
//-------------------------------------------------
void signUpMenu() {
    int choice;
    do {
        std::cout << "\n=== Sign Up Menu ===\n";
        std::cout << "1. Create New Account [1]\n";
        std::cout << "2. Already Have an Account? [2]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            createNewAccount(); // call the function in features.cpp
            break;
        case 2:
            alreadyHaveAccount(); // call the function in features.cpp
            break;
        case 0:
            std::cout << "Returning to Main Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// The remaining menus (Admin, Staff, Veterinary, Guest)
// now only handle redirection without extra business logic.
//-------------------------------------------------

void adminMenu() {
    int choice;
    do {
        std::cout << "\n=== Admin Menu ===\n";
        std::cout << "1. Appointment Management [1]\n";
        std::cout << "2. Owner Management [2]\n";
        std::cout << "3. Pet Management [3]\n";
        std::cout << "4. System Management [4]\n";
        std::cout << "0. Logout [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            adminAppointmentManagementMenu();
            break;
        case 2:
            adminOwnerManagementMenu();
            break;
        case 3:
            adminPetManagementMenu();
            break;
        case 4:
            adminSystemManagementMenu();
            break;
        case 0:
            std::cout << "Logging out of Admin account...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Appointment Management ---\n";
        std::cout << "1. Schedule Appointment [1]\n";
        std::cout << "2. Modify Appointment [2]\n";
        std::cout << "3. Cancel Appointment [3]\n";
        std::cout << "4. View Appointment Records [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        // Each option should now simply call the corresponding function in features.cpp
        switch (choice) {
        case 1:
            std::cout << "Redirecting to Schedule Appointment (function in Features)...\n";
            // e.g. call a scheduling function from features if implemented.
            break;
        case 2:
            std::cout << "Redirecting to Modify Appointment (function in Features)...\n";
            break;
        case 3:
            std::cout << "Redirecting to Cancel Appointment (function in Features)...\n";
            break;
        case 4:
            std::cout << "Redirecting to View Appointment Records (using View functions)...\n";
            break;
        case 0:
            std::cout << "Returning to Admin Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminOwnerManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Owner Management ---\n";
        std::cout << "1. View Owner Records [1]\n";
        std::cout << "2. Add Owner [2]\n";
        std::cout << "3. Update Owner Details [3]\n";
        std::cout << "4. Remove Owner [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to View Owner Records...\n";
            break;
        case 2:
            std::cout << "Redirecting to Add Owner (function in Features)...\n";
            break;
        case 3:
            std::cout << "Redirecting to Update Owner Details (function in Features)...\n";
            break;
        case 4:
            std::cout << "Redirecting to Remove Owner (function in Features)...\n";
            break;
        case 0:
            std::cout << "Returning to Admin Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminPetManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Pet Management ---\n";
        std::cout << "1. View Pet Records [1]\n";
        std::cout << "2. Add Pet [2]\n";
        std::cout << "3. Update Pet Details [3]\n";
        std::cout << "4. Remove Pet [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to View Pet Records (using View functions)...\n";
            break;
        case 2:
            std::cout << "Redirecting to Add Pet (function in Features/Profiles)...\n";
            break;
        case 3:
            std::cout << "Redirecting to Update Pet Details (function in Features)...\n";
            break;
        case 4:
            std::cout << "Redirecting to Remove Pet (function in Features)...\n";
            break;
        case 0:
            std::cout << "Returning to Admin Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminSystemManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin System Management ---\n";
        std::cout << "1. Save Data [1]\n";
        std::cout << "2. Load Data [2]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to Save Data (function in Features)...\n";
            break;
        case 2:
            std::cout << "Redirecting to Load Data (function in Features)...\n";
            break;
        case 0:
            std::cout << "Returning to Admin Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void staffMenu() {
    int choice;
    do {
        std::cout << "\n=== Staff Menu ===\n";
        std::cout << "1. Appointment Management\n";
        std::cout << "0. Logout [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            staffAppointmentManagementMenu();
            break;
        case 0:
            std::cout << "Logging out of Staff account...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void staffAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Staff Appointment Management ---\n";
        std::cout << "1. Schedule Appointment [1]\n";
        std::cout << "2. Modify Appointment [2]\n";
        std::cout << "3. Cancel Appointment [3]\n";
        std::cout << "4. View Appointment Records [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to Schedule Appointment (function in Features)...\n";
            break;
        case 2:
            std::cout << "Redirecting to Modify Appointment (function in Features)...\n";
            break;
        case 3:
            std::cout << "Redirecting to Cancel Appointment (function in Features)...\n";
            break;
        case 4:
            std::cout << "Redirecting to View Appointment Records (using View functions)...\n";
            break;
        case 0:
            std::cout << "Returning to Staff Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void veterinaryMenu() {
    int choice;
    do {
        std::cout << "\n=== Veterinary Menu ===\n";
        std::cout << "1. Appointment Management\n";
        std::cout << "2. Owner Management\n";
        std::cout << "0. Logout [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            veterinaryAppointmentManagementMenu();
            break;
        case 2:
            veterinaryOwnerManagementMenu();
            break;
        case 0:
            std::cout << "Logging out of Veterinary account...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void veterinaryAppointmentManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Veterinary Appointment Management ---\n";
        std::cout << "1. Schedule Appointment [1]\n";
        std::cout << "2. Modify Appointment [2]\n";
        std::cout << "3. Cancel Appointment [3]\n";
        std::cout << "4. View Appointment Records [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to Schedule Appointment (function in Features)...\n";
            break;
        case 2:
            std::cout << "Redirecting to Modify Appointment (function in Features)...\n";
            break;
        case 3:
            std::cout << "Redirecting to Cancel Appointment (function in Features)...\n";
            break;
        case 4:
            std::cout << "Redirecting to View Appointment Records (using View functions)...\n";
            break;
        case 0:
            std::cout << "Returning to Veterinary Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void veterinaryOwnerManagementMenu() {
    int choice;
    do {
        std::cout << "\n--- Veterinary Owner Management ---\n";
        std::cout << "1. View Owner Records [1]\n";
        std::cout << "2. Update Owner Details [2]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to View Owner Records...\n";
            break;
        case 2:
            std::cout << "Redirecting to Update Owner Details (function in Features)...\n";
            break;
        case 0:
            std::cout << "Returning to Veterinary Menu...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void guestMenu() {
    int choice;
    do {
        std::cout << "\n=== Guest Menu ===\n";
        std::cout << "1. View Pet Records [1]\n";
        std::cout << "2. View Owner Records [2]\n";
        std::cout << "3. View Appointment Records [3]\n";
        std::cout << "0. Logout [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            std::cout << "Redirecting to View Pet Records (using View functions)...\n";
            break;
        case 2:
            std::cout << "Redirecting to View Owner Records...\n";
            break;
        case 3:
            std::cout << "Redirecting to View Appointment Records (using View functions)...\n";
            break;
        case 0:
            std::cout << "Logging out of Guest account...\n";
            break;
        default:
            std::cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}
