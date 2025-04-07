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
        // Output the text from the file
        // cout << user << endl;
        stringstream ss(line);
        while (ss, token, ','){
            details.push_back(token);
        }
        
      }
      
      // Close the file
      MyReadFile.close();
      
    cout << "Displaying info" << name << fileName << endl;

}