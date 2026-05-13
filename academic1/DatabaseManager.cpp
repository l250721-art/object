#include "DatabaseManager.h"
#include <iostream>
#include <fstream>
using namespace std;

DatabaseManager::DatabaseManager()
{
    studentCount = 0;
    teacherCount = 0;
    courseCount = 0;
    venueCount = 0;
    sectionCount = 0;

    coreExamW = 50;    coreAssignW = 30;    coreQuizW = 20;
    electiveExamW = 30; electiveAssignW = 40; electiveQuizW = 30;
    labExamW = 0;      labAssignW = 60;     labQuizW = 40;

    for (int i = 0; i < MAX_STUDENTS; i++) students[i] = NULL;
    for (int i = 0; i < MAX_COURSES; i++)  courses[i] = NULL;
}

DatabaseManager::~DatabaseManager()
{
    for (int i = 0; i < studentCount; i++) { delete students[i]; students[i] = NULL; }
    for (int i = 0; i < courseCount; i++) { delete courses[i];  courses[i] = NULL; }
}

string DatabaseManager::getPart(string line, int index)
{
    int count = 0;
    string part = "";
    for (int i = 0; i < (int)line.length(); i++)
    {
        if (line[i] == '|')
        {
            if (count == index) return part;
            count++;
            part = "";
        }
        else
        {
            part += line[i];
        }
    }
    if (count == index) return part;
    return "";
}

void DatabaseManager::loadAll()
{
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

void DatabaseManager::loadWeightages()
{
    ifstream file("weightages.txt");
    if (!file.is_open())
    {
        cout << "  WARNING: weightages.txt not found. Using defaults." << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        string type = getPart(line, 0);
        double exam = atof(getPart(line, 1).c_str());
        double assign = atof(getPart(line, 2).c_str());
        double quiz = atof(getPart(line, 3).c_str());
        if (type == "Core") { coreExamW = exam;     coreAssignW = assign;     coreQuizW = quiz; }
        if (type == "Elective") { electiveExamW = exam; electiveAssignW = assign; electiveQuizW = quiz; }
        if (type == "Lab") { labExamW = exam;      labAssignW = assign;      labQuizW = quiz; }
    }
    file.close();
}

void DatabaseManager::loadStudents()
{
    ifstream file("Students.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        string id = getPart(line, 0);
        string name = getPart(line, 1);
        string email = getPart(line, 2);
        string type = getPart(line, 3);
        Student* s = NULL;
        if (type == "Regular")
            s = new RegularStudent(id, name, email);
        else if (type == "Scholarship")
            s = new ScholarshipStudent(id, name, email, atof(getPart(line, 5).c_str()));
        else if (type == "Exchange")
            s = new ExchangeStudent(id, name, email);
        if (s != NULL) addStudent(s);
    }
    file.close();
}

void DatabaseManager::loadTeachers()
{
    ifstream file("Teachers.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        Teacher t(getPart(line, 0), getPart(line, 1), getPart(line, 2));
        addTeacher(t);
    }
    file.close();
}

void DatabaseManager::loadCourses()
{
    ifstream file("Courses.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        string id = getPart(line, 0);
        string title = getPart(line, 1);
        string tID = getPart(line, 2);
        string type = getPart(line, 3);
        Course* c = NULL;
        if (type == "Core") { c = new CoreCourse(id, title, tID);     c->setWeightages(coreExamW, coreAssignW, coreQuizW); }
        if (type == "Elective") { c = new ElectiveCourse(id, title, tID); c->setWeightages(electiveExamW, electiveAssignW, electiveQuizW); }
        if (type == "Lab") { c = new LabCourse(id, title, tID);      c->setWeightages(labExamW, labAssignW, labQuizW); }
        if (c != NULL) addCourse(c);
    }
    file.close();
}

void DatabaseManager::loadVenues()
{
    ifstream file("Venues.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        Venue v(getPart(line, 0), atoi(getPart(line, 1).c_str()), getPart(line, 2) == "1");
        addVenue(v);
    }
    file.close();
}

void DatabaseManager::loadSections()
{
    ifstream file("Sections.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        Section sec(getPart(line, 0), getPart(line, 1), getPart(line, 2), getPart(line, 4));
        sec.addVenue(getPart(line, 3));
        addSection(sec);
    }
    file.close();
}

void DatabaseManager::loadAssessments()
{
    ifstream file("Assessments.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        Course* c = findCourse(getPart(line, 0));
        if (c != NULL)
            c->enterMarks(getPart(line, 1), getPart(line, 2), atof(getPart(line, 3).c_str()), atof(getPart(line, 4).c_str()));
    }
    file.close();
}

void DatabaseManager::loadFeedback()
{
    ifstream file("Feedback.txt");
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        Teacher* t = findTeacher(getPart(line, 1));
        if (t != NULL)
        {
            Feedback f(getPart(line, 0), getPart(line, 1), atoi(getPart(line, 2).c_str()), getPart(line, 3));
            t->addFeedback(f);
        }
    }
    file.close();
}

