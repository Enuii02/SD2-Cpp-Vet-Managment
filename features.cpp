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
    
        //check if user
        if (!details.empty() && details[0] == name && details.size() == 6) {
            std::cout << "Details for " << name << ":" << std::endl;
            std::cout << "Username: " << details[0] << std::endl;
            std::cout << "Role: " << details[1] << std::endl;
            std::cout << "Password: " << details[2] << std::endl;
            std::cout << "Full Name: " << details[3] << std::endl;
            std::cout << "Email: " << details[4] << std::endl;
            std::cout << "Phone Number: " << details[5] << std::endl;
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

        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
        
        ofstream MyFile(pathToFile, std::ios::app);

        cout << pathToFile;

        MyFile << uname << "," << r << "," << pwd << "," << fname << "," << mail << "," << phone << "\n";

        MyFile.close();
    }

    void Save::savePet(std::string name, std::string ownerUsername, std::string appointmentsHistory, 
        std::string DOB, std::string breed){
            string pathToFile = "Data/pets.txt";
    
            ofstream MyFile(pathToFile, std::ios::app);
    
            MyFile << name << "," << ownerUsername << "," << appointmentsHistory << "," << DOB << "," << breed << "\n";
    
            MyFile.close();
        }