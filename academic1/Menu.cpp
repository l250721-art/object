#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(DatabaseManager* d, Scheduler* s)
{
    db = d;
    scheduler = s;
}

void Menu::printLine()
{
    cout << "  ================================================" << endl;
}

void Menu::printHeader(string title)
{
    cout << endl;
    printLine();
    cout << "    " << title << endl;
    printLine();
}

int Menu::getIntInput(string prompt, int minVal, int maxVal)
{
    int val;
    while (true)
    {
        cout << "  " << prompt;
        cin >> val;
        if (cin.fail() || val < minVal || val > maxVal)
        {
            cin.clear();
            cin.ignore();
            cout << "  Invalid input. Please enter a number between " << minVal << " and " << maxVal << endl;
        }
        else
        {
            cin.ignore();
            return val;
        }
    }
}

string Menu::getStringInput(string prompt)
{
    string val;
    cout << "  " << prompt;
    getline(cin, val);
    return val;
}

void Menu::run()
{
    printHeader("FAST Academic Office System");
    cout << "  Loading data..." << endl;
    db->loadAll();

    int choice = 0;
    while (choice != 8)
    {
        printHeader("MAIN MENU");
        cout << "  1. Student Management" << endl;
        cout << "  2. Teacher Management" << endl;
        cout << "  3. Course Management" << endl;
        cout << "  4. Registration" << endl;
        cout << "  5. Grading (Enter Marks)" << endl;
        cout << "  6. Teacher Feedback" << endl;
        cout << "  7. Exam Scheduler" << endl;
        cout << "  8. Save & Exit" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 8);

        if (choice == 1) studentMenu();
        else if (choice == 2) teacherMenu();
        else if (choice == 3) courseMenu();
        else if (choice == 4) registrationMenu();
        else if (choice == 5) gradingMenu();
        else if (choice == 6) feedbackMenu();
        else if (choice == 7) schedulerMenu();
        else if (choice == 8)
        {
            db->saveAll();
            cout << "  Goodbye!" << endl;
        }
    }
}

void Menu::studentMenu()
{
    int choice = 0;
    while (choice != 5)
    {
        printHeader("STUDENT MANAGEMENT");
        cout << "  1. Add Student" << endl;
        cout << "  2. View All Students" << endl;
        cout << "  3. Delete Student" << endl;
        cout << "  4. View Transcript" << endl;
        cout << "  5. Back" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 5);

        if (choice == 1) addStudentFlow();
        else if (choice == 2) db->listStudents();
        else if (choice == 3) deleteStudentFlow();
        else if (choice == 4) viewTranscriptFlow();
    }
}

void Menu::addStudentFlow()
{
    printHeader("ADD STUDENT");
    string id = getStringInput("Student ID: ");

    if (db->findStudent(id))
    {
        cout << "  ERROR: Student ID already exists." << endl;
        return;
    }

    string name = getStringInput("Name: ");
    string email = getStringInput("Email: ");

    cout << "  Student Type:" << endl;
    cout << "  1. Regular" << endl;
    cout << "  2. Scholarship" << endl;
    cout << "  3. Exchange" << endl;
    int type = getIntInput("Choose type: ", 1, 3);

    Student* s = NULL;

    if (type == 1)
    {
        s = new RegularStudent(id, name, email);
    }
    else if (type == 2)
    {
        double minGPA = 0;
        cout << "  Minimum GPA required: ";
        cin >> minGPA;
        cin.ignore();
        s = new ScholarshipStudent(id, name, email, minGPA);
    }
    else
    {
        s = new ExchangeStudent(id, name, email);
    }

    if (db->addStudent(s))
        cout << "  Student added successfully." << endl;
    else
        cout << "  ERROR: Could not add student." << endl;
}

void Menu::deleteStudentFlow()
{
    printHeader("DELETE STUDENT");
    string id = getStringInput("Enter Student ID to delete: ");

    if (db->deleteStudent(id))
        cout << "  Student deleted." << endl;
    else
        cout << "  ERROR: Student not found." << endl;
}

void Menu::viewTranscriptFlow()
{
    printHeader("VIEW TRANSCRIPT");
    string id = getStringInput("Enter Student ID: ");
    Student* s = db->findStudent(id);

    if (s == NULL)
    {
        cout << "  ERROR: Student not found." << endl;
        return;
    }

    s->viewTranscript();
}

