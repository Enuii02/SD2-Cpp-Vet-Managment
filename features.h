#pragma once // With this the compiler won't open and read the file again after the first #include of the file
#include<string>

class View{
    public:

    void viewIndividual(std::string name, std::string fileName);

    void viewAll(std::string fileName);
};


class Save{
    public:

    void saveUser(std::string uname, std::string r, std::string pwd, 
        std::string fname, std::string mail, std::string phone);
};