#include <iostream>
#include <fstream>
#include <string>
#include "features.h"
#include "profiles.h"
#include "menu.h"

using namespace std;

int main() {

    // Ensure that the necessary files exist.
    ensureFileExists("Data/staffacc.txt");
    ensureFileExists("Data/owner.txt");
    ensureFileExists("Data/pets.txt");
    ensureFileExists("Data/appointments.txt");

    // ----------------------------------------------------------------
    // Test the new View functions for appointment records.
    // ----------------------------------------------------------------
    View viewObj;

    // Test: Display all appointments.
    cout << "\n=== Testing viewAllAppointments ===\n";
    viewObj.viewAllAppointments("Data/appointments.txt");

    // Test: Display an individual appointment using an appointment ID.
    // Replace '101' with an appointmentID that exists in your appointments.txt.
    int testAppointmentID = 1;
    cout << "\n=== Testing viewIndividualAppointment for appointment ID " << testAppointmentID << " ===\n";
    viewObj.viewIndividualAppointment(testAppointmentID, "Data/appointments.txt");

    // ----------------------------------------------------------------
    // Uncomment the next line if you wish to start the menu system.
    // mainMenu();

    return 0;
}
