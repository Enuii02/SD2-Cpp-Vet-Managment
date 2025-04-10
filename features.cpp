#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"features.h"

using namespace std;

        #include <iostream>
        #include <fstream>
        #include <string>
        #include <sstream>
        #include <vector>
        #include "features.h"
        
        using namespace std;
        
        //-------------------------------------------------
        // View section
        //-------------------------------------------------
        
        void View::viewIndividual(string name, string fileName) {
            vector<string> details;
            string line, token;
            ifstream MyReadFile(fileName);
            if (!MyReadFile.is_open()) {
                cerr << "Failed to open file: " << fileName << endl;
                return;
            }
        
            while (getline(MyReadFile, line)) {
                details.clear();
                stringstream ss(line);
        
                while (getline(ss, token, ',')) {
                    details.push_back(token);
                }
        
        /*
        These can be easly adjusted if we change the formats
        the users.
        */

        // details[0] = username
        // details[1] = role
        // details[2] = password
        // details[3] = full name
        // details[4] = email
        // details[5] = phone
    
                // Check if it is a user/staff record.
                if (!details.empty() && details[0] == name && details.size() == 6) {
                    cout << "========================================" << endl;
                    cout << "Details for " << name << ":" << endl;
                    cout << "Username: " << details[0] << endl;
                    cout << "Role: " << details[1] << endl;
                    cout << "Password: " << details[2] << endl;
                    cout << "Full Name: " << details[3] << endl;
                    cout << "Email: " << details[4] << endl;
                    cout << "Phone Number: " << details[5] << endl;
                    cout << "========================================" << endl;
                }
                // Check if it is a pet record (assuming fileName is "pets.txt")
                else if (!details.empty() && details[0] == name && fileName == "pets.txt") {
                    cout << "Details for " << name << ":" << endl;
                    cout << "Name: " << details[0] << endl;
                    cout << "Owner Username: " << details[1] << endl;
                    cout << "Appointment History: " << details[2] << endl;
                    cout << "DOB: " << details[3] << endl;
                    cout << "Breed: " << details[4] << endl;
                }
            
                cout << "Info from: " << fileName << endl;
            }
            MyReadFile.close();
        }
        
        void View::viewAllUsers(string fileName) {
            ifstream MyReadFile(fileName);
            string output;
        
            cout << "== Displaying: " << fileName << " ==" << endl;
            cout << "Format: username, role, password, full name, email, phone number" << endl << endl;
            while (getline(MyReadFile, output)) {
                cout << output << endl;
            }
        }
        
        void View::viewAllPets(string fileName) {
            ifstream MyReadFile(fileName);
            string output;
        
            cout << "== Displaying: " << fileName << " ==" << endl;
            cout << "Format: name, ownerUsername, appointmentsHistory, DOB, breed" << endl << endl;
            while (getline(MyReadFile, output)) {
                cout << output << endl;
            }
        }
        
        //-------------------------------------------------
        // New: Appointment View section
        //-------------------------------------------------
        
        // View an individual appointment by appointmentID
        void View::viewIndividualAppointment(int appointmentID, string fileName) {
            ifstream inFile(fileName);
            if (!inFile.is_open()) {
                cerr << "Failed to open file: " << fileName << endl;
                return;
            }
            
            string line;
            bool found = false;
            while (getline(inFile, line)) {
                vector<string> details;
                string token;
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    details.push_back(token);
                }
                
                // Check if details are valid and if the first token matches appointmentID
                if (!details.empty() && details.size() >= 5) {
                    try {
                        int currentID = stoi(details[0]);
                        if (currentID == appointmentID) {
                            cout << "========================================" << endl;
                            cout << "Appointment Details for ID: " << appointmentID << endl;
                            cout << "Appointment ID: " << details[0] << endl;
                            cout << "Pet Name: " << details[1] << endl;
                            cout << "Owner Username: " << details[2] << endl;
                            cout << "Appointment Date: " << details[3] << endl;
                            cout << "Description: " << details[4] << endl;
                            cout << "========================================" << endl;
                            found = true;
                            break;
                        }
                    } catch (const std::exception& e) {
                        cerr << "Error processing appointment ID: " << e.what() << endl;
                        continue;
                    }
                }
            }
            if (!found) {
                cout << "Appointment with ID " << appointmentID << " not found in " << fileName << "." << endl;
            }
            inFile.close();
        }
        
        // View all appointments from a given file
        void View::viewAllAppointments(string fileName) {
            ifstream inFile(fileName);
            if (!inFile.is_open()) {
                cerr << "Failed to open file: " << fileName << endl;
                return;
            }
            
            cout << "== Displaying all appointments from " << fileName << " ==" << endl;
            cout << "Format: appointmentID, petName, ownerUsername, appointmentDate, description" << endl << endl;
            string output;
            while (getline(inFile, output)) {
                cout << output << endl;
            }
            inFile.close();
        }
        
        //-------------------------------------------------
        // Save section
        //-------------------------------------------------
        
        void Save::saveUser(string uname, string r, string pwd, 
                            string fname, string mail, string phone) {
            string pathToFile;
            try {
                if (r == "admin" || r == "vet" || r == "staff" || r == "guest") {
                    pathToFile = "Data/staffacc.txt";
                } else if (r == "guest") {
                    pathToFile = "Data/owner.txt";
                } else {
                    throw "Error, no valid user role, select an appropriate role.";
                }
            } catch (const char* e) {
                cerr << e << '\n';
            }
        
            vector<string> details;
            string line, token;
            ifstream MyReadFile(pathToFile);
            if (!MyReadFile.is_open()) {
                cerr << "Failed to open file: " << pathToFile << endl;
                return;
            }
            
            // Check if the profile already exists in the database
            while (getline(MyReadFile, line)) {
                details.clear();
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    details.push_back(token);
                }
                if (!details.empty() && details[0] == uname) {
                    cout << "User already exists, please login!" << endl;
                    return;
                }
            }
            MyReadFile.close();
        
            // Save the file
            ofstream MyFile(pathToFile, ios::app);
            MyFile << uname << "," << r << "," << pwd << "," << fname << "," << mail << "," << phone << "\n";
            MyFile.close();
        }
        
        void Save::savePet(string name, string ownerUsername, string appointmentsHistory, 
                           string DOB, string breed) {
            string pathToFile = "Data/pets.txt";
            ofstream MyFile(pathToFile, ios::app);
            if (!MyFile.is_open()) {
                cerr << "Failed to open file: pets.txt" << endl;
                return;
            }
            MyFile << name << "," << ownerUsername << "," << appointmentsHistory << "," << DOB << "," << breed << "\n";
            MyFile.close();
        }
        
        void Save::saveAppointment(int appointmentID, string petName, string ownerUsername, 
                                   string appopintmentDate, string appointmentDescription) {
            ofstream MyFile("Data/appointments.txt", ios::app);
            if (!MyFile.is_open()) {
                cerr << "Failed to open file: appointments.txt" << endl;
                return;
            }
            MyFile << appointmentID << "," << petName << "," << ownerUsername << "," << appopintmentDate << "," << appointmentDescription << "\n";
            MyFile.close();
        }
        
        //-------------------------------------------------
        // Update section
        //-------------------------------------------------
        
        void Update::updateUser(string uname, string fileName) {
            vector<string> details;
            string line, token;
            ifstream MyReadFile(fileName);
            while (getline(MyReadFile, line)) {
                details.clear();
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    details.push_back(token);
                }
                if (!details.empty() && details[0] == uname && details.size() == 6) {
                    break;
                }
            }
            MyReadFile.close();
        
            string password = details[2];
            string userInputPassword;
            bool authenticated = false;
            for (int i = 3; i >= 0; i--) {
                cout << "Please enter password: ";
                cin >> userInputPassword;
                if (userInputPassword == password) {
                    cout << "Password accepted!" << endl;
                    authenticated = true;
                    break;
                } else {
                    cout << "Invalid password, please try again. \n [Tries left: " << i << "]" << endl;
                }
            }
            if (!authenticated) {
                cout << "You entered a wrong password too many times, try again later." << endl;
                return;
            }
        
            while (true) {
                int choice;
                cout << "\n--- What would you like to update in your profile? ---\n";
                cout << "1. Username [1]\n";
                cout << "2. Password [2]\n";
                cout << "3. Email [3]\n";
                cout << "4. Phone [4]\n";
                cout << "0. Back [0]\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1) {
                    string newUsername;
                    cout << "Enter new username: ";
                    cin >> newUsername;
                    details[0] = newUsername;
                    cout << "Username updated to " << newUsername << endl;
                    break;
                } else if (choice == 2) {
                    string newPassword;
                    cout << "Enter new password: ";
                    cin >> newPassword;
                    details[2] = newPassword;
                    cout << "Password updated." << endl;
                    break;
                } else if (choice == 3) {
                    string newEmail;
                    cout << "Enter new email: ";
                    cin >> newEmail;
                    details[4] = newEmail;
                    cout << "Email updated to " << newEmail << endl;
                    break;
                } else if (choice == 4) {
                    string newPhone;
                    cout << "Enter new phone number: ";
                    cin >> newPhone;
                    details[5] = newPhone;
                    cout << "Phone number updated to " << newPhone << endl;
                    break;
                } else if (choice == 0) {
                    cout << "Returning to previous menu..." << endl;
                    break;
                } else {
                    cout << "Invalid option selected. Please try again.\n";
                }
            }
        
            string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4] + "," + details[5];
            vector<string> allLines;
            ifstream inputFile(fileName);
            while (getline(inputFile, line)) {
                allLines.push_back(line);
            }
            inputFile.close();
        
            for (auto& l : allLines) {
                stringstream ss(l);
                string temp;
                getline(ss, temp, ',');
                if (temp == uname) {
                    l = updatedLine;
                    break;
                }
            }
        
            ofstream outputFile(fileName);
            for (const auto& l : allLines) {
                outputFile << l << '\n';
            }
            outputFile.close();
        
            cout << "Profile updated successfully." << endl;
        }
        
        void Update::updatePet(string petName, string fileName) {
            vector<string> details;
            string line, token;
            vector<string> allLines;
            bool found = false;
            ifstream inputFile(fileName);
            while (getline(inputFile, line)) {
                details.clear();
                stringstream ss(line);
                while (getline(ss, token, ',')) {
                    details.push_back(token);
                }
                if (!details.empty() && details[0] == petName && details.size() == 5) {
                    found = true;
                    break;
                }
                allLines.push_back(line);
            }
            inputFile.close();
        
            if (!found) {
                cout << "Pet not found." << endl;
                return;
            }
        
            cout << "\n--- Current Pet Info ---\n";
            cout << "Name: " << details[0] << endl;
            cout << "Owner Username: " << details[1] << endl;
            cout << "Appointment History: " << details[2] << endl;
            cout << "DOB: " << details[3] << endl;
            cout << "Breed: " << details[4] << endl;
        
            while (true) {
                int choice;
                cout << "\n--- What would you like to update? ---\n";
                cout << "1. Appointment History [1]\n";
                cout << "2. Date of Birth (DOB) [2]\n";
                cout << "3. Breed [3]\n";
                cout << "0. Back [0]\n";
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();
                if (choice == 1) {
                    string newHistory;
                    cout << "Enter new appointment history: ";
                    getline(cin, newHistory);
                    details[2] = newHistory;
                    cout << "Appointment history updated." << endl;
                    break;
                } else if (choice == 2) {
                    string newDOB;
                    cout << "Enter new date of birth (YYYY-MM-DD): ";
                    cin >> newDOB;
                    details[3] = newDOB;
                    cout << "DOB updated." << endl;
                    break;
                } else if (choice == 3) {
                    string newBreed;
                    cout << "Enter new breed: ";
                    cin >> newBreed;
                    details[4] = newBreed;
                    cout << "Breed updated." << endl;
                    break;
                } else if (choice == 0) {
                    cout << "Returning to previous menu..." << endl;
                    return;
                } else {
                    cout << "Invalid option, please try again." << endl;
                }
            }
        
            string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];
            allLines.push_back(updatedLine);
        
            ofstream outputFile(fileName);
            for (const auto& l : allLines) {
                outputFile << l << "\n";
            }
            outputFile.close();
        
            cout << "Pet profile updated successfully." << endl;
        }
        
        //-------------------------------------------------
        // Delete section
        //-------------------------------------------------
        
        void Delete::deleteProfile(string uname) {
            cout << "Deleting profile: " << uname;
        }
        
        void Delete::deletePet(const string& petName, const string& fileName) {
            ifstream inputFile(fileName);
            vector<string> allLines;
            string line;
            if (!inputFile.is_open()) {
                cerr << "Error opening file: " << fileName << endl;
                return;
            }
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ',');
                if (token != petName) {
                    allLines.push_back(line);
                } else {
                    cout << "Pet '" << petName << "' found and deleted." << endl;
                }
            }
            inputFile.close();
            ofstream outputFile(fileName);
            if (!outputFile.is_open()) {
                cerr << "Error writing to file: " << fileName << endl;
                return;
            }
            for (const string& l : allLines) {
                outputFile << l << '\n';
            }
            outputFile.close();
        }
        