void Menu::teacherMenu()
{
    int choice = 0;
    while (choice != 4)
    {
        printHeader("TEACHER MANAGEMENT");
        cout << "  1. Add Teacher" << endl;
        cout << "  2. View All Teachers" << endl;
        cout << "  3. Delete Teacher" << endl;
        cout << "  4. Back" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 4);

        if (choice == 1) addTeacherFlow();
        else if (choice == 2) db->listTeachers();
        else if (choice == 3) deleteTeacherFlow();
    }
}

void Menu::addTeacherFlow()
{
    printHeader("ADD TEACHER");
    string id = getStringInput("Teacher ID: ");

    if (db->findTeacher(id))
    {
        cout << "  ERROR: Teacher ID already exists." << endl;
        return;
    }

    string name = getStringInput("Name: ");
    string email = getStringInput("Email: ");
    Teacher t(id, name, email);

    if (db->addTeacher(t))
        cout << "  Teacher added successfully." << endl;
}

void Menu::deleteTeacherFlow()
{
    printHeader("DELETE TEACHER");
    string id = getStringInput("Enter Teacher ID to delete: ");

    if (db->deleteTeacher(id))
        cout << "  Teacher deleted." << endl;
    else
        cout << "  ERROR: Teacher not found." << endl;
}

void Menu::courseMenu()
{
    int choice = 0;
    while (choice != 5)
    {
        printHeader("COURSE MANAGEMENT");
        cout << "  1. Add Course" << endl;
        cout << "  2. View All Courses" << endl;
        cout << "  3. Delete Course" << endl;
        cout << "  4. Add Section" << endl;
        cout << "  5. Back" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 5);

        if (choice == 1) addCourseFlow();
        else if (choice == 2) db->listCourses();
        else if (choice == 3) deleteCourseFlow();
        else if (choice == 4) addSectionFlow();
    }
}

void Menu::addCourseFlow()
{
    printHeader("ADD COURSE");
    string id = getStringInput("Course ID: ");

    if (db->findCourse(id))
    {
        cout << "  ERROR: Course already exists." << endl;
        return;
    }

    string title = getStringInput("Title: ");
    string tID = getStringInput("Teacher ID: ");

    if (!db->findTeacher(tID))
    {
        cout << "  WARNING: Teacher not found, but course will be created." << endl;
    }

    cout << "  Course Type:" << endl;
    cout << "  1. Core" << endl;
    cout << "  2. Elective" << endl;
    cout << "  3. Lab" << endl;
    int type = getIntInput("Choose type: ", 1, 3);

    Course* c = NULL;

    if (type == 1)
        c = new CoreCourse(id, title, tID);
    else if (type == 2)
        c = new ElectiveCourse(id, title, tID);
    else
        c = new LabCourse(id, title, tID);

    if (db->addCourse(c))
        cout << "  Course added." << endl;
}

void Menu::deleteCourseFlow()
{
    printHeader("DELETE COURSE");
    string id = getStringInput("Enter Course ID to delete: ");

    if (db->deleteCourse(id))
        cout << "  Course deleted." << endl;
    else
        cout << "  ERROR: Course not found." << endl;
}

void Menu::addSectionFlow()
{
    printHeader("ADD SECTION");
    string secID = getStringInput("Section ID: ");
    string courseID = getStringInput("Course ID: ");
    string teacherID = getStringInput("Teacher ID: ");
    string timeSlot = getStringInput("Time Slot (e.g. Mon-09:00): ");
    Section sec(secID, courseID, teacherID, timeSlot);

    cout << "  Add venues to this section. Type 'done' when finished." << endl;
    while (true)
    {
        string venueID = getStringInput("Venue ID (or 'done'): ");
        if (venueID == "done") break;
        if (!db->findVenue(venueID))
        {
            cout << "  WARNING: Venue not found, but added anyway." << endl;
        }
        sec.addVenue(venueID);
    }

    if (db->addSection(sec))
        cout << "  Section added." << endl;
}

void Menu::registrationMenu()
{
    printHeader("SMART REGISTRATION");
    cout << "  Available Sections:" << endl;
    db->listSections();
    printLine();
    string studentID = getStringInput("Student ID: ");
    string sectionID = getStringInput("Section ID to register in: ");
    db->registerStudentForSection(studentID, sectionID);
}

