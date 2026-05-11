#pragma once
#include "AcademicEntity.h"

const int MAX_STUDENT_COURSES = 20;


class Student : public AcademicEntity {
protected:
    string enrolledCourseIDs[MAX_STUDENT_COURSES];
    int    courseCount;
    string studentType;  

public:
    Student();
    Student(string id, string name, string email, string type);

    string getStudentType() const;
    int    getCourseCount() const;
    string getEnrolledCourseID(int index) const;

    void addCourse(string courseID);
    bool isInCourse(string courseID) const;
    void dropCourse(string courseID);

    
    virtual double calculateGPA()    const = 0;
    virtual void   viewTranscript()  const = 0;
    void           displayProfile()  const override = 0;

    virtual ~Student();
};