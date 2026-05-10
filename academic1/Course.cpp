#include "Course.h"
#include "Assessments.h"
#include <iostream>
using namespace std;

Course::Course() {
    courseID = "";
    title = "";
    teacherID = "";
    courseType = "";
    assessmentCount = 0;
    enrolledCount = 0;
    examWeightage = 0;
    assignmentWeightage = 0;
    quizWeightage = 0;

    for (int i = 0; i < MAX_ASSESSMENTS; i++)
        assessments[i] = nullptr;
}

Course::Course(string id, string t, string tid, string type) {
    courseID = id;
    title = t;
    teacherID = tid;
    courseType = type;
    assessmentCount = 0;
    enrolledCount = 0;
    examWeightage = 0;
    assignmentWeightage = 0;
    quizWeightage = 0;

    for (int i = 0; i < MAX_ASSESSMENTS; i++)
        assessments[i] = nullptr;
}

string Course::getCourseID()      const { return courseID; }
string Course::getTitle()         const { return title; }
string Course::getTeacherID()     const { return teacherID; }
string Course::getCourseType()    const { return courseType; }
int    Course::getEnrolledCount() const { return enrolledCount; }

string Course::getEnrolledStudentID(int index) const {
    if (index < 0 || index >= enrolledCount) return "";
    return enrolledStudentIDs[index];
}

void Course::setWeightages(double exam, double assign, double quiz) {
    examWeightage = exam;
    assignmentWeightage = assign;
    quizWeightage = quiz;
}

bool Course::enrollStudent(string studentID) {
    if (enrolledCount >= MAX_ENROLLED) {
        cout << "  ERROR: Course is at full capacity!" << endl;
        return false;
    }
    // Duplicate check
    if (isEnrolled(studentID)) {
        cout << "  ERROR: Student already enrolled in this course." << endl;
        return false;
    }
    enrolledStudentIDs[enrolledCount] = studentID;
    enrolledCount++;
    return true;
}

bool Course::isEnrolled(string studentID) const {
    for (int i = 0; i < enrolledCount; i++)
        if (enrolledStudentIDs[i] == studentID) return true;
    return false;
}

void Course::removeStudent(string studentID) {
    for (int i = 0; i < enrolledCount; i++) {
        if (enrolledStudentIDs[i] == studentID) {
            // Shift left
            for (int j = i; j < enrolledCount - 1; j++)
                enrolledStudentIDs[j] = enrolledStudentIDs[j + 1];
            enrolledCount--;
            return;
        }
    }
}

void Course::addAssessment(Assessment* a) {
    if (assessmentCount < MAX_ASSESSMENTS) {
        assessments[assessmentCount] = a;
        assessmentCount++;
    }
}

// Enter marks: creates a new Assessment of the right type for that student
// In this simple model each assessment record links type + score
void Course::enterMarks(string studentID, string assessType, double raw, double max) {
    if (!isEnrolled(studentID)) {
        cout << "  ERROR: Student " << studentID << " is not enrolled in this course." << endl;
        return;
    }
    Assessment* a = nullptr;
    if (assessType == "Exam")
        a = new Exam(raw, max, examWeightage);
    else if (assessType == "Quiz")
        a = new Quiz(raw, max, quizWeightage);
    else if (assessType == "Assignment")
        a = new Assignment(raw, max, assignmentWeightage);
    else {
        cout << "  ERROR: Unknown assessment type." << endl;
        return;
    }
    addAssessment(a);
    cout << "  Marks entered successfully." << endl;
}

void Course::displayAssessments() const {
    if (assessmentCount == 0) {
        cout << "  No assessments recorded." << endl;
        return;
    }
    for (int i = 0; i < assessmentCount; i++)
        assessments[i]->display();
}

Course::~Course() {
    for (int i = 0; i < assessmentCount; i++) {
        delete assessments[i];
        assessments[i] = nullptr;
    }
}