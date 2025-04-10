#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"features.h"

//-------------------------------------------------
// View section
//-------------------------------------------------

void View::viewIndividual(std::string name, std::string fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream MyReadFile(fileName);
    if (!MyReadFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    while (std::getline(MyReadFile, line)) {
        details.clear();
        std::stringstream ss(line);

        while (std::getline(ss, token, ',')) {
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
        // Check if it is a pet record (assuming fileName is "pets.txt")
        else if (!details.empty() && details[0] == name && fileName == "pets.txt") {
            std::cout << "Details for " << name << ":" << std::endl;
            std::cout << "Name: " << details[0] << std::endl;
            std::cout << "Owner Username: " << details[1] << std::endl;
            std::cout << "Appointment History: " << details[2] << std::endl;
            std::cout << "DOB: " << details[3] << std::endl;
            std::cout << "Breed: " << details[4] << std::endl;
        }
    
        std::cout << "Info from: " << fileName << std::endl;
    }
    MyReadFile.close();
}

void View::viewAllUsers(std::string fileName) {
    std::ifstream MyReadFile(fileName);
    std::string output;

    std::cout << "== Displaying: " << fileName << " ==" << std::endl;
    std::cout << "Format: username, role, password, full name, email, phone number" << std::endl << std::endl;
    while (std::getline(MyReadFile, output)) {
        std::cout << output << std::endl;
    }
}

void View::viewAllPets(std::string fileName) {
    std::ifstream MyReadFile(fileName);
    std::string output;

    std::cout << "== Displaying: " << fileName << " ==" << std::endl;
    std::cout << "Format: name, ownerUsername, appointmentsHistory, DOB, breed" << std::endl << std::endl;
    while (std::getline(MyReadFile, output)) {
        std::cout << output << std::endl;
    }
}

//-------------------------------------------------
// Appointment View section
//-------------------------------------------------

// View an individual appointment by appointmentID
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
        
        // Check if details are valid and if the first token matches appointmentID
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

// View all appointments from a given file
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

bool checkForDuplicates(const std::string& identifier, const std::string& pathToFile) {
    std::vector<std::string> details;
    std::string line;
    std::string token;
    std::ifstream MyReadFile(pathToFile);
    if (!MyReadFile.is_open()) {
        std::cerr << "Failed to open file: " << pathToFile << std::endl;
        return false;  // Changed from 'return;' to 'return false;'
    }

    // Check if the profile already exists in the database
    while (std::getline(MyReadFile, line)) {
        details.clear();
        std::stringstream ss(line);

        while (std::getline(ss, token, ',')) {
            details.push_back(token);
        }

        if (!details.empty() && details[0] == identifier && (pathToFile == "Data/staffacc.txt" || pathToFile == "Data/owner.txt")) {  // check if user/staff
            std::cout << "User " << identifier << " already exists, please login!" << std::endl;
            return true;
        }
        else if (!details.empty() && details[0] == identifier && pathToFile == "Data/pets.txt") {  // check if pet
            std::cout << "Pet " << identifier << " already exists, please login!" << std::endl;
            return true;
        }
        else if (!details.empty() && details[0] == identifier && pathToFile == "Data/appointments.txt") {  // check if appointment
            std::cout << "Appointment " << identifier << " already exists, please login!" << std::endl;
            return true;
        }
    }
    MyReadFile.close(); 
    return false;
}

void Save::saveUser(std::string uname, std::string r, std::string pwd, 
std::string fname, std::string mail, std::string phone){
    std::string pathToFile;

    try
    {
        if(r == "admin" || r == "vet" || r == "staff" || r == "guest"){
            pathToFile = "Data/staffacc.txt";
        }
        else if (r == "guest"){
            pathToFile = "Data/owner.txt";
        }
        else{
            throw "Error, no valid user role, select an appropiate role.";
        }       
    }
    catch(const char* e){
        std::cerr << e << '\n';
    }

    std::vector<std::string> details;
    std::string line;
    std::string token;
    std::ifstream MyReadFile(pathToFile);
    if (!MyReadFile.is_open()) {
        std::cerr << "Failed to open file: " << pathToFile << std::endl;
        return;
    }
    
    if(checkForDuplicates(uname, pathToFile)){
        return;
    } 

    // save the file
    std::ofstream MyFile(pathToFile, std::ios::app);

    MyFile << uname << "," << r << "," << pwd << "," << fname << "," << mail << "," << phone << "\n";

    MyFile.close();
}

void Save::savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
    std::string DOB, std::string breed){
    std::string pathToFile = "Data/pets.txt";
    std::ofstream MyFile(pathToFile, std::ios::app);
    if (!MyFile.is_open()) {
        std::cerr << "Failed to open file: pets.txt" << std::endl;
        return;
    }

    if(checkForDuplicates(name, pathToFile)){
        return;
    } 

    MyFile << name << "," << ownerUsername << "," << appointmentsHistory << "," << DOB << "," << breed << "\n";
    MyFile.close();
}

void Save::saveAppointment(int appointmentID, std::string petName, std::string ownerUsername, std::string appopintmentDate, std::string appointmentDescription){
    std::ofstream MyFile("Data/appointments.txt", std::ios::app);
    if (!MyFile.is_open()) {
        std::cerr << "Failed to open file: " << "appointments.txt" << std::endl;
        return;
    }

    std::string IdToString = std::to_string(appointmentID);

    if(checkForDuplicates(IdToString, "Data/appointments.txt")){
        return;
    } 

    MyFile << appointmentID << "," << petName << "," << ownerUsername << "," << appopintmentDate << "," << appointmentDescription << "\n";

    MyFile.close();
}

//-------------------------------------------------
// Update section
//-------------------------------------------------

void Update::updateUser(std::string uname, std::string fileName){
    //reads the file
    std::vector<std::string> details;
    std::string line;
    std::string token;
    std::ifstream MyReadFile(fileName);

    while (std::getline(MyReadFile, line))
    {
        details.clear();
        std::stringstream ss(line);

        while(std::getline(ss, token, ',')){
            details.push_back(token);
        }

        if(!details.empty() && details[0] == uname && details.size() == 6){
            break;
        }
    }

    //authentication
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
            std::cout << "Invalid password, please try again. \n [Tries left: " << i << "]" << std::endl;
        }
    }

    if (!authenticated) {
        std::cout << "You entered a wrong password too many times, try again later." << std::endl;
        return;  // Exit the function early
    }

    //asks for changes
    while (true) {
        int choice;
        std::cout << "\n--- What would you like to update in your profile? ---\n";
        std::cout << "1. Username [1]\n";
        std::cout << "2. Password [2]\n";
        std::cout << "3. Email [3]\n";
        std::cout << "4. Phone [4]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string newUsername;
            std::cout << "Enter new username: ";
            std::cin >> newUsername;
            details[0] = newUsername;
            std::cout << "Username updated to " << newUsername << std::endl;
            break;  // exit after successful update
        }

        else if (choice == 2) {
            std::string newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;
            details[2] = newPassword;
            std::cout << "Password updated." << std::endl;
            break;
        }

        else if (choice == 3) {
            std::string newEmail;
            std::cout << "Enter new email: ";
            std::cin >> newEmail;
            details[4] = newEmail;
            std::cout << "Email updated to " << newEmail << std::endl;
            break;
        }

        else if (choice == 4) {
            std::string newPhone;
            std::cout << "Enter new phone number: ";
            std::cin >> newPhone;
            details[5] = newPhone;
            std::cout << "Phone number updated to " << newPhone << std::endl;
            break;
        }

        else if (choice == 0) {
            std::cout << "Returning to previous menu..." << std::endl;
            break;
        }

        else {
            std::cout << "Invalid option selected. Please try again.\n";
        }
    }
    //saves the changes

    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," +
                    details[3] + "," + details[4] + "," + details[5];

    std::vector<std::string> allLines;
    std::ifstream inputFile(fileName);

    while(std::getline(inputFile, line)){
        allLines.push_back(line);
    }

    inputFile.close();

    for (auto& l : allLines) {
        std::stringstream ss(l);
        std::string temp;
        std::getline(ss, temp, ',');  // temp holds the username
        if (temp == uname) {
            l = updatedLine;
            break;
        }
    }

    std::ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << '\n';
    }
    outputFile.close();

    std::cout << "Profile updated successfully. \n";
}