void DatabaseManager::saveAll()
{
    saveStudents();
    saveTeachers();
    saveCourses();
    saveVenues();
    saveSections();
    saveAssessments();
    saveFeedback();
    cout << "  All data saved." << endl;
}

void DatabaseManager::saveStudents()
{
    ofstream file("Students.txt");
    file << "# ID|Name|Email|Type|GPA|ExtraParam" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        Student* s = students[i];
        file << s->getID() << "|" << s->getName() << "|" << s->getEmail() << "|" << s->getStudentType() << "|";
        if (s->getStudentType() == "Scholarship")
        {
            ScholarshipStudent* ss = (ScholarshipStudent*)s;
            file << ss->calculateGPA() << "|" << ss->getMinGPA();
        }
        else
            file << s->calculateGPA() << "|0";
        file << endl;
    }
    file.close();
}

void DatabaseManager::saveTeachers()
{
    ofstream file("Teachers.txt");
    file << "# ID|Name|Email|AvgFeedback" << endl;
    for (int i = 0; i < teacherCount; i++)
        file << teachers[i].getID() << "|" << teachers[i].getName() << "|" << teachers[i].getEmail() << "|" << teachers[i].calculateAverageScore() << endl;
    file.close();
}

void DatabaseManager::saveCourses()
{
    ofstream file("Courses.txt");
    file << "# CourseID|Title|TeacherID|Type" << endl;
    for (int i = 0; i < courseCount; i++)
        file << courses[i]->getCourseID() << "|" << courses[i]->getTitle() << "|" << courses[i]->getTeacherID() << "|" << courses[i]->getCourseType() << endl;
    file.close();
}

void DatabaseManager::saveVenues()
{
    ofstream file("Venues.txt");
    file << "# RoomID|Capacity|HasComputers(1/0)" << endl;
    for (int i = 0; i < venueCount; i++)
        file << venues[i].getRoomID() << "|" << venues[i].getCapacity() << "|" << (venues[i].getHasComputers() ? "1" : "0") << endl;
    file.close();
}

void DatabaseManager::saveSections()
{
    ofstream file("Sections.txt");
    file << "# SectionID|CourseID|TeacherID|VenueID|TimeSlot" << endl;
    for (int i = 0; i < sectionCount; i++)
    {
        Section& sec = sections[i];
        string vlist = "";
        for (int v = 0; v < sec.getVenueCount(); v++) { if (v > 0) vlist += ","; vlist += sec.getVenueID(v); }
        file << sec.getSectionID() << "|" << sec.getCourseID() << "|" << sec.getTeacherID() << "|" << vlist << "|" << sec.getTimeSlot() << endl;
    }
    file.close();
}

void DatabaseManager::saveAssessments()
{
    ofstream file("Assessments.txt");
    file << "# CourseID|StudentID|Type|RawScore|MaxScore" << endl;
    file.close();
}

void DatabaseManager::saveFeedback()
{
    ofstream file("Feedback.txt");
    file << "# StudentID|TeacherID|Rating|Comment" << endl;
    for (int i = 0; i < teacherCount; i++)
        for (int j = 0; j < teachers[i].getFeedbackCount(); j++)
        {
            Feedback f = teachers[i].getFeedback(j);
            file << f.getStudentID() << "|" << f.getTeacherID() << "|" << f.getRating() << "|" << f.getComment() << endl;
        }
    file.close();
}

void DatabaseManager::applyWeightages(Course* c)
{
    if (c->getCourseType() == "Core")
        c->setWeightages(coreExamW, coreAssignW, coreQuizW);
    else if (c->getCourseType() == "Elective")
        c->setWeightages(electiveExamW, electiveAssignW, electiveQuizW);
    else if (c->getCourseType() == "Lab")
        c->setWeightages(labExamW, labAssignW, labQuizW);
}

bool DatabaseManager::addStudent(Student* s)
{
    if (studentCount >= MAX_STUDENTS) return false;
    students[studentCount] = s;
    studentCount++;
    return true;
}

Student* DatabaseManager::findStudent(string id)
{
    for (int i = 0; i < studentCount; i++)
        if (students[i]->getID() == id) return students[i];
    return NULL;
}

