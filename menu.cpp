//-------------------------------------------------
// IMPROTANT! This is commented out of main and 
// shouldn't be used until we make the base classes.
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include "features.h"
#include "menu.h"

using namespace std;

//-------------------------------------------------
// Utility Functions
//-------------------------------------------------

// Clear input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Ensure that a file exists (if not, create an empty file)
void ensureFileExists(const string& filename) {
    ofstream ofs(filename, ios::app);
    ofs.close();
}

//-------------------------------------------------
// Account Handling Functions
//-------------------------------------------------

// For staff accounts, records are stored in: username,password,role
// For guest accounts, records are stored in: username,password,fullName,email,phone

// Check credentials: returns true if username and password match the expected role.
// expectedRole for guest should be "Guest"; for others, exactly "Admin", "Staff", or "Veterinary".
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
        getline(ss, filePassword, ',');
        getline(ss, fileRole, ','); // For guest accounts, fileRole holds fullName (extra info)
        if (fileUsername == username && filePassword == password) {
            if (expectedRole == "Guest") {
                // For guest, we assume the record is valid.
                return true;
            }
            if (fileRole == expectedRole)
                return true;
        }
    }
    return false;
}

// Create account and save it to a file. For staff, record: username,password,role.
// For guest, record: username,password,fullName,email,phone.
bool createAccount(const string& username, const string& password, const string& role, const string& extraInfo, const string& filename) {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cout << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }
    if (role == "Guest") {
        outfile << username << "," << password << "," << extraInfo << "\n";
    }
    else {
        outfile << username << "," << password << "," << role << "\n";
    }
    outfile.close();
    return true;
}

// Prompt user for username and password and check credentials based on expectedRole.
// Returns true if login is successful.
bool loginUser(const string& expectedRole) {
    string filename;
    if (expectedRole == "Guest")
        filename = "owner.txt";
    else
        filename = "staffacc.txt";

    ensureFileExists(filename);

    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    if (checkCredentials(username, password, filename, expectedRole)) {
        cout << "Login successful as " << expectedRole << "!\n";
        return true;
    }
    else {
        cout << "Login failed. Invalid credentials.\n";
        return false;
    }
}

//-------------------------------------------------
// Main Menu
//-------------------------------------------------

void mainMenu() {
    int choice;
    do {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Login [1]\n";
        cout << "2. Sign Up [2]\n";
        cout << "3. Exit [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
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
        case 3:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 3);
}

//-------------------------------------------------
// Login Menu
//-------------------------------------------------

