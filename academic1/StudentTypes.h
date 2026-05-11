#pragma once
#include "Student.h"

// RegularStudent //
class RegularStudent : public Student {
protected:
    double gradePoints[MAX_STUDENT_COURSES]; 
    int    creditHours[MAX_STUDENT_COURSES];  

public:
    RegularStudent();
    RegularStudent(string id, string name, string email);

    void   setGradeForCourse(string courseID, double gradePoint, int credits);
    double calculateGPA()   const override;
    void   viewTranscript() const override;
    void   displayProfile() const override;
};

//  ScholarshipStudent //
class ScholarshipStudent : public RegularStudent {
private:
    double minGPA;
    string status;

public:
    ScholarshipStudent();
    ScholarshipStudent(string id, string name, string email, double minGPA);

    double calculateGPA()   const override; 
    void   viewTranscript() const override;
    void   displayProfile() const override;

    string getStatus()  const;
    double getMinGPA()  const;
    void   checkStatus();   
};

// ExchangeStudent //
class ExchangeStudent : public Student {
private:
    string passFailResults[MAX_STUDENT_COURSES]; 

public:
    ExchangeStudent();
    ExchangeStudent(string id, string name, string email);

    void   setResult(string courseID, string result);  
    string getResult(string courseID) const;

    double calculateGPA()   const override;  
    void   viewTranscript() const override;
    void   displayProfile() const override;
};