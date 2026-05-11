#include "Section.h"
#include <iostream>
using namespace std;

Section::Section() {
    sectionID = "";
    courseID = "";
    teacherID = "";
    timeSlot = "";
    venueCount = 0;
}

Section::Section(string secID, string cID, string tID, string ts) {
    sectionID = secID;
    courseID = cID;
    teacherID = tID;
    timeSlot = ts;
    venueCount = 0;
}

string Section::getSectionID()  const { return sectionID; }
string Section::getCourseID()   const { return courseID; }
string Section::getTeacherID()  const { return teacherID; }
string Section::getTimeSlot()   const { return timeSlot; }
int    Section::getVenueCount() const { return venueCount; }

string Section::getVenueID(int index) const {
    if (index < 0 || index >= venueCount) return "";
    return venueIDs[index];
}

void Section::setTimeSlot(string ts) { timeSlot = ts; }

void Section::addVenue(string venueID) {
    if (venueCount < MAX_SECTION_VENUES) {
        venueIDs[venueCount] = venueID;
        venueCount++;
    }
}
bool Section::hasTimeConflict(string otherTimeSlot) const {
    return (timeSlot == otherTimeSlot);
}

void Section::display() const {
    cout << "  Section: " << sectionID
        << "  Course: " << courseID
        << "  Teacher: " << teacherID
        << "  Time: " << timeSlot << endl;
    cout << "  Venues: ";
    for (int i = 0; i < venueCount; i++)
        cout << venueIDs[i] << " ";
    cout << endl;
}