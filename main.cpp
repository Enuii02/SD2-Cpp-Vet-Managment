#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "profiles.h"
#include "menu.h"


using namespace std;

//-------------------------------------------------
// Main Function
//-------------------------------------------------

int main() {

    //-------------------------------------------------
    // For Testing, delete later
    User user1("john_doe", "admin", "secure_password", "John Doe", "john.doe@example.com", "555-1234");
    user1.viewSelf("Data/staffacc.txt");

    View view;
    view.viewAll("Data/staffacc.txt");
    //-------------------------------------------------

    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    // mainMenu();
    return 0;
}
