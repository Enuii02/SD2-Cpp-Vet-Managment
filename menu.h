// menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>
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
#endif
