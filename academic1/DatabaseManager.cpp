#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


DatabaseManager::DatabaseManager() {
    studentCount = 0;
    teacherCount = 0;
    courseCount = 0;
    venueCount = 0;
    sectionCount = 0;

   
    coreExamW = 50; coreAssignW = 30; coreQuizW = 20;
    electiveExamW = 30; electiveAssignW = 40; electiveQuizW = 30;
    labExamW = 0;  labAssignW = 60; labQuizW = 40;

    for (int i = 0; i < MAX_STUDENTS; i++) students[i] = nullptr;
    for (int i = 0; i < MAX_COURSES; i++) courses[i] = nullptr;
}

DatabaseManager::~DatabaseManager() {
    for (int i = 0; i < studentCount; i++) {
        delete students[i];
        students[i] = nullptr;
    }
    for (int i = 0; i < courseCount; i++) {
        delete courses[i];
        courses[i] = nullptr;
    }
}

string* DatabaseManager::splitLine(string line, char delim, int& count) {
    static string parts[20];
    count = 0;
    string token = "";
    for (int i = 0; i <= (int)line.size(); i++) {
        if (i == (int)line.size() || line[i] == delim) {
            if (count < 20) {
                parts[count] = token;
                count++;
            }
            token = "";
        }
        else {
            token += line[i];
        }
    }
    return parts;
}

void DatabaseManager::loadAll() {
    loadWeightages();
    loadStudents();
    loadTeachers();
    loadCourses();
    loadVenues();
    loadSections();
    loadAssessments();
    loadFeedback();
    cout << "  Data loaded successfully." << endl;
}


void DatabaseManager::loadWeightages() {
    ifstream file("weightages.txt");
    if (!file.is_open()) {
        cout << "  WARNING: weightages.txt not found. Using defaults." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* parts = splitLine(line, '|', count);
        if (count < 4) continue;
        string type = parts[0];
        double exam = stod(parts[1]);
        double assign = stod(parts[2]);
        double quiz = stod(parts[3]);
        if (type == "Core") { coreExamW = exam; coreAssignW = assign; coreQuizW = quiz; }
        if (type == "Elective") { electiveExamW = exam; electiveAssignW = assign; electiveQuizW = quiz; }
        if (type == "Lab") { labExamW = exam; labAssignW = assign; labQuizW = quiz; }
    }
    file.close();
}

void DatabaseManager::loadStudents() {
    ifstream file("Students.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 4) continue;
        string id = p[0];
        string name = p[1];
        string email = p[2];
        string type = p[3];
        Student* s = nullptr;
        if (type == "Regular") {
            s = new RegularStudent(id, name, email);
            if (count >= 5 && p[4] != "0") {
               
            }
        }
        else if (type == "Scholarship") {
            double minGPA = (count >= 6) ? stod(p[5]) : 2.5;
            s = new ScholarshipStudent(id, name, email, minGPA);
        }
        else if (type == "Exchange") {
            s = new ExchangeStudent(id, name, email);
        }
        if (s) addStudent(s);
    }
    file.close();
}

void DatabaseManager::loadTeachers() {
    ifstream file("Teachers.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 3) continue;
        Teacher t(p[0], p[1], p[2]);
        addTeacher(t);
    }
    file.close();
}


void DatabaseManager::loadCourses() {
    ifstream file("Courses.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 4) continue;
        Course* c = nullptr;
        string type = p[3];
        if (type == "Core") {
            c = new CoreCourse(p[0], p[1], p[2]);
            c->setWeightages(coreExamW, coreAssignW, coreQuizW);
        }
        else if (type == "Elective") {
            c = new ElectiveCourse(p[0], p[1], p[2]);
            c->setWeightages(electiveExamW, electiveAssignW, electiveQuizW);
        }
        else if (type == "Lab") {
            c = new LabCourse(p[0], p[1], p[2]);
            c->setWeightages(labExamW, labAssignW, labQuizW);
        }
        if (c) addCourse(c);
    }
    file.close();
}


void DatabaseManager::loadVenues() {
    ifstream file("Venues.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 3) continue;
        Venue v(p[0], stoi(p[1]), (p[2] == "1"));
        addVenue(v);
    }
    file.close();
}


void DatabaseManager::loadSections() {
    ifstream file("Sections.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 5) continue;
        Section sec(p[0], p[1], p[2], p[4]);
        sec.addVenue(p[3]);
        addSection(sec);
    }
    file.close();
}


void DatabaseManager::loadAssessments() {
    ifstream file("Assessments.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 5) continue;
        Course* c = findCourse(p[0]);
        if (!c) continue;
        c->enterMarks(p[1], p[2], stod(p[3]), stod(p[4]));
    }
    file.close();
}

void DatabaseManager::loadFeedback() {
    ifstream file("Feedback.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        int count;
        string* p = splitLine(line, '|', count);
        if (count < 4) continue;
        Teacher* t = findTeacher(p[1]);
        if (!t) continue;
        Feedback f(p[0], p[1], stoi(p[2]), p[3]);
        t->addFeedback(f);
    }
    file.close();
}

