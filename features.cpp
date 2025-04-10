#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"features.h"

using namespace std;


//-------------------------------------------------
// View section
//-------------------------------------------------

void View::viewIndividual(string name, string fileName){

    vector<string> details;
    string line;
    string token;
    ifstream MyReadFile(fileName);
    if (!MyReadFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    while (getline (MyReadFile, line)) {
        details.clear();
        stringstream ss(line);

        while (getline(ss, token, ',')){
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
    
        //check if user/staff
        if (!details.empty() && details[0] == name && details.size() == 6) {
            std::cout << "========================================" << endl;
            std::cout << "Details for " << name << ":" << std::endl;
            std::cout << "Username: " << details[0] << std::endl;
            std::cout << "Role: " << details[1] << std::endl;
            std::cout << "Password: " << details[2] << std::endl;
            std::cout << "Full Name: " << details[3] << std::endl;
            std::cout << "Email: " << details[4] << std::endl;
            std::cout << "Phone Number: " << details[5] << std::endl;
            std::cout << "========================================" << endl;

        }

        // check if pet
        else if(!details.empty() && details [0] == name && fileName=="pets.txt"){
            std::cout << "Details for " << name << ":" << endl;
            std::cout << "Name: " << details[0] << endl;
            std::cout << "Owner Username: " << details[1] << endl;
            std::cout << "Date of birth: " << details[2] << endl;
            std::cout << "breed: " << details[3] << endl;
        }
    
    cout << "Info from: " << fileName << endl;

    }
    // Close the file
    MyReadFile.close();
}

void View::viewAllUsers(std::string fileName){
    ifstream MyReadFile(fileName);
    string output;

    cout << "== Displaying: " << fileName << " ==" << endl;
    cout << "Format: username, role, password, full name, email, phone number" << endl << endl;
    while (getline (MyReadFile, output)) {
        cout << output << endl;
    };
}

void View::viewAllPets(std::string fileName){
    ifstream MyReadFile(fileName);
    string output;

    cout << "== Displaying: " << fileName << " ==" << endl;
    cout << "Format: name, ownerUsername, apoointmentHistory, DOB, breed" << endl << endl;
    while (getline (MyReadFile, output)) {
        cout << output << endl;
    };
}


//-------------------------------------------------
// Save section
//-------------------------------------------------

void Save::saveUser(std::string uname, std::string r, std::string pwd, 
    std::string fname, std::string mail, std::string phone){
        string pathToFile;

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

        vector<string> details;
        string line;
        string token;
        ifstream MyReadFile(pathToFile);
        if (!MyReadFile.is_open()) {
            std::cerr << "Failed to open file: " << pathToFile << std::endl;
            return;
        }
        
        //Check if the profile already exists in the database
        while (getline (MyReadFile, line)) {
            details.clear();
            stringstream ss(line);
    
            while (getline(ss, token, ',')){
                details.push_back(token);
            }

            if(details[0] == uname){
                cout << "User already exists, please login!" << endl;
                return;
            }
        }
        // save the file
        ofstream MyFile(pathToFile, std::ios::app);

        MyFile << uname << "," << r << "," << pwd << "," << fname << "," << mail << "," << phone << "\n";

        MyFile.close();
        
    }

    void Save::savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
        std::string DOB, std::string breed){
            string pathToFile = "Data/pets.txt";
            ofstream MyFile(pathToFile, std::ios::app);

            if (!MyFile.is_open()) {
                std::cerr << "Failed to open file: " << "pets.txt" << std::endl;
                return;
            }
    
            MyFile << name << "," << ownerUsername << "," << appointmentsHistory << "," << DOB << "," << breed << "\n";
    
            MyFile.close();
        }
    
    void Save::saveAppointment(int appointmentID, std::string petName, std::string ownerUsername, std::string appopintmentDate, std::string appointmentDescription){
        ofstream MyFile("Data/appointments.txt", std::ios::app);
        if (!MyFile.is_open()) {
            std::cerr << "Failed to open file: " << "appointments.txt" << std::endl;
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
    vector<string> details;
    string line;
    string token;
    ifstream MyReadFile(fileName);

    while (getline (MyReadFile, line))
    {
        details.clear();
        stringstream ss(line);

        while(getline(ss, token, ',')){
            details.push_back(token);
        }

        if(!details.empty() && details[0] == uname && details.size() == 6){
            break;
        }
    }

    //authentication
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
        return;  // Exit the function early
    }

    //asks for changes
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
            break;  // exit after successful update
        }
    
        else if (choice == 2) {
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;
            details[2] = newPassword;
            cout << "Password updated." << endl;
            break;
        }
    
        else if (choice == 3) {
            string newEmail;
            cout << "Enter new email: ";
            cin >> newEmail;
            details[4] = newEmail;
            cout << "Email updated to " << newEmail << endl;
            break;
        }
    
        else if (choice == 4) {
            string newPhone;
            cout << "Enter new phone number: ";
            cin >> newPhone;
            details[5] = newPhone;
            cout << "Phone number updated to " << newPhone << endl;
            break;
        }
    
        else if (choice == 0) {
            cout << "Returning to previous menu..." << endl;
            break;
        }
    
        else {
            cout << "Invalid option selected. Please try again.\n";
        }
    }
    //saves the changes

    string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," +
                     details[3] + "," + details[4] + "," + details[5];
    
    vector<string> allLines;
    ifstream inputFile(fileName);

    while(getline(inputFile, line)){
        allLines.push_back(line);
    }

    inputFile.close();

    for (auto& l : allLines) {
        stringstream ss(l);
        string temp;
        getline(ss, temp, ',');  // temp holds the username
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

    cout << "Profile updated successfully. \n";
}

