#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "features.h"

//-------------------------------------------------
// View section
//-------------------------------------------------

void View::viewIndividual(std::string name, std::string fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    while (std::getline(inFile, line)) {
        details.clear();
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
            details.push_back(token);
        }
        // For a user record (6 fields)
        if (!details.empty() && details[0] == name && details.size() == 6) {
            std::cout << "========================================" << std::endl;
            std::cout << "Details for " << name << ":" << std::endl;
            std::cout << "Username: " << details[0] << std::endl;
            std::cout << "Role: " << details[1] << std::endl;
            std::cout << "Password: " << details[2] << std::endl;
            std::cout << "Full Name: " << details[3] << std::endl;
            std::cout << "Email: " << details[4] << std::endl;
            std::cout << "Phone Number: " << details[5] << std::endl;
            std::cout << "========================================" << std::endl;
        }
        // For a pet record (assumed file "pets.txt")
        else if (!details.empty() && details[0] == name && fileName == "Data/pets.txt") {
            std::cout << "Details for " << name << ":" << std::endl;
            std::cout << "Name: " << details[0] << std::endl;
            std::cout << "Owner Username: " << details[1] << std::endl;
            std::cout << "Appointment History: " << details[2] << std::endl;
            std::cout << "DOB: " << details[3] << std::endl;
            std::cout << "Breed: " << details[4] << std::endl;
        }
    }
    inFile.close();
}

void View::viewAllUsers(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string output;
    std::cout << "== Displaying: " << fileName << " ==" << std::endl;
    std::cout << "Format: username, role, password, full name, email, phone number" << std::endl << std::endl;
    while (std::getline(inFile, output)) {
        std::cout << output << std::endl;
    }
    inFile.close();
}

void View::viewAllPets(std::string fileName) {
    std::ifstream inFile(fileName);
    std::string output;
    std::cout << "== Displaying: " << fileName << " ==" << std::endl;
    std::cout << "Format: name, ownerUsername, appointmentsHistory, DOB, breed" << std::endl << std::endl;
    while (std::getline(inFile, output)) {
        std::cout << output << std::endl;
    }
    inFile.close();
}

void View::viewIndividualAppointment(int appointmentID, std::string fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        std::vector<std::string> details;
        std::string token;
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
            details.push_back(token);
        }
        if (!details.empty() && details.size() >= 5) {
            try {
                int currentID = std::stoi(details[0]);
                if (currentID == appointmentID) {
                    std::cout << "========================================" << std::endl;
                    std::cout << "Appointment Details for ID: " << appointmentID << std::endl;
                    std::cout << "Appointment ID: " << details[0] << std::endl;
                    std::cout << "Pet Name: " << details[1] << std::endl;
                    std::cout << "Owner Username: " << details[2] << std::endl;
                    std::cout << "Appointment Date: " << details[3] << std::endl;
                    std::cout << "Description: " << details[4] << std::endl;
                    std::cout << "========================================" << std::endl;
                    found = true;
                    break;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing appointment ID: " << e.what() << std::endl;
                continue;
            }
        }
    }
    if (!found) {
        std::cout << "Appointment with ID " << appointmentID << " not found in " << fileName << "." << std::endl;
    }
    inFile.close();
}

void View::viewAllAppointments(std::string fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::cout << "== Displaying all appointments from " << fileName << " ==" << std::endl;
    std::cout << "Format: appointmentID, petName, ownerUsername, appointmentDate, description" << std::endl << std::endl;
    std::string output;
    while (std::getline(inFile, output)) {
        std::cout << output << std::endl;
    }
    inFile.close();
}

//-------------------------------------------------
// Save section
//-------------------------------------------------

// Helper function to check for duplicate entries in a file.
bool checkForDuplicates(const std::string& identifier, const std::string& pathToFile) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream inFile(pathToFile);
    if (!inFile.is_open()) {
        // If file doesn't exist, that is okay.
        return false;
    }
    while (std::getline(inFile, line)) {
        details.clear();
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
            details.push_back(token);
        }
        if (!details.empty() && details[0] == identifier) {
            std::cout << "ID/Username/Name " << identifier << " already exists, please try again." << std::endl;
            return true;
        }
    }
    inFile.close();
    return false;
}

