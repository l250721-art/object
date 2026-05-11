#pragma once
#include "AcademicEntity.h"
#include "Feedback.h"

const int MAX_TEACHER_COURSES = 20;
const int MAX_FEEDBACK_ENTRIES = 100;

class Teacher : public AcademicEntity {
private:
    string assignedCourseIDs[MAX_TEACHER_COURSES];
    int    courseCount;

    Feedback feedbackList[MAX_FEEDBACK_ENTRIES];
    int      feedbackCount;

public:
    Teacher();
    Teacher(string id, string name, string email);

    // Course assignment
    void   assignCourse(string courseID);
    bool   hasCourse(string courseID) const;
    string getAssignedCourseID(int index) const;
    int    getCourseCount() const;

    // Feedback
    void   addFeedback(Feedback f);
    double calculateAverageScore() const;
    int    getFeedbackCount() const;
    Feedback getFeedback(int index) const;

    void displayProfile() const override;
    void displayFeedback() const;
};