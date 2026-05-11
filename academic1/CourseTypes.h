#pragma once

#include "Course.h"


class CoreCourse : public Course {
public:
    CoreCourse();
    CoreCourse(string id, string title, string teacherID);

    double calculateFinalGrade(string studentID) 
        const override;
    int    getExamDuration()                     
        const override;
    void   displayInfo()                         
        const override;
};


class ElectiveCourse : public Course {
public:
    ElectiveCourse();
    ElectiveCourse(string id, string title, string teacherID);

    double calculateFinalGrade(string studentID) 
        const override;
    int    getExamDuration()                     
        const override;
    void   displayInfo()                         
        const override;
};


class LabCourse : public Course {
private:
    bool requiresComputers;

public:
    LabCourse();
    LabCourse(string id, string title, string teacherID);

    double calculateFinalGrade(string studentID) 
        const override;
    int    getExamDuration()                    
        const override;  
    void   displayInfo()                         
        const override;

    bool getRequiresComputers()
        const;
};