void Save::saveUser(std::string uname, std::string r, std::string pwd, 
                     std::string fname, std::string mail, std::string phone) {
    std::string pathToFile;
    if (r == "admin" || r == "vet" || r == "staff" || r == "guest") {
        pathToFile = "Data/staffacc.txt";
    } else if (r == "guest") {
        pathToFile = "Data/owner.txt";
    } else {
        std::cerr << "Error, no valid user role, select an appropriate role." << std::endl;
        return;
    }
    // Open file (create if necessary)
    std::ofstream outFile(pathToFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << pathToFile << std::endl;
        return;
    }
    if (checkForDuplicates(uname, pathToFile)) return;
    outFile << uname << "," << r << "," << pwd << "," << fname << "," << mail << "," << phone << "\n";
    outFile.close();
}

void Save::savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
                   std::string DOB, std::string breed) {
    std::string pathToFile = "Data/pets.txt";
    std::ofstream outFile(pathToFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << pathToFile << std::endl;
        return;
    }
    if (checkForDuplicates(name, pathToFile)) return;
    outFile << name << "," << ownerUsername << "," << appointmentsHistory << "," << DOB << "," << breed << "\n";
    outFile.close();
}

void Save::saveAppointment(int appointmentID, std::string petName, std::string ownerUsername, 
                           std::string appopintmentDate, std::string appointmentDescription) {
    std::string pathToFile = "Data/appointments.txt";
    std::ofstream outFile(pathToFile, std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << pathToFile << std::endl;
        return;
    }
    std::string idStr = std::to_string(appointmentID);
    if (checkForDuplicates(idStr, pathToFile)) return;
    outFile << appointmentID << "," << petName << "," << ownerUsername << "," << appopintmentDate << "," << appointmentDescription << "\n";
    outFile.close();
}

//-------------------------------------------------
// Update section
//-------------------------------------------------

void Update::updateUser(std::string uname, std::string fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream inFile(fileName);
    while (std::getline(inFile, line)) {
        details.clear();
        std::stringstream ss(line);
        while(std::getline(ss, token, ',')) {
            details.push_back(token);
        }
        if (!details.empty() && details[0] == uname && details.size() == 6) {
            break;
        }
    }
    inFile.close();
    std::string password = details[2];
    std::string userInputPassword;
    bool authenticated = false;
    for (int i = 3; i >= 0; i--) {
        std::cout << "Please enter password: ";
        std::cin >> userInputPassword;
        if (userInputPassword == password) {
            std::cout << "Password accepted!" << std::endl;
            authenticated = true;
            break;
        } else {
            std::cout << "Invalid password, please try again. [Tries left: " << i << "]" << std::endl;
        }
    }
    if (!authenticated) {
        std::cout << "Too many failed attempts. Try again later." << std::endl;
        return;
    }
    int choice;
    std::cout << "\n--- Update Profile ---" << std::endl;
    std::cout << "1. Username\n2. Password\n3. Email\n4. Phone\n0. Back\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice == 1) {
        std::string newUsername;
        std::cout << "Enter new username: ";
        std::cin >> newUsername;
        details[0] = newUsername;
    } else if (choice == 2) {
        std::string newPassword;
        std::cout << "Enter new password: ";
        std::cin >> newPassword;
        details[2] = newPassword;
    } else if (choice == 3) {
        std::string newEmail;
        std::cout << "Enter new email: ";
        std::cin >> newEmail;
        details[4] = newEmail;
    } else if (choice == 4) {
        std::string newPhone;
        std::cout << "Enter new phone number: ";
        std::cin >> newPhone;
        details[5] = newPhone;
    } else if (choice == 0) {
        std::cout << "Update cancelled." << std::endl;
        return;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return;
    }
    // Rebuild line and update file.
    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," +
                              details[3] + "," + details[4] + "," + details[5];
    std::vector<std::string> allLines;
    std::ifstream inputFile(fileName);
    while(std::getline(inputFile, line)) {
        allLines.push_back(line);
    }
    inputFile.close();
    for (auto& l : allLines) {
        std::stringstream ss(l);
        std::string temp;
        std::getline(ss, temp, ',');
        if (temp == uname) {
            l = updatedLine;
            break;
        }
    }
    std::ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << "\n";
    }
    outputFile.close();
    std::cout << "Profile updated successfully." << std::endl;
}

