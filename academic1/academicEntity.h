#pragma once
#include <string>
using namespace std;


class AcademicEntity {
protected:
    string ID;
    string name;
    string email;

public:
    AcademicEntity();
    AcademicEntity(string id, string name, string email);

    // Getters
    string getID()    const;
    string getName()  const;
    string getEmail() const;

    // Setters
    void setID(string id);
    void setName(string n);
    void setEmail(string e);

   
    virtual void displayProfile() const = 0;

   
    virtual ~AcademicEntity();
};
