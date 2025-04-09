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
    //-------------------------------------------------

    Pet myPet("Buddy", "john_doe", "2024-05-01, 2025-01-15", "2020-08-12", "Golden Retriever");


    User user1("john_doe", "admin", "secure_password", "John Doe", "john.doe@example.com", "555-1234");
    user1.viewSelf("Data/staffacc.txt");

    User user2("jane_smith", "staff", "password123", "Jane Smith", "jane.smith@email.com", "555-5678");

    User user3("alex_brown", "staff", "alexpass456", "Alex Brown", "alex.brown@mail.net", "555-8765");


    // Save save;
    // save.saveUser("john_doe", "admin", "secure_password", "John Doe", "john.doe@example.com", "555-1234");

    // View view;
    // view.viewAllUsers("Data/staffacc.txt");
    // view.viewAllPets("Data/pets.txt");

    Update update;
    update.updateSelf("john_doe", "Data/staffacc.txt");

    //-------------------------------------------------

    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    // mainMenu();
    return 0;
}