void DatabaseManager::saveAll() {
    saveStudents();
    saveTeachers();
    saveCourses();
    saveVenues();
    saveSections();
    saveAssessments();
    saveFeedback();
    cout << "  All data saved." << endl;
}

void DatabaseManager::saveStudents() {
    ofstream file("Students.txt");
    file << "# ID|Name|Email|Type|GPA|ExtraParam" << endl;
    for (int i = 0; i < studentCount; i++) {
        Student* s = students[i];
        file << s->getID() << "|"
            << s->getName() << "|"
            << s->getEmail() << "|"
            << s->getStudentType() << "|";

        if (s->getStudentType() == "Scholarship") {
            ScholarshipStudent* ss = (ScholarshipStudent*)s;
            file << ss->calculateGPA() << "|" << ss->getMinGPA();
        }
        else {
            file << s->calculateGPA() << "|0";
        }
        file << endl;
    }
    file.close();
}

void DatabaseManager::saveTeachers() {
    ofstream file("Teachers.txt");
    file << "# ID|Name|Email|AvgFeedback" << endl;
    for (int i = 0; i < teacherCount; i++) {
        file << teachers[i].getID() << "|"
            << teachers[i].getName() << "|"
            << teachers[i].getEmail() << "|"
            << teachers[i].calculateAverageScore() << endl;
    }
    file.close();
}

void DatabaseManager::saveCourses() {
    ofstream file("Courses.txt");
    file << "# CourseID|Title|TeacherID|Type" << endl;
    for (int i = 0; i < courseCount; i++) {
        file << courses[i]->getCourseID() << "|"
            << courses[i]->getTitle() << "|"
            << courses[i]->getTeacherID() << "|"
            << courses[i]->getCourseType() << endl;
    }
    file.close();
}

void DatabaseManager::saveVenues() {
    ofstream file("Venues.txt");
    file << "# RoomID|Capacity|HasComputers(1/0)" << endl;
    for (int i = 0; i < venueCount; i++) {
        file << venues[i].getRoomID() << "|"
            << venues[i].getCapacity() << "|"
            << (venues[i].getHasComputers() ? "1" : "0") << endl;
    }
    file.close();
}

void DatabaseManager::saveSections() {
    ofstream file("Sections.txt");
    file << "# SectionID|CourseID|TeacherID|VenueID|TimeSlot" << endl;
    for (int i = 0; i < sectionCount; i++) {
        Section& sec = sections[i];
        string venues = "";
        for (int v = 0; v < sec.getVenueCount(); v++) {
            if (v > 0) venues += ",";
            venues += sec.getVenueID(v);
        }
        file << sec.getSectionID() << "|"
            << sec.getCourseID() << "|"
            << sec.getTeacherID() << "|"
            << venues << "|"
            << sec.getTimeSlot() << endl;
    }
    file.close();
}

void DatabaseManager::saveAssessments() {
    ofstream file("Assessments.txt");
    file << "# CourseID|StudentID|Type|RawScore|MaxScore" << endl;
   
    file.close();
}

void DatabaseManager::saveFeedback() {
    ofstream file("Feedback.txt");
    file << "# StudentID|TeacherID|Rating|Comment" << endl;
    for (int i = 0; i < teacherCount; i++) {
        for (int j = 0; j < teachers[i].getFeedbackCount(); j++) {
            Feedback f = teachers[i].getFeedback(j);
            file << f.getStudentID() << "|"
                << f.getTeacherID() << "|"
                << f.getRating() << "|"
                << f.getComment() << endl;
        }
    }
    file.close();
}

bool DatabaseManager::addStudent(Student* s) {
    if (studentCount >= MAX_STUDENTS) return false;
    students[studentCount] = s;
    studentCount++;
    return true;
}

Student* DatabaseManager::findStudent(string id) {
    for (int i = 0; i < studentCount; i++)
        if (students[i]->getID() == id) return students[i];
    return nullptr;
}