void loginMenu() {
    int choice;
    do {
        cout << "\n=== Login Menu ===\n";
        cout << "1. Admin [1]\n";
        cout << "2. Staff [2]\n";
        cout << "3. Veterinary [3]\n";
        cout << "4. Guest [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
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
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Sign Up Menu
//-------------------------------------------------

void signUpMenu() {
    int choice;
    do {
        cout << "\n=== Sign Up Menu ===\n";
        cout << "1. Create New Account [1]\n";
        cout << "2. Already Have an Account? [2]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            createNewAccount();
            break;
        case 2:
            alreadyHaveAccount();
            break;
        case 0:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Sign Up Process Functions
//-------------------------------------------------

void createNewAccount() {
    cout << "\n--- Create New Account ---\n";
    string fullName, email, phone, username, password, confirmPassword;
    int accountTypeChoice;

    // Enter personal details
    cout << "Enter Full Name: ";
    getline(cin, fullName);
    cout << "Enter Email Address: ";
    getline(cin, email);
    cout << "Enter Phone Number (optional): ";
    getline(cin, phone);

    // Enter login credentials
    cout << "Choose Username: ";
    getline(cin, username);
    cout << "Choose Password: ";
    getline(cin, password);
    cout << "Confirm Password: ";
    getline(cin, confirmPassword);

    if (password != confirmPassword) {
        cout << "Passwords do not match. Account creation failed.\n";
        return;
    }

    cout << "\nChoose Account Type:\n";
    cout << "1. Guest [1]\n";
    cout << "2. Staff (Admin/Staff/Veterinary) [2]\n";
    cout << "Enter your choice: ";
    cin >> accountTypeChoice;
    clearInput();

    if (accountTypeChoice == 1) {
        // Guest account saved in owner.txt; extra info: fullName,email,phone
        string extraInfo = fullName + "," + email + "," + phone;
        if (createAccount(username, password, "Guest", extraInfo, "owner.txt"))
            cout << "Guest account created successfully!\n";
        else
            cout << "Failed to create account.\n";
    }
    else if (accountTypeChoice == 2) {
        // Let the user choose among Admin, Staff, or Veterinary.
        int roleChoice;
        string role;
        cout << "Select Role:\n";
        cout << "1. Admin [1]\n";
        cout << "2. Staff [2]\n";
        cout << "3. Veterinary [3]\n";
        cout << "Enter your choice: ";
        cin >> roleChoice;
        clearInput();
        switch (roleChoice) {
        case 1: role = "Admin"; break;
        case 2: role = "Staff"; break;
        case 3: role = "Veterinary"; break;
        default:
            cout << "Invalid role choice. Account creation failed.\n";
            return;
        }
        if (createAccount(username, password, role, "", "staffacc.txt"))
            cout << role << " account created successfully!\n";
        else
            cout << "Failed to create account.\n";
    }
    else {
        cout << "Invalid account type choice. Account creation failed.\n";
    }
}

void alreadyHaveAccount() {
    cout << "\nRedirecting to Login Menu...\n";
    loginMenu();
}

//-------------------------------------------------
// Admin Menu and Submenus
//-------------------------------------------------

void adminMenu() {
    int choice;
    do {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Appointment Management\n";
        cout << "2. Owner Management\n";
        cout << "3. Pet Management\n";
        cout << "4. System Management\n";
        cout << "0. Logout [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
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
            cout << "Logging out of Admin account...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Appointment Management ---\n";
        cout << "1. Schedule Appointment [1]\n";
        cout << "2. Modify Appointment [2]\n";
        cout << "3. Cancel Appointment [3]\n";
        cout << "4. View Appointment Records [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Scheduling Appointment (Admin)...\n";
            break;
        case 2:
            cout << "Modifying Appointment (Admin)...\n";
            break;
        case 3:
            cout << "Cancelling Appointment (Admin)...\n";
            break;
        case 4:
            cout << "Viewing Appointment Records (Admin)...\n";
            break;
        case 0:
            cout << "Returning to Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminOwnerManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Owner Management ---\n";
        cout << "1. View Owner Records [1]\n";
        cout << "2. Add Owner [2]\n";
        cout << "3. Update Owner Details [3]\n";
        cout << "4. Remove Owner [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Viewing Owner Records (Admin)...\n";
            {
                ifstream infile("owner.txt");
                string line;
                while (getline(infile, line)) {
                    if (!line.empty())
                        cout << line << "\n";
                }
            }
            break;
        case 2:
            cout << "Adding Owner (Admin)...\n";
            // You could implement adding an owner similar to creating a guest account.
            break;
        case 3:
            cout << "Updating Owner Details (Admin)...\n";
            break;
        case 4:
            cout << "Removing Owner (Admin)...\n";
            break;
        case 0:
            cout << "Returning to Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminPetManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin Pet Management ---\n";
        cout << "1. View Pet Records [1]\n";
        cout << "2. Add Pet [2]\n";
        cout << "3. Update Pet Details [3]\n";
        cout << "4. Remove Pet [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Viewing Pet Records (Admin)...\n";
            // Implement reading pet records from file if available.
            break;
        case 2:
            cout << "Adding Pet (Admin)...\n";
            break;
        case 3:
            cout << "Updating Pet Details (Admin)...\n";
            break;
        case 4:
            cout << "Removing Pet (Admin)...\n";
            break;
        case 0:
            cout << "Returning to Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void adminSystemManagementMenu() {
    int choice;
    do {
        cout << "\n--- Admin System Management ---\n";
        cout << "1. Save Data [1]\n";
        cout << "2. Load Data [2]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Saving Data (Admin)...\n";
            // Implement data saving functionality.
            break;
        case 2:
            cout << "Loading Data (Admin)...\n";
            // Implement data loading functionality.
            break;
        case 0:
            cout << "Returning to Admin Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Staff Menu and Submenu
//-------------------------------------------------

void staffMenu() {
    int choice;
    do {
        cout << "\n=== Staff Menu ===\n";
        cout << "1. Appointment Management\n";
        cout << "0. Logout [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            staffAppointmentManagementMenu();
            break;
        case 0:
            cout << "Logging out of Staff account...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void staffAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Staff Appointment Management ---\n";
        cout << "1. Schedule Appointment [1]\n";
        cout << "2. Modify Appointment [2]\n";
        cout << "3. Cancel Appointment [3]\n";
        cout << "4. View Appointment Records [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Scheduling Appointment (Staff)...\n";
            break;
        case 2:
            cout << "Modifying Appointment (Staff)...\n";
            break;
        case 3:
            cout << "Cancelling Appointment (Staff)...\n";
            break;
        case 4:
            cout << "Viewing Appointment Records (Staff)...\n";
            break;
        case 0:
            cout << "Returning to Staff Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Veterinary Menu and Submenus
//-------------------------------------------------

void veterinaryMenu() {
    int choice;
    do {
        cout << "\n=== Veterinary Menu ===\n";
        cout << "1. Appointment Management\n";
        cout << "2. Owner Management\n";
        cout << "0. Logout [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
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
            cout << "Logging out of Veterinary account...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void veterinaryAppointmentManagementMenu() {
    int choice;
    do {
        cout << "\n--- Veterinary Appointment Management ---\n";
        cout << "1. Schedule Appointment [1]\n";
        cout << "2. Modify Appointment [2]\n";
        cout << "3. Cancel Appointment [3]\n";
        cout << "4. View Appointment Records [4]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Scheduling Appointment (Veterinary)...\n";
            break;
        case 2:
            cout << "Modifying Appointment (Veterinary)...\n";
            break;
        case 3:
            cout << "Cancelling Appointment (Veterinary)...\n";
            break;
        case 4:
            cout << "Viewing Appointment Records (Veterinary)...\n";
            break;
        case 0:
            cout << "Returning to Veterinary Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

void veterinaryOwnerManagementMenu() {
    int choice;
    do {
        cout << "\n--- Veterinary Owner Management ---\n";
        cout << "1. View Owner Records [1]\n";
        cout << "2. Update Owner Details [2]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Viewing Owner Records (Veterinary)...\n";
            {
                ifstream infile("owner.txt");
                string line;
                while (getline(infile, line)) {
                    if (!line.empty())
                        cout << line << "\n";
                }
            }
            break;
        case 2:
            cout << "Updating Owner Details (Veterinary)...\n";
            break;
        case 0:
            cout << "Returning to Veterinary Menu...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}

//-------------------------------------------------
// Guest Menu
//-------------------------------------------------

void guestMenu() {
    int choice;
    do {
        cout << "\n=== Guest Menu ===\n";
        cout << "1. View Pet Records [1]\n";
        cout << "2. View Owner Records [2]\n";
        cout << "3. View Appointment Records [3]\n";
        cout << "0. Logout [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input.\n";
            clearInput();
            continue;
        }
        clearInput();
        switch (choice) {
        case 1:
            cout << "Viewing Pet Records (Guest)...\n";
            // Implement reading pet records from file if available.
            break;
        case 2:
            cout << "Viewing Owner Records (Guest)...\n";
            {
                ifstream infile("owner.txt");
                string line;
                while (getline(infile, line)) {
                    if (!line.empty())
                        cout << line << "\n";
                }
            }
            break;
        case 3:
            cout << "Viewing Appointment Records (Guest)...\n";
            break;
        case 0:
            cout << "Logging out of Guest account...\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);
}
