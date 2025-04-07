#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include"features.h"

using namespace std;

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

        // check if staff
        if(!details.empty() && details [0] == name && details.size() == 3){ 
            std::cout << "Details for " << name << ":" << endl;
            std::cout << "Username: " << details[0] << endl;
            std::cout << "Password: " << details[1] << endl;
            std::cout << "Role: " << details[2] << endl;
        }
        // check if guest
        else if(!details.empty() && details [0] == name && details.size() == 5){
            std::cout << "Details for " << name << ":" << endl;
            std::cout << "Username: " << details[0] << endl;
            std::cout << "Password: " << details[1] << endl;
            std::cout << "Full name: " << details[2] << endl;
            std::cout << "Email: " << details[3] << endl;
            std::cout << "Phone: " << details[4] << endl;
        }
        //TODO: add condition for pet
      }
      
      // Close the file
      MyReadFile.close();
      
    cout << "Info from: " << fileName << endl;

}