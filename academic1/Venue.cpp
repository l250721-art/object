#include "Venue.h"
#include <iostream>
using namespace std;

Venue::Venue() {
    roomID = "";
    capacity = 0;
    hasComputers = false;
}

Venue::Venue(string id, int cap, bool computers) {
    roomID = id;
    capacity = cap;
    hasComputers = computers;
}

string Venue::getRoomID()       const { return roomID; }
int    Venue::getCapacity()     const { return capacity; }
bool   Venue::getHasComputers() const { return hasComputers; }

void Venue::setRoomID(string id) { roomID = id; }
void Venue::setCapacity(int c) { capacity = c; }
void Venue::setHasComputers(bool h) { hasComputers = h; }

void Venue::display() const {
    cout << "  Room: " << roomID
        << "  Capacity: " << capacity
        << "  Computers: " << (hasComputers ? "Yes" : "No") << endl;
}