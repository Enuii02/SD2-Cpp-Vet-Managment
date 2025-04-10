#include <iostream>
#include "features.h"
#include "profiles.h"
#include "menu.h"

using namespace std;

int main() {
    // Ensure the data files exist (create them if they don't)
    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    ensureFileExists("Data/appointments.txt");

    // Start the menu-driven application
    mainMenu();
    
    return 0;
}
