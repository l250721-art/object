#pragma once
#include <string>
using namespace std;

class Venue {
private:
    string roomID;
    int    capacity;
    bool   hasComputers;

public:
    Venue();
    Venue(string id, int cap, bool computers);

    string getRoomID()       const;
    int    getCapacity()     const;
    bool   getHasComputers() const;

    void setRoomID(string id);
    void setCapacity(int c);
    void setHasComputers(bool h);

    void display() const;
};