// Function to update a pet's details in the pets.txt file
void Update::updatePet(std::string petName, std::string fileName) {
    // Step 1: Read all pet data
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

        // Match pet by name
        if (!details.empty() && details[0] == petName && details.size() == 5) {
            found = true;
            break;
        }

        // Store other lines
        allLines.push_back(line);
    }
    inputFile.close();

    if (!found) {
        std::cout << "Pet not found.\n";
        return;
    }

    // Show current details
    std::cout << "\n--- Current Pet Info ---\n";
    std::cout << "Name: " << details[0] << std::endl;
    std::cout << "Owner Username: " << details[1] << std::endl;
    std::cout << "Appointment History: " << details[2] << std::endl;
    std::cout << "DOB: " << details[3] << std::endl;
    std::cout << "Breed: " << details[4] << std::endl;

    // Show menu for updates
    while (true) {
        int choice;
        std::cout << "\n--- What would you like to update? ---\n";
        std::cout << "1. Appointment History [1]\n";
        std::cout << "2. Date of Birth (DOB) [2]\n";
        std::cout << "3. Breed [3]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            std::string newHistory;
            std::cout << "Enter new appointment history: ";
            std::getline(std::cin, newHistory);
            details[2] = newHistory;
            std::cout << "Appointment history updated.\n";
            break;
        }
        else if (choice == 2) {
            std::string newDOB;
            std::cout << "Enter new date of birth (YYYY-MM-DD): ";
            std::cin >> newDOB;
            details[3] = newDOB;
            std::cout << "DOB updated.\n";
            break;
        }
        else if (choice == 3) {
            std::string newBreed;
            std::cout << "Enter new breed: ";
            std::cin >> newBreed;
            details[4] = newBreed;
            std::cout << "Breed updated.\n";
            break;
        }
        else if (choice == 0) {
            std::cout << "Returning to previous menu...\n";
            return;
        }
        else {
            std::cout << "Invalid option, please try again.\n";
        }
    }

    // Rebuild the updated line
    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];

    // Replace old pet line
    allLines.push_back(updatedLine);

    std::ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << "\n";
    }
    outputFile.close();

    std::cout << "Pet profile updated successfully.\n";
}

