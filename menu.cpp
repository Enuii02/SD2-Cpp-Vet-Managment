#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include "features.h"
#include "profiles.h"
#include "menu.h"

using namespace std;

//-------------------------------------------------
// Forward Declarations
//-------------------------------------------------
void clearInput();
bool isValidPhoneNumber(const string &phone);
void ensureFileExists(const string& filename);

void createNewAccount();
void alreadyHaveAccount();

bool checkCredentials(const string& username, const string& password, const string& filename, const string& expectedRole);
bool loginUser(const string& expectedRole);
void loginMenu();
void signUpMenu();
void mainMenu();

void adminMenu();
void adminAppointmentManagementMenu();
void adminOwnerManagementMenu();
void adminPetManagementMenu();
void adminSystemManagementMenu();

void staffMenu();
void staffAppointmentManagementMenu();

void veterinaryMenu();
void veterinaryAppointmentManagementMenu();
void veterinaryOwnerManagementMenu();

void guestMenu();

void addOwner();  // Forward declaration added for addOwner()

void scheduleAppointment();
void modifyAppointment();
void cancelAppointment();
void viewAppointmentRecordsFullAcess();

//-------------------------------------------------
// Helper Function Definitions
//-------------------------------------------------

// Clears the input stream error state and ignores the rest of the input line.
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Checks if a given phone number string consists solely of digits.
// Returns true if valid (or empty if optional), false otherwise.
bool isValidPhoneNumber(const string &phone) {
    if (phone.empty()) return true; // Allow empty phone number if optional.
    return all_of(phone.begin(), phone.end(), ::isdigit);
}

// Ensures that a file exists (creates it if it doesn't).
void ensureFileExists(const string& filename) {
    ofstream ofs(filename, ios::app);
    ofs.close();
}

//-----------------------------
// Account Management Functions
//-----------------------------
void createNewAccount() {
    string fullName, email, phone, username, password, confirmPassword;
    int accountTypeChoice;
    cout << "\n--- Create New Account ---" << endl;

    cout << "Enter Full Name: ";
    getline(cin, fullName);

    cout << "Enter Email Address: ";
    getline(cin, email);

    // Validate phone number input: only digits allowed.
    bool validPhone = false;
    while (!validPhone) {
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        if (isValidPhoneNumber(phone)) {
            validPhone = true;
        } else {
            cout << "Invalid input. Phone number must contain only digits." << endl;
        }
    }

    cout << "Choose Username: ";
    getline(cin, username);

    cout << "Choose Password: ";
    getline(cin, password);

    cout << "Confirm Password: ";
    getline(cin, confirmPassword);

    if (password != confirmPassword) {
        cout << "Passwords do not match. Account creation failed." << endl;
        return;
    }

    cout << "\nChoose Account Type:" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Staff (Admin/Staff/Veterinary)" << endl;
    cout << "Enter your choice: ";
    cin >> accountTypeChoice;
    clearInput();

    if (accountTypeChoice == 1) {
        string extraInfo = fullName + "," + email + "," + phone;
        if (!checkForDuplicates(username, "Data/owner.txt")) {
            ofstream outfile("Data/owner.txt", ios::app);
            outfile << username << "," << password << "," << extraInfo << "\n";
            outfile.close();
            cout << "Guest account created successfully!" << endl;
        } else {
            cout << "Account already exists. Please login." << endl;
        }
    }
    else if (accountTypeChoice == 2) {
        int roleChoice;
        string role;
        cout << "Select Role:" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Veterinary" << endl;
        cout << "Enter your choice: ";
        cin >> roleChoice;
        clearInput();
        switch (roleChoice) {
            case 1: role = "Admin"; break;
            case 2: role = "Staff"; break;
            case 3: role = "Veterinary"; break;
            default:
                cout << "Invalid role choice. Account creation failed." << endl;
                return;
        }
        if (!checkForDuplicates(username, "Data/staffacc.txt")) {
            ofstream outfile("Data/staffacc.txt", ios::app);
            outfile << username << "," << password << "," << role << "\n";
            outfile.close();
            cout << role << " account created successfully!" << endl;
        } else {
            cout << "Account already exists. Please login." << endl;
        }
    }
    else {
        cout << "Invalid account type choice. Account creation failed." << endl;
    }
}

void alreadyHaveAccount() {
    cout << "\nRedirecting to Login Menu..." << endl;
    loginMenu();
}

//-----------------------------
// Login Functions and Menus
//-----------------------------
bool checkCredentials(const string& username, const string& password, const string& filename, const string& expectedRole) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }
    string line;
    while (getline(infile, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string fileUsername, filePassword, fileRole;
        getline(ss, fileUsername, ',');
        if (fileUsername != username)
            continue;
        getline(ss, fileRole, ',');
        getline(ss, filePassword, ',');
        if (fileUsername == username && filePassword == password) {
            if (expectedRole == "guest" || fileRole == expectedRole)
                return true;
        }
    }
    return false;
}