void Menu::gradingMenu()
{
    printHeader("GRADING - ENTER MARKS");
    string courseID = getStringInput("Course ID: ");
    Course* c = db->findCourse(courseID);

    if (c == NULL)
    {
        cout << "  ERROR: Course not found." << endl;
        return;
    }

    c->displayInfo();
    cout << endl;

    string studentID = getStringInput("Student ID: ");

    if (!c->isEnrolled(studentID))
    {
        cout << "  ERROR: Student not enrolled in this course." << endl;
        return;
    }

    cout << "  Assessment Type:" << endl;
    cout << "  1. Exam" << endl;
    cout << "  2. Quiz" << endl;
    cout << "  3. Assignment" << endl;
    int type = getIntInput("Choose: ", 1, 3);

    string assessType = "";
    if (type == 1) assessType = "Exam";
    else if (type == 2) assessType = "Quiz";
    else assessType = "Assignment";

    double raw = 0, max = 0;
    cout << "  Raw Score: ";
    cin >> raw;
    cout << "  Max Score: ";
    cin >> max;
    cin.ignore();

    c->enterMarks(studentID, assessType, raw, max);

    Student* s = db->findStudent(studentID);

    if (s != NULL && s->getStudentType() == "Scholarship")
    {
        ScholarshipStudent* ss = (ScholarshipStudent*)s;
        ss->checkStatus();
        cout << "  Scholarship Status: " << ss->getStatus() << endl;
    }

    if (s != NULL && s->getStudentType() == "Exchange")
    {
        cout << "  Enter result for exchange student (1=Pass / 2=Fail): ";
        int res;
        cin >> res;
        cin.ignore();
        ExchangeStudent* es = (ExchangeStudent*)s;
        if (res == 1)
            es->setResult(courseID, "Pass");
        else
            es->setResult(courseID, "Fail");
        cout << "  Result recorded." << endl;
    }
}

void Menu::feedbackMenu()
{
    int choice = 0;
    while (choice != 3)
    {
        printHeader("TEACHER FEEDBACK");
        cout << "  1. Leave Feedback for a Teacher" << endl;
        cout << "  2. View Teacher Feedback" << endl;
        cout << "  3. Back" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 3);

        if (choice == 1) leaveFeedbackFlow();
        else if (choice == 2) viewFeedbackFlow();
    }
}

void Menu::leaveFeedbackFlow()
{
    printHeader("LEAVE FEEDBACK");
    string studentID = getStringInput("Your Student ID: ");

    if (!db->findStudent(studentID))
    {
        cout << "  ERROR: Student not found." << endl;
        return;
    }

    string teacherID = getStringInput("Teacher ID: ");
    Teacher* t = db->findTeacher(teacherID);

    if (t == NULL)
    {
        cout << "  ERROR: Teacher not found." << endl;
        return;
    }

    int rating = getIntInput("Rating (1-5): ", 1, 5);
    string comment = getStringInput("Comment: ");

    Feedback f(studentID, teacherID, rating, comment);
    t->addFeedback(f);
    cout << "  Feedback submitted. Teacher average score: " << t->calculateAverageScore() << "/5" << endl;
}

void Menu::viewFeedbackFlow()
{
    printHeader("VIEW TEACHER FEEDBACK");
    string teacherID = getStringInput("Teacher ID: ");
    Teacher* t = db->findTeacher(teacherID);

    if (t == NULL)
    {
        cout << "  ERROR: Teacher not found." << endl;
        return;
    }

    t->displayFeedback();
}

void Menu::schedulerMenu()
{
    int choice = 0;
    while (choice != 4)
    {
        printHeader("EXAM SCHEDULER");
        cout << "  1. Auto-assign Venues to Sections" << endl;
        cout << "  2. Run Conflict Solver" << endl;
        cout << "  3. View Schedule and Save to File" << endl;
        cout << "  4. Back" << endl;
        printLine();
        choice = getIntInput("Enter choice: ", 1, 4);

        if (choice == 1) scheduler->assignVenuesToSections();
        else if (choice == 2) scheduler->resolveConflicts();
        else if (choice == 3)
        {
            scheduler->displaySchedule();
            scheduler->saveScheduleToFile();
        }
    }
}