bool DatabaseManager::deleteStudent(string id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i]->getID() == id) {
            delete students[i];
            for (int j = i; j < studentCount - 1; j++)
                students[j] = students[j + 1];
            students[studentCount - 1] = nullptr;
            studentCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listStudents() const {
    if (studentCount == 0) { cout << "  No students found." << endl; return; }
    for (int i = 0; i < studentCount; i++)
        students[i]->displayProfile();
}

int      DatabaseManager::getStudentCount()         const { return studentCount; }
Student* DatabaseManager::getStudent(int index) { return students[index]; }


bool DatabaseManager::addTeacher(Teacher t) {
    if (teacherCount >= MAX_TEACHERS) return false;
    teachers[teacherCount] = t;
    teacherCount++;
    return true;
}

Teacher* DatabaseManager::findTeacher(string id) {
    for (int i = 0; i < teacherCount; i++)
        if (teachers[i].getID() == id) return &teachers[i];
    return nullptr;
}

bool DatabaseManager::deleteTeacher(string id) {
    for (int i = 0; i < teacherCount; i++) {
        if (teachers[i].getID() == id) {
            for (int j = i; j < teacherCount - 1; j++)
                teachers[j] = teachers[j + 1];
            teacherCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listTeachers() const {
    if (teacherCount == 0) { cout << "  No teachers found." << endl; return; }
    for (int i = 0; i < teacherCount; i++)
        teachers[i].displayProfile();
}

int      DatabaseManager::getTeacherCount()         const { return teacherCount; }
Teacher* DatabaseManager::getTeacher(int index) { return &teachers[index]; }

bool DatabaseManager::addCourse(Course* c) {
    if (courseCount >= MAX_COURSES) return false;
    courses[courseCount] = c;
    courseCount++;
    return true;
}

Course* DatabaseManager::findCourse(string id) {
    for (int i = 0; i < courseCount; i++)
        if (courses[i]->getCourseID() == id) return courses[i];
    return nullptr;
}

bool DatabaseManager::deleteCourse(string id) {
    for (int i = 0; i < courseCount; i++) {
        if (courses[i]->getCourseID() == id) {
            delete courses[i];
            for (int j = i; j < courseCount - 1; j++)
                courses[j] = courses[j + 1];
            courses[courseCount - 1] = nullptr;
            courseCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listCourses() const {
    if (courseCount == 0) { cout << "  No courses found." << endl; return; }
    for (int i = 0; i < courseCount; i++)
        courses[i]->displayInfo();
}

int     DatabaseManager::getCourseCount()        const { return courseCount; }
Course* DatabaseManager::getCourse(int index) { return courses[index]; }


bool DatabaseManager::addVenue(Venue v) {
    if (venueCount >= MAX_VENUES) return false;
    venues[venueCount] = v;
    venueCount++;
    return true;
}

Venue* DatabaseManager::findVenue(string id) {
    for (int i = 0; i < venueCount; i++)
        if (venues[i].getRoomID() == id) return &venues[i];
    return nullptr;
}

void DatabaseManager::listVenues() const {
    if (venueCount == 0) { cout << "  No venues found." << endl; return; }
    for (int i = 0; i < venueCount; i++)
        venues[i].display();
}

int    DatabaseManager::getVenueCount()       const { return venueCount; }
Venue* DatabaseManager::getVenue(int index) { return &venues[index]; }


bool DatabaseManager::addSection(Section s) {
    if (sectionCount >= MAX_SECTIONS) return false;
    sections[sectionCount] = s;
    sectionCount++;
    return true;
}

Section* DatabaseManager::findSection(string id) {
    for (int i = 0; i < sectionCount; i++)
        if (sections[i].getSectionID() == id) return &sections[i];
    return nullptr;
}

void DatabaseManager::listSections() const {
    if (sectionCount == 0) { cout << "  No sections found." << endl; return; }
    for (int i = 0; i < sectionCount; i++)
        sections[i].display();
}

int      DatabaseManager::getSectionCount()         const { return sectionCount; }
Section* DatabaseManager::getSection(int index) { return &sections[index]; }

bool DatabaseManager::registerStudentForSection(string studentID, string sectionID) {
    Student* s = findStudent(studentID);
    if (!s) {
        cout << "  ERROR: Student not found." << endl;
        return false;
    }
    Section* sec = findSection(sectionID);
    if (!sec) {
        cout << "  ERROR: Section not found." << endl;
        return false;
    }
    Course* c = findCourse(sec->getCourseID());
    if (!c) {
        cout << "  ERROR: Course not found." << endl;
        return false;
    }


    int totalCapacity = 0;
    for (int v = 0; v < sec->getVenueCount(); v++) {
        Venue* venue = findVenue(sec->getVenueID(v));
        if (venue) totalCapacity += venue->getCapacity();
    }
    if (c->getEnrolledCount() >= totalCapacity) {
        cout << "  ERROR: Capacity Full! Section cannot accept more students." << endl;
        return false;
    }

    string newTime = sec->getTimeSlot();
    for (int i = 0; i < sectionCount; i++) {
        if (sections[i].getSectionID() == sectionID) continue;
        if (!sections[i].hasTimeConflict(newTime)) continue;
        
        Course* otherCourse = findCourse(sections[i].getCourseID());
        if (otherCourse && otherCourse->isEnrolled(studentID)) {
            cout << "  ERROR: Time Conflict! Student is already in section "
                << sections[i].getSectionID()
                << " at time " << newTime << endl;
            return false;
        }
    }

 
    c->enrollStudent(studentID);
    s->addCourse(sec->getCourseID());
    cout << "  SUCCESS: " << s->getName() << " enrolled in "
        << c->getTitle() << " (Section " << sectionID << ")" << endl;
    return true;
}