// Function to update an appointment in appointments.txt
void Update::updateAppointment(int appointmentID, const std::string& fileName) {
    std::vector<std::string> details;
    std::string line, token;
    std::ifstream MyReadFile(fileName);

    bool found = false;

    // Read all lines and find the appointment by ID
    while (getline(MyReadFile, line)) {
        details.clear();
        std::stringstream ss(line);

        while (getline(ss, token, ',')) {
            details.push_back(token);
        }

        if (!details.empty() && std::stoi(details[0]) == appointmentID) {
            found = true;
            break;
        }
    }

    MyReadFile.close();

    if (!found) {
        std::cout << "Appointment with ID " << appointmentID << " not found.\n";
        return;
    }

    // Ask the user what they want to update
    while (true) {
        int choice;
        std::cout << "\n--- What would you like to update for Appointment ID " << appointmentID << "? ---\n";
        std::cout << "1. Appointment Date [1]\n";
        std::cout << "2. Appointment Description [2]\n";
        std::cout << "0. Back [0]\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string newDate;
            std::cout << "Enter new appointment date: ";
            std::cin >> newDate;
            details[3] = newDate;
            std::cout << "Appointment date updated to " << newDate << "\n";
            break;
        } else if (choice == 2) {
            std::cin.ignore(); // clear newline from input buffer
            std::string newDescription;
            std::cout << "Enter new appointment description: ";
            std::getline(std::cin, newDescription);
            details[4] = newDescription;
            std::cout << "Appointment description updated.\n";
            break;
        } else if (choice == 0) {
            std::cout << "Returning to menu...\n";
            return;
        } else {
            std::cout << "Invalid option. Try again.\n";
        }
    }

    // Rebuild the file with updated appointment
    std::vector<std::string> allLines;
    std::ifstream inputFile(fileName);

    while (getline(inputFile, line)) {
        allLines.push_back(line);
    }

    inputFile.close();

    // Rebuild the line to write
    std::string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," +
                              details[3] + "," + details[4];

    for (auto& l : allLines) {
        std::stringstream ss(l);
        std::string id;
        getline(ss, id, ',');
        if (std::stoi(id) == appointmentID) {
            l = updatedLine;
            break;
        }
    }

    std::ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << "\n";
    }
    outputFile.close();

    std::cout << "Appointment updated successfully.\n";
}

//-------------------------------------------------
// Delete section
//-------------------------------------------------

void Delete::deleteEntry(const std::string& identifier, const std::string& fileName, const std::string& entryType) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> allLines;
    std::string line;
    bool found = false;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ','); // Grab the first item in the line (assumed unique identifier)

        if (token != identifier) {
            allLines.push_back(line);
        } else {
            std::cout << entryType << " '" << identifier << "' found and deleted." << std::endl;
            found = true;
        }
    }

    inputFile.close();

    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error writing to file: " << fileName << std::endl;
        return;
    }

    for (const std::string& l : allLines) {
        outputFile << l << '\n';
    }

    outputFile.close();

    if (!found) {
        std::cout << entryType << " '" << identifier << "' not found in file." << std::endl;
    }
}