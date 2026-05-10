#include "AcademicEntity.h"
#include <iostream>
using namespace std;

AcademicEntity::AcademicEntity() {
    ID = "";
    name = "";
    email = "";
}

AcademicEntity::AcademicEntity(string id, string n, string e) {
    ID = id;
    name = n;
    email = e;
}

string AcademicEntity::getID()    const { return ID; }
string AcademicEntity::getName()  const { return name; }
string AcademicEntity::getEmail() const { return email; }

void AcademicEntity::setID(string id) { ID = id; }
void AcademicEntity::setName(string n) { name = n; }
void AcademicEntity::setEmail(string e) { email = e; }

AcademicEntity::~AcademicEntity() {}
