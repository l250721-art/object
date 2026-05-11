#include "StudentTypes.h"
#include <iostream>
using namespace std;
RegularStudent::RegularStudent() : Student() {
    studentType = "Regular";
    for (int i = 0; i < MAX_STUDENT_COURSES; i++) {
        gradePoints[i] = 0;
        creditHours[i] = 0;
    }
}

RegularStudent::RegularStudent(string id, string name, string email)
    : Student(id, name, email, "Regular") {
    for (int i = 0; i < MAX_STUDENT_COURSES; i++) {
        gradePoints[i] = 0;
        creditHours[i] = 0;
    }
}

void RegularStudent::setGradeForCourse(string courseID, double gp, int credits) {
    for (int i = 0; i < courseCount; i++) {
        if (enrolledCourseIDs[i] == courseID) {
            gradePoints[i] = gp;
            creditHours[i] = credits;
            return;
        }
    }
}

// GPA = sum(gradePoint * creditHours) / sum(creditHours)
double RegularStudent::calculateGPA() const {
    double totalPoints = 0;
    int    totalCredits = 0;
    for (int i = 0; i < courseCount; i++) {
        totalPoints += gradePoints[i] * creditHours[i];
        totalCredits += creditHours[i];
    }
    if (totalCredits == 0) return 0.0;
    return totalPoints / totalCredits;
}

void RegularStudent::viewTranscript() const {
    cout << "\n  ===== TRANSCRIPT: " << name << " (" << ID << ") =====" << endl;
    cout << "  Type: Regular Student" << endl;
    if (courseCount == 0) {
        cout << "  No courses enrolled." << endl;
        return;
    }
    cout << "  Course ID        Grade Points  Credits" << endl;
    cout << "  ----------------------------------------" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << "  " << enrolledCourseIDs[i]
            << "           " << gradePoints[i]
            << "           " << creditHours[i] << endl;
    }
    cout << "  ----------------------------------------" << endl;
    cout << "  Cumulative GPA: " << calculateGPA() << endl;
}

void RegularStudent::displayProfile() const {
    cout << "  [Regular Student] ID: " << ID
        << "  Name: " << name
        << "  GPA: " << calculateGPA() << endl;
}


ScholarshipStudent::ScholarshipStudent() : RegularStudent() {
    studentType = "Scholarship";
    minGPA = 3.0;
    status = "Good Standing";
}

ScholarshipStudent::ScholarshipStudent(string id, string name, string email, double min)
    : RegularStudent(id, name, email) {
    studentType = "Scholarship";
    minGPA = min;
    status = "Good Standing";
}

double ScholarshipStudent::calculateGPA() const {
    
    return RegularStudent::calculateGPA();
}

void ScholarshipStudent::checkStatus() {
    if (calculateGPA() < minGPA)
        status = "Probation";
    else
        status = "Good Standing";
}

string ScholarshipStudent::getStatus() const { return status; }
double ScholarshipStudent::getMinGPA() const { return minGPA; }

void ScholarshipStudent::viewTranscript() const {
    cout << "\n  ===== TRANSCRIPT: " << name << " (" << ID << ") =====" << endl;
    cout << "  Type: Scholarship Student  |  Min Required GPA: " << minGPA << endl;
    cout << "  Status: " << status << endl;
    if (courseCount == 0) {
        cout << "  No courses enrolled." << endl;
        return;
    }
    cout << "  Course ID        Grade Points  Credits" << endl;
    cout << "  ----------------------------------------" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << "  " << enrolledCourseIDs[i]
            << "           " << gradePoints[i]
            << "           " << creditHours[i] << endl;
    }
    cout << "  ----------------------------------------" << endl;
    cout << "  Cumulative GPA: " << calculateGPA() << endl;
    if (calculateGPA() < minGPA)
        cout << "  *** WARNING: GPA below scholarship minimum! ***" << endl;
}

void ScholarshipStudent::displayProfile() const {
    cout << "  [Scholarship Student] ID: " << ID
        << "  Name: " << name
        << "  GPA: " << calculateGPA()
        << "  Status: " << status << endl;
}


ExchangeStudent::ExchangeStudent() : Student() {
    studentType = "Exchange";
    for (int i = 0; i < MAX_STUDENT_COURSES; i++)
        passFailResults[i] = "N/A";
}

ExchangeStudent::ExchangeStudent(string id, string name, string email)
    : Student(id, name, email, "Exchange") {
    for (int i = 0; i < MAX_STUDENT_COURSES; i++)
        passFailResults[i] = "N/A";
}

void ExchangeStudent::setResult(string courseID, string result) {
    for (int i = 0; i < courseCount; i++) {
        if (enrolledCourseIDs[i] == courseID) {
            passFailResults[i] = result;
            return;
        }
    }
}

string ExchangeStudent::getResult(string courseID) const {
    for (int i = 0; i < courseCount; i++)
        if (enrolledCourseIDs[i] == courseID) return passFailResults[i];
    return "N/A";
}


double ExchangeStudent::calculateGPA() const { return 0.0; }

void ExchangeStudent::viewTranscript() const {
    cout << "\n  ===== TRANSCRIPT: " << name << " (" << ID << ") =====" << endl;
    cout << "  Type: Exchange Student  (Pass/Fail grading only)" << endl;
    if (courseCount == 0) {
        cout << "  No courses enrolled." << endl;
        return;
    }
    cout << "  Course ID        Result" << endl;
    cout << "  --------------------------------" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << "  " << enrolledCourseIDs[i]
            << "           " << passFailResults[i] << endl;
    }
}

void ExchangeStudent::displayProfile() const {
    cout << "  [Exchange Student] ID: " << ID
        << "  Name: " << name
        << "  (No GPA - Pass/Fail)" << endl;
}