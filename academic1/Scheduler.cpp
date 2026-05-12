#include "Scheduler.h"
#include <iostream>
#include <fstream>
using namespace std;

Scheduler::Scheduler(DatabaseManager* dbManager) {
    db = dbManager;
    timeSlotCount = 0;
    initTimeSlots();
}

void Scheduler::initTimeSlots() {
    
    timeSlots[0] = "Mon-08:00"; 
    timeSlots[1] = "Mon-11:00";
    timeSlots[2] = "Mon-14:00";
    timeSlots[3] = "Tue-08:00";
    timeSlots[4] = "Tue-11:00";
    timeSlots[5] = "Tue-14:00";
    timeSlots[6] = "Wed-08:00"; 
    timeSlots[7] = "Wed-11:00";
    timeSlots[8] = "Wed-14:00";
    timeSlots[9] = "Thu-08:00";
    timeSlots[10] = "Thu-11:00";
    timeSlots[11] = "Thu-14:00";
    timeSlots[12] = "Fri-08:00";
    timeSlots[13] = "Fri-11:00";
    timeSlots[14] = "Fri-14:00";
    timeSlotCount = 15;
}


bool Scheduler::isVenueFreeAt(string venueID, string timeSlot) {
    for (int i = 0; i < db->getSectionCount(); i++) {
        Section* sec = db->getSection(i);
        if (sec->getTimeSlot() != timeSlot) continue;
        for (int v = 0; v < sec->getVenueCount(); v++) {
            if (sec->getVenueID(v) == venueID) return false;
        }
    }
    return true;
}

string Scheduler::findNextFreeSlot(string venueID, string startAfterSlot) {
    bool found = (startAfterSlot == "");  
    for (int i = 0; i < timeSlotCount; i++) {
        if (!found) {
            if (timeSlots[i] == startAfterSlot) found = true;
            continue;
        }
        if (isVenueFreeAt(venueID, timeSlots[i]))
            return timeSlots[i];
    }
    return "NO_SLOT_AVAILABLE";
}


void Scheduler::assignVenuesToSections() {
    cout << "\n  === Scheduler: Assigning Venues ===" << endl;

    for (int i = 0; i < db->getSectionCount(); i++) {
        Section* sec = db->getSection(i);

        
        if (sec->getTimeSlot() != "" && sec->getTimeSlot() != "TBD") continue;

        Course* course = db->findCourse(sec->getCourseID());
        if (!course) continue;

        int studentsLeft = course->getEnrolledCount();
        bool needsComputers = (course->getCourseType() == "Lab");
        bool assigned = false;

        for (int t = 0; t < timeSlotCount && !assigned; t++) {
            string slot = timeSlots[t];
            int capacityCovered = 0;

        
            for (int v = 0; v < db->getVenueCount(); v++) {
                Venue* venue = db->getVenue(v);

                if (needsComputers && !venue->getHasComputers()) continue;

                if (!isVenueFreeAt(venue->getRoomID(), slot)) continue;

                sec->addVenue(venue->getRoomID());
                capacityCovered += venue->getCapacity();

                if (capacityCovered >= studentsLeft) {
                    sec->setTimeSlot(slot);
                    cout << "  Section " << sec->getSectionID()
                        << " assigned to slot " << slot << endl;
                    assigned = true;
                    break;
                }
            }
           
            if (capacityCovered > 0 && capacityCovered < studentsLeft) {
                sec->setTimeSlot(slot);
                cout << "  WARNING: Section " << sec->getSectionID()
                    << " partially covered at " << slot
                    << " (" << capacityCovered << "/" << studentsLeft << " seats)" << endl;
                assigned = true;
            }
        }

        if (!assigned) {
            cout << "  ERROR: Could not find venue for section "
                << sec->getSectionID() << endl;
        }
    }
}


void Scheduler::resolveConflicts() {
    cout << "\n  === Conflict Solver ===" << endl;
    bool anyConflict = false;

    for (int i = 0; i < db->getSectionCount(); i++) {
        for (int j = i + 1; j < db->getSectionCount(); j++) {
            Section* a = db->getSection(i);
            Section* b = db->getSection(j);

            if (a->getTimeSlot() != b->getTimeSlot()) continue;
            if (a->getTimeSlot() == "" || a->getTimeSlot() == "TBD") continue;

            for (int va = 0; va < a->getVenueCount(); va++) {
                for (int vb = 0; vb < b->getVenueCount(); vb++) {
                    if (a->getVenueID(va) == b->getVenueID(vb)) {
                        anyConflict = true;
                        cout << "  CONFLICT: Section " << a->getSectionID()
                            << " and Section " << b->getSectionID()
                            << " both use venue " << a->getVenueID(va)
                            << " at " << a->getTimeSlot() << endl;

                        string suggested = findNextFreeSlot(
                            b->getVenueID(vb), b->getTimeSlot());

                        cout << "  SUGGESTION: Move Section " << b->getSectionID()
                            << " to: " << suggested << endl;
                    }
                }
            }
        }
    }
    if (!anyConflict)
        cout << "  No conflicts detected." << endl;
}

void Scheduler::saveScheduleToFile() {
    ofstream file("ExamSchedule.txt");
    file << "# ===== EXAM SCHEDULE =====" << endl;
    file << "# SectionID | CourseID | TimeSlot | Venues" << endl;
    for (int i = 0; i < db->getSectionCount(); i++) {
        Section* sec = db->getSection(i);
        file << sec->getSectionID() << "|"
            << sec->getCourseID() << "|"
            << sec->getTimeSlot() << "|";
        for (int v = 0; v < sec->getVenueCount(); v++) {
            if (v > 0) file << ",";
            file << sec->getVenueID(v);
        }
        file << endl;
    }
    file.close();
    cout << "  Schedule saved to ExamSchedule.txt" << endl;
}

void Scheduler::displaySchedule() {
    cout << "\n  ===== EXAM SCHEDULE =====" << endl;
    if (db->getSectionCount() == 0) {
        cout << "  No sections scheduled." << endl;
        return;
    }
    cout << "  Section     Course      Time Slot     Venues" << endl;
    cout << "  -----------------------------------------------" << endl;
    for (int i = 0; i < db->getSectionCount(); i++) {
        Section* sec = db->getSection(i);
        cout << "  " << sec->getSectionID()
            << "    " << sec->getCourseID()
            << "    " << sec->getTimeSlot()
            << "    ";
        for (int v = 0; v < sec->getVenueCount(); v++) {
            if (v > 0) cout << ", ";
            cout << sec->getVenueID(v);
        }
        cout << endl;
    }
}