#include "Menu.h"
#include "DatabaseManager.h"
#include "Scheduler.h"
#include <iostream>
using namespace std;

int main() {
    DatabaseManager db;

    
    Scheduler scheduler(&db);

    
    Menu menu(&db, &scheduler);
    menu.run();

    return 0;
}