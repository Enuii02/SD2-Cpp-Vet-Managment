#include<iostream>
#include<fstream>
#include<string>
#include"features.h"

using namespace std;

void View::viewIndividual(int ID, string fileName){

    string output;
    ifstream MyReadFile(fileName);

    while (getline (MyReadFile, output)) {
        // Output the text from the file
        cout << output;
      }
      
      // Close the file
      MyReadFile.close();
      
    cout << "Displaying info" << ID << fileName << endl;

}