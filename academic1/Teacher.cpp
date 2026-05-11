#include "Teacher.h"
#include <iostream>
using namespace std;

Teacher::Teacher() : AcademicEntity() {
    courseCount = 0;
    feedbackCount = 0;
}

Teacher::Teacher(string id, string name, string email)
    : AcademicEntity(id, name, email) {
    courseCount = 0;
    feedbackCount = 0;
}

void Teacher::assignCourse(string courseID) {
    if (courseCount < MAX_TEACHER_COURSES) {
        assignedCourseIDs[courseCount] = courseID;
        courseCount++;
    }
}

bool Teacher::hasCourse(string courseID) const {
    for (int i = 0; i < courseCount; i++)
        if (assignedCourseIDs[i] == courseID) return true;
    return false;
}

string Teacher::getAssignedCourseID(int index) const {
    if (index < 0 || index >= courseCount) return "";
    return assignedCourseIDs[index];
}

int Teacher::getCourseCount() const { return courseCount; }

void Teacher::addFeedback(Feedback f) {
    if (feedbackCount < MAX_FEEDBACK_ENTRIES) {
        feedbackList[feedbackCount] = f;
        feedbackCount++;
    }
}

double Teacher::calculateAverageScore() const {
    if (feedbackCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < feedbackCount; i++)
        sum += feedbackList[i].getRating();
    return sum / feedbackCount;
}

int Teacher::getFeedbackCount() const { return feedbackCount; }

Feedback Teacher::getFeedback(int index) const {
    return feedbackList[index];
}

void Teacher::displayProfile() const {
    cout << "  [Teacher] ID: " << ID
        << "  Name: " << name
        << "  Email: " << email << endl;
    cout << "  Courses: " << courseCount
        << "  Avg Feedback Score: " << calculateAverageScore() << "/5" << endl;
}

void Teacher::displayFeedback() const {
    cout << "  Feedback for " << name << " (Avg: "
        << calculateAverageScore() << "/5):" << endl;
    if (feedbackCount == 0) {
        cout << "  No feedback yet." << endl;
        return;
    }
    for (int i = 0; i < feedbackCount; i++)
        feedbackList[i].display();
}