bool loginUser(const string& expectedRole) {
    string filename = (expectedRole == "guest") ? "Data/owner.txt" : "Data/staffacc.txt";
    ensureFileExists(filename);
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (checkCredentials(username, password, filename, expectedRole)) {
        cout << "Login successful as " << expectedRole << "!" << endl;
        return true;
    }
    else {
        cout << "Login failed. Invalid credentials." << endl;
        return false;
    }
}

void loginMenu() {
    int choice;
    do {
        cout << "\n=== Login Menu ===" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Veterinary" << endl;
        cout << "4. Guest" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: if (loginUser("admin")) adminMenu(); break;
            case 2: if (loginUser("staff")) staffMenu(); break;
            case 3: if (loginUser("veterinary")) veterinaryMenu(); break;
            case 4: if (loginUser("guest")) guestMenu(); break;
            case 0: cout << "Returning to Main Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void signUpMenu() {
    int choice;
    do {
        cout << "\n=== Sign Up Menu ===" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Already Have an Account?" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: createNewAccount(); break;
            case 2: alreadyHaveAccount(); break;
            case 0: cout << "Returning to Main Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void mainMenu() {
    int choice;
    do {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: loginMenu(); break;
            case 2: signUpMenu(); break;
            case 3: cout << "Exiting program. Goodbye!" << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 3);
}

//-----------------------------
// Admin Menus
//-----------------------------
void adminMenu() {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Appointment Management" << endl;
        cout << "2. Owner Management" << endl;
        cout << "3. Pet Management" << endl;
        cout << "4. System Management" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: adminAppointmentManagementMenu(); break;
            case 2: adminOwnerManagementMenu(); break;
            case 3: adminPetManagementMenu(); break;
            case 4: adminSystemManagementMenu(); break;
            case 0: cout << "Logging out of Admin account..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void adminAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Appointment Management ---" << endl;
        cout << "1. Schedule Appointment" << endl;
        cout << "2. Modify Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "4. View Appointment Records" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess(); break;
            case 0: cout << "Returning to Admin Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void adminOwnerManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Owner Management ---" << endl;
        cout << "1. View Owner Records" << endl;
        cout << "2. Add Owner" << endl;
        cout << "3. Update Owner Details" << endl;
        cout << "4. Remove Owner" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: viewOwnerRecords(); break;
            case 2: addOwner(); break;
            case 3: updateOwner(); break;
            case 4: removeOwner(); break;
            case 0: adminOwnerManagement(); break;
            default: std::cout << "Invalid choice, try again." << std::endl;
        }
    } while (choice != 0);
}

void adminPetManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Pet Management ---" << endl;
        cout << "1. View Pet Records" << endl;
        cout << "2. Add Pet" << endl;
        cout << "3. Update Pet Details" << endl;
        cout << "4. Remove Pet" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: cout << "Redirecting to View Pet Records..." << endl; break;
            case 2: cout << "Redirecting to Add Pet..." << endl; break;
            case 3: cout << "Redirecting to Update Pet Details..." << endl; break;
            case 4: cout << "Redirecting to Remove Pet..." << endl; break;
            case 0: cout << "Returning to Admin Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void adminSystemManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin System Management ---" << endl;
        cout << "1. Save Data" << endl;
        cout << "2. Load Data" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
            case 1: cout << "Redirecting to Save Data..." << endl; break;
            case 2: cout << "Redirecting to Load Data..." << endl; break;
            case 0: cout << "Returning to Admin Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

