#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "menu.h"


using namespace std;

//-------------------------------------------------
// testing, delete later
//-------------------------------------------------
View view;

//-------------------------------------------------
// Main Function
//-------------------------------------------------

int main() {
    // Testing, delete later
    view.viewIndividual("mat", "owner.txt");

    // Ensure the account files exist.
    ensureFileExists("staffacc.txt");
    ensureFileExists("owner.txt");
    mainMenu();
    return 0;
}
