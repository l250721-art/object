#pragma once
#include "Assessment.h"
#include <string>
using namespace std;

const int MAX_ASSESSMENTS = 20;
const int MAX_ENROLLED = 100;


class Course {
protected:
    string courseID;
    string title;
    string teacherID;
    string courseType;   

    
    Assessment* assessments[MAX_ASSESSMENTS];
    int assessmentCount;

   
    string enrolledStudentIDs[MAX_ENROLLED];
    int enrolledCount;

    
    double examWeightage;
    double assignmentWeightage;
    double quizWeightage;

public:
    Course();
    Course(string id, string title, string teacherID, string type);

   
    string getCourseID()  
        const;
    string getTitle()     
        const;
    string getTeacherID()  
        const;
    string getCourseType() 
        const;
    int    getEnrolledCount() 
        const;
    string getEnrolledStudentID(int index)
        const;

    
    void setWeightages(double exam, double assign, double quiz);

  
    bool enrollStudent(string studentID);  
    bool isEnrolled(string studentID) 
        const;
    void removeStudent(string studentID);

    
    void addAssessment(Assessment* a);
    void enterMarks(string studentID, string assessType, double raw, double max);

   
    virtual double calculateFinalGrade(string studentID) 
        const = 0;
    virtual int    getExamDuration()                     
        const = 0;  
    virtual void   displayInfo()                       
        const = 0;

    
    void displayAssessments() const;

    virtual ~Course();
};