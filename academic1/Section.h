#pragma once
#include "Course.h"
#include "Teacher.h"
#include "Venue.h"

const int MAX_SECTION_VENUES = 10;  

class Section {
private:
    string  sectionID;
    string  courseID;
    string  teacherID;
    string  timeSlot;    

    
    string  venueIDs[MAX_SECTION_VENUES];
    int     venueCount;

public:
    Section();
    Section(string secID, string courseID, string teacherID, string timeSlot);

    string getSectionID()  const;
    string getCourseID()   const;
    string getTeacherID()  const;
    string getTimeSlot()   const;
    int    getVenueCount() const;
    string getVenueID(int index) const;

    void setTimeSlot(string ts);
    void addVenue(string venueID);

    
    bool hasTimeConflict(string otherTimeSlot) const;

    void display() const;
};