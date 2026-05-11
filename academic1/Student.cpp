#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() : AcademicEntity() {
    courseCount = 0;
    studentType = "";
}

Student::Student(string id, string name, string email, string type)
    : AcademicEntity(id, name, email) {
    courseCount = 0;
    studentType = type;
}

string Student::getStudentType() const { return studentType; }
int    Student::getCourseCount() const { return courseCount; }

string Student::getEnrolledCourseID(int index) const {
    if (index < 0 || index >= courseCount) return "";
    return enrolledCourseIDs[index];
}

void Student::addCourse(string courseID) {
    if (courseCount < MAX_STUDENT_COURSES && !isInCourse(courseID)) {
        enrolledCourseIDs[courseCount] = courseID;
        courseCount++;
    }
}

bool Student::isInCourse(string courseID) const {
    for (int i = 0; i < courseCount; i++)
        if (enrolledCourseIDs[i] == courseID) return true;
    return false;
}

void Student::dropCourse(string courseID) {
    for (int i = 0; i < courseCount; i++) {
        if (enrolledCourseIDs[i] == courseID) {
            for (int j = i; j < courseCount - 1; j++)
                enrolledCourseIDs[j] = enrolledCourseIDs[j + 1];
            courseCount--;
            return;
        }
    }
}

Student::~Student() {}