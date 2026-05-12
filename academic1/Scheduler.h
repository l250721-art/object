#pragma once
#include "Section.h"
#include "Venue.h"
#include "DatabaseManager.h"

const int MAX_TIME_SLOTS = 30;

class Scheduler {
private:
    DatabaseManager* db;

    
    string timeSlots[MAX_TIME_SLOTS];
    int    timeSlotCount;

    
    bool isVenueFreeAt(string venueID, string timeSlot);

   
    string findNextFreeSlot(string venueID, string startAfterSlot);

public:
    Scheduler(DatabaseManager* dbManager);

    void initTimeSlots();

    
    void assignVenuesToSections();

    
    void resolveConflicts();

  
    void saveScheduleToFile();

    
    void displaySchedule();
};