// Function to update a pet's details in the pets.txt file
void Update::updatePet(std::string petName, std::string fileName) {
    // Step 1: Read all pet data
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
        cout << "Pet not found.\n";
        return;
    }

    // Show current details
    cout << "\n--- Current Pet Info ---\n";
    cout << "Name: " << details[0] << endl;
    cout << "Owner Username: " << details[1] << endl;
    cout << "Appointment History: " << details[2] << endl;
    cout << "DOB: " << details[3] << endl;
    cout << "Breed: " << details[4] << endl;

    // Show menu for updates
    while (true) {
        int choice;
        cout << "\n--- What would you like to update? ---\n";
        cout << "1. Appointment History [1]\n";
        cout << "2. Date of Birth (DOB) [2]\n";
        cout << "3. Breed [3]\n";
        cout << "0. Back [0]\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            string newHistory;
            cout << "Enter new appointment history: ";
            getline(cin, newHistory);
            details[2] = newHistory;
            cout << "Appointment history updated.\n";
            break;
        }
        else if (choice == 2) {
            string newDOB;
            cout << "Enter new date of birth (YYYY-MM-DD): ";
            cin >> newDOB;
            details[3] = newDOB;
            cout << "DOB updated.\n";
            break;
        }
        else if (choice == 3) {
            string newBreed;
            cout << "Enter new breed: ";
            cin >> newBreed;
            details[4] = newBreed;
            cout << "Breed updated.\n";
            break;
        }
        else if (choice == 0) {
            cout << "Returning to previous menu...\n";
            return;
        }
        else {
            cout << "Invalid option, please try again.\n";
        }
    }

    // Rebuild the updated line
    string updatedLine = details[0] + "," + details[1] + "," + details[2] + "," + details[3] + "," + details[4];

    // Replace old pet line
    allLines.push_back(updatedLine);

    ofstream outputFile(fileName);
    for (const auto& l : allLines) {
        outputFile << l << "\n";
    }
    outputFile.close();

    cout << "Pet profile updated successfully.\n";
}


//-------------------------------------------------
// Delete section
//-------------------------------------------------

void Delete::deleteProfile(std::string uname){
    cout << "Deleting profile: " << uname;
}

void Delete::deletePet(const std::string& petName, const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::vector<std::string> allLines;
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    // Read all lines and filter out the pet to delete
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string token;
        getline(ss, token, ','); // token holds the pet name

        if (token != petName) {
            allLines.push_back(line);
        } else {
            std::cout << "Pet '" << petName << "' found and deleted." << std::endl;
        }
    }

    inputFile.close();

    // Write filtered lines back to the file
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error writing to file: " << fileName << std::endl;
        return;
    }

    for (const std::string& l : allLines) {
        outputFile << l << '\n';
    }

    outputFile.close();
}
    