void Update::updatePet(std::string petName, std::string fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::vector<std::string> allLines;
    bool found = false;
    std::ifstream inputFile(fileName);
    while (std::getline(inputFile, line)) {
        details.clear();
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
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
        std::cout << "Pet not found." << std::endl;
        return;
    }
    int choice;
    std::cout << "\n--- Update Pet Details ---" << std::endl;
    std::cout << "1. Appointment History\n2. DOB\n3. Breed\n0. Back\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice == 1) {
        std::string newHistory;
        std::cout << "Enter new appointment history: ";
        std::cin.ignore();
        std::getline(std::cin, newHistory);
        details[2] = newHistory;
    } else if (choice == 2) {
        std::string newDOB;
        std::cout << "Enter new date of birth (YYYY-MM-DD): ";
        std::cin >> newDOB;
        details[3] = newDOB;
    } else if (choice == 3) {
        std::string newBreed;
        std::cout << "Enter new breed: ";
        std::cin >> newBreed;
        details[4] = newBreed;
    } else if (choice == 0) {
        std::cout << "Update cancelled." << std::endl;
        return;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return;
    }
    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];
    allLines.push_back(updatedLine);
    std::ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << "\n";
    }
    outputFile.close();
    std::cout << "Pet updated successfully." << std::endl;
}

void Update::updateAppointment(int appointmentID, const std::string& fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream inFile(fileName);
    bool found = false;
    while (std::getline(inFile, line)) {
        details.clear();
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
            details.push_back(token);
        }
        if (!details.empty() && std::stoi(details[0]) == appointmentID) {
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        std::cout << "Appointment with ID " << appointmentID << " not found." << std::endl;
        return;
    }
    int choice;
    std::cout << "\n--- Update Appointment ---" << std::endl;
    std::cout << "1. Date\n2. Description\n0. Back\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    if (choice == 1) {
        std::string newDate;
        std::cout << "Enter new date: ";
        std::cin >> newDate;
        details[3] = newDate;
    } else if (choice == 2) {
        std::string newDescription;
        std::cout << "Enter new description: ";
        std::cin.ignore();
        std::getline(std::cin, newDescription);
        details[4] = newDescription;
    } else if (choice == 0) {
        std::cout << "Update cancelled." << std::endl;
        return;
    } else {
        std::cout << "Invalid choice." << std::endl;
        return;
    }
    std::vector<std::string> allLines;
    std::ifstream fileIn(fileName);
    while (std::getline(fileIn, line)) {
        allLines.push_back(line);
    }
    fileIn.close();
    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];
    for (auto& l : allLines) {
        std::stringstream ss(l);
        std::string id;
        std::getline(ss, id, ',');
        if (std::stoi(id) == appointmentID) {
            l = updatedLine;
            break;
        }
    }
    std::ofstream fileOut(fileName);
    for (const auto& l : allLines) {
        fileOut << l << "\n";
    }
    fileOut.close();
    std::cout << "Appointment updated successfully." << std::endl;
}

//-------------------------------------------------
// Delete section
//-------------------------------------------------

void Delete::deleteEntry(const std::string& identifier, const std::string& fileName, const std::string& entryType) {
    std::ifstream inFile(fileName);
    std::vector<std::string> allLines;
    std::string line;
    bool found = false;
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ',');
        if (token != identifier) {
            allLines.push_back(line);
        } else {
            std::cout << entryType << " '" << identifier << "' deleted." << std::endl;
            found = true;
        }
    }
    inFile.close();
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Error writing to file: " << fileName << std::endl;
        return;
    }
    for (const std::string& l : allLines) {
        outFile << l << "\n";
    }
    outFile.close();
    if (!found) {
        std::cout << entryType << " '" << identifier << "' not found." << std::endl;
    }
}

