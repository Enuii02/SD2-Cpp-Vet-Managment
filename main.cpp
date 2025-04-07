#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "menu.h"


using namespace std;

//-------------------------------------------------
// Main Function
//-------------------------------------------------

int main() {
    // Testing, delete later
    // view.viewIndividual(69, "staffacc.txt");

    // Ensure the account files exist.
    ensureFileExists("staffacc.txt");
    ensureFileExists("owner.txt");
    mainMenu();
    return 0;
}