//-----------------------------
// Staff Menus
//-----------------------------
void staffMenu() {
    int choice;
    do {
        cout << "\n=== Staff Menu ===" << endl;
        cout << "1. Appointment Management" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: staffAppointmentManagementMenu(); break;
            case 0: cout << "Logging out of Staff account..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void staffAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Staff Appointment Management ---" << endl;
        cout << "1. Schedule Appointment" << endl;
        cout << "2. Modify Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "4. View Appointment Records" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess(); break;
            case 0: cout << "Returning to Staff Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while(choice != 0);
}

//-----------------------------
// Veterinary Menus
//-----------------------------
void veterinaryMenu() {
    int choice;
    do {
        cout << "\n=== Veterinary Menu ===" << endl;
        cout << "1. Appointment Management" << endl;
        cout << "2. Owner Management" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: veterinaryAppointmentManagementMenu(); break;
            case 2: veterinaryOwnerManagementMenu(); break;
            case 0: cout << "Logging out of Veterinary account..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while(choice != 0);
}

void veterinaryAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Veterinary Appointment Management ---" << endl;
        cout << "1. Schedule Appointment" << endl;
        cout << "2. Modify Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "4. View Appointment Records" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: scheduleAppointment(); break;
            case 2: modifyAppointment(); break;
            case 3: cancelAppointment(); break;
            case 4: viewAppointmentRecordsFullAcess(); break;
            case 0: cout << "Returning to Veterinary Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while(choice != 0);
}

void veterinaryOwnerManagementMenu() {
    int choice;
    do {
        cout << "\n--- Veterinary Owner Management ---" << endl;
        cout << "1. View Owner Records" << endl;
        cout << "2. Update Owner Details" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: cout << "Redirecting to View Owner Records..." << endl; break;
            case 2: cout << "Redirecting to Update Owner Details..." << endl; break;
            case 0: cout << "Returning to Veterinary Menu..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while(choice != 0);
}

//-----------------------------
// Guest Menu
//-----------------------------
void guestMenu() {
    int choice;
    do {
        cout << "\n=== Guest Menu ===" << endl;
        cout << "1. View Pet Records" << endl;
        cout << "2. View Owner Records" << endl;
        cout << "3. View Appointment Records" << endl;
        cout << "0. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()){
            cout << "Invalid input." << endl;
            clearInput();
            continue;
        }
        clearInput();
        switch(choice) {
            case 1: cout << "Redirecting to View Pet Records..." << endl; break;
            case 2: cout << "Redirecting to View Owner Records..." << endl; break;
            case 3: cout << "Redirecting to View Appointment Records..." << endl; break;
            case 0: cout << "Logging out of Guest account..." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while(choice != 0);
}

//-----------------------------
// Appointment Operations (linked to features)
//-----------------------------
void scheduleAppointment() {
    int appointmentID;
    string petName, ownerUsername, appointmentDate, appointmentDescription;
    cout << "\n--- Schedule Appointment ---" << endl;
    cout << "Enter Appointment ID (integer): ";
    while (!(cin >> appointmentID)) {
        cout << "Invalid input. Please enter a valid integer for Appointment ID: ";
        clearInput();
    }
    clearInput();
    string stringID = to_string(appointmentID);
    if (checkForDuplicates(stringID, "Data/appointments.txt")) {
        return;
    }
    cout << "Enter Pet Name: ";
    getline(cin, petName);
    cout << "Enter Owner Username: ";
    getline(cin, ownerUsername);
    cout << "Enter Appointment Date (e.g., 2025-04-12): ";
    getline(cin, appointmentDate);
    cout << "Enter Appointment Description: ";
    getline(cin, appointmentDescription);

    // Creating an Appointment object (constructor auto-saves data)
    Appointment appointment(appointmentID, petName, ownerUsername, appointmentDate, appointmentDescription);
}

void modifyAppointment() {
    int appointmentID;
    string filePath = "Data/appointments.txt";
    cout << "\n--- Modify Appointment ---" << endl;
    cout << "Please enter the Appointment ID of the appointment you want to modify: ";
    while (!(cin >> appointmentID)) {
        cout << "Invalid input. Please enter a valid integer for Appointment ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    clearInput();
    Update update;
    update.updateAppointment(appointmentID, filePath);
    cout << "Appointment with ID " << appointmentID << " has been successfully modified!" << endl;
}

void cancelAppointment() {
    cout << "\n--- Delete Appointment ---" << endl;
    string identifier;
    string fileName = "Data/appointments.txt";
    string entryType = "Appointment";
    cout << "Please enter the appointment ID you would like to delete: ";
    cin >> identifier;
    clearInput();
    if (identifier.empty()) {
        cout << "Invalid input. Please enter a valid appointment ID." << endl;
        return;
    }
    Delete deleteInstance;
    deleteInstance.deleteEntry(identifier, fileName, entryType);
}

void viewAppointmentRecordsFullAcess() {
    int choice;
    string pathToFile = "Data/appointments.txt";
    cout << "\n--- View Appointment Records ---" << endl;
    cout << "1. View All Appointment Records" << endl;
    cout << "2. View a Specific Appointment Record" << endl;
    cout << "0. Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (cin.fail()) {
        cout << "Invalid input. Please enter a valid choice." << endl;
        clearInput();
        return;
    }
    clearInput();
    switch (choice) {
        case 1: {
            View view;
            view.viewAllAppointments(pathToFile);
            break;
        }
        case 2: {
            int identifier;
            cout << "Enter Appointment ID: ";
            cin >> identifier;
            clearInput();
            View view;
            view.viewIndividualAppointment(identifier, pathToFile);
            break;
        }
        case 0:
            cout << "Returning to previous menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

//-----------------------------
// Additional Functions
//-----------------------------
void addOwner() {
    string uname, role = "owner", pwd, fname, mail, phone;

    cout << "Enter new owner's username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pwd;
    cout << "Enter full name: ";
    cin.ignore(); // flush newline
    getline(cin, fname);
    cout << "Enter email: ";
    cin >> mail;

    // Validate phone number input: only digits allowed.
    bool validPhone = false;
    while (!validPhone) {
        cout << "Enter phone number (digits only): ";
        cin >> phone;
        if (isValidPhoneNumber(phone)) {
            validPhone = true;
        } else {
            cout << "Invalid input. Only digits allowed. Please re-enter." << endl;
        }
    }
    clearInput();

    Save save;
    save.saveUser(uname, role, pwd, fname, mail, phone);
    cout << "Owner profile added successfully." << endl;
}