bool DatabaseManager::deleteStudent(string id)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i]->getID() == id)
        {
            delete students[i];
            for (int j = i; j < studentCount - 1; j++) students[j] = students[j + 1];
            students[studentCount - 1] = NULL;
            studentCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listStudents() const
{
    if (studentCount == 0) { cout << "  No students found." << endl; return; }
    for (int i = 0; i < studentCount; i++) students[i]->displayProfile();
}

int      DatabaseManager::getStudentCount() const { return studentCount; }
Student* DatabaseManager::getStudent(int index) { return students[index]; }

bool DatabaseManager::addTeacher(Teacher t)
{
    if (teacherCount >= MAX_TEACHERS) return false;
    teachers[teacherCount] = t;
    teacherCount++;
    return true;
}

Teacher* DatabaseManager::findTeacher(string id)
{
    for (int i = 0; i < teacherCount; i++)
        if (teachers[i].getID() == id) return &teachers[i];
    return NULL;
}

bool DatabaseManager::deleteTeacher(string id)
{
    for (int i = 0; i < teacherCount; i++)
    {
        if (teachers[i].getID() == id)
        {
            for (int j = i; j < teacherCount - 1; j++) teachers[j] = teachers[j + 1];
            teacherCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listTeachers() const
{
    if (teacherCount == 0) { cout << "  No teachers found." << endl; return; }
    for (int i = 0; i < teacherCount; i++) teachers[i].displayProfile();
}

int      DatabaseManager::getTeacherCount() const { return teacherCount; }
Teacher* DatabaseManager::getTeacher(int index) { return &teachers[index]; }

bool DatabaseManager::addCourse(Course* c)
{
    if (courseCount >= MAX_COURSES) return false;
    courses[courseCount] = c;
    courseCount++;
    return true;
}

Course* DatabaseManager::findCourse(string id)
{
    for (int i = 0; i < courseCount; i++)
        if (courses[i]->getCourseID() == id) return courses[i];
    return NULL;
}

bool DatabaseManager::deleteCourse(string id)
{
    for (int i = 0; i < courseCount; i++)
    {
        if (courses[i]->getCourseID() == id)
        {
            delete courses[i];
            for (int j = i; j < courseCount - 1; j++) courses[j] = courses[j + 1];
            courses[courseCount - 1] = NULL;
            courseCount--;
            return true;
        }
    }
    return false;
}

void DatabaseManager::listCourses() const
{
    if (courseCount == 0) { cout << "  No courses found." << endl; return; }
    for (int i = 0; i < courseCount; i++) courses[i]->displayInfo();
}

int     DatabaseManager::getCourseCount() const { return courseCount; }
Course* DatabaseManager::getCourse(int index) { return courses[index]; }

bool DatabaseManager::addVenue(Venue v)
{
    if (venueCount >= MAX_VENUES) return false;
    venues[venueCount] = v;
    venueCount++;
    return true;
}

Venue* DatabaseManager::findVenue(string id)
{
    for (int i = 0; i < venueCount; i++)
        if (venues[i].getRoomID() == id) return &venues[i];
    return NULL;
}

void DatabaseManager::listVenues() const
{
    if (venueCount == 0) { cout << "  No venues found." << endl; return; }
    for (int i = 0; i < venueCount; i++) venues[i].display();
}

int    DatabaseManager::getVenueCount() const { return venueCount; }
Venue* DatabaseManager::getVenue(int index) { return &venues[index]; }

bool DatabaseManager::addSection(Section s)
{
    if (sectionCount >= MAX_SECTIONS) return false;
    sections[sectionCount] = s;
    sectionCount++;
    return true;
}

Section* DatabaseManager::findSection(string id)
{
    for (int i = 0; i < sectionCount; i++)
        if (sections[i].getSectionID() == id) return &sections[i];
    return NULL;
}

void DatabaseManager::listSections() const
{
    if (sectionCount == 0) { cout << "  No sections found." << endl; return; }
    for (int i = 0; i < sectionCount; i++) sections[i].display();
}

int      DatabaseManager::getSectionCount() const { return sectionCount; }
Section* DatabaseManager::getSection(int index) { return &sections[index]; }

bool DatabaseManager::registerStudentForSection(string studentID, string sectionID)
{
    Student* s = findStudent(studentID);
    if (s == NULL) { cout << "  ERROR: Student not found." << endl; return false; }

    Section* sec = findSection(sectionID);
    if (sec == NULL) { cout << "  ERROR: Section not found." << endl; return false; }

    Course* c = findCourse(sec->getCourseID());
    if (c == NULL) { cout << "  ERROR: Course not found." << endl; return false; }

    if (s->isInCourse(sec->getCourseID())) { cout << "  ERROR: Already registered in this course." << endl; return false; }

    int totalCapacity = 0;
    for (int v = 0; v < sec->getVenueCount(); v++)
    {
        Venue* venue = findVenue(sec->getVenueID(v));
        if (venue != NULL) totalCapacity += venue->getCapacity();
    }
    if (c->getEnrolledCount() >= totalCapacity) { cout << "  ERROR: Section is full." << endl; return false; }

    string newTime = sec->getTimeSlot();
    for (int i = 0; i < sectionCount; i++)
    {
        if (sections[i].getSectionID() == sectionID) continue;
        if (!sections[i].hasTimeConflict(newTime)) continue;
        Course* other = findCourse(sections[i].getCourseID());
        if (other != NULL && other->isEnrolled(studentID))
        {
            cout << "  ERROR: Time conflict at " << newTime << endl;
            return false;
        }
    }

    c->enrollStudent(studentID);
    s->addCourse(sec->getCourseID());
    cout << "  SUCCESS: " << s->getName() << " enrolled in " << c->getTitle() << endl;
    return true;
}