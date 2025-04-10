#ifndef MENU_H
#define MENU_H

#include <string>

void mainMenu(); 
void loginMenu(); 
void signUpMenu(); 
void adminMenu(); 
void staffMenu();
void veterinaryMenu();
void guestMenu();

void adminAppointmentManagementMenu(); 
void adminOwnerManagementMenu();
void adminPetManagementMenu();
void adminSystemManagementMenu();

void staffAppointmentManagementMenu();
void veterinaryAppointmentManagementMenu();
void veterinaryOwnerManagementMenu();

void createNewAccount();
void alreadyHaveAccount();

void ensureFileExists(const std::string& filename);

//Functions linking to features

void scheduleAppointment();
void modifyAppointment();
void cancelAppointment();
void viewAppointmentRecordsFullAcess();
#endif
