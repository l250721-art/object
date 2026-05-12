#pragma once

#include "StudentTypes.h"
#include "Teacher.h"
#include "CourseTypes.h"
#include "Venue.h"
#include "Section.h"
#include "Feedback.h"
#include <fstream>

const int MAX_STUDENTS = 200;
const int MAX_TEACHERS = 50;
const int MAX_COURSES = 100;
const int MAX_VENUES = 50;
const int MAX_SECTIONS = 100;


class DatabaseManager {
private:

    Student* students[MAX_STUDENTS];
    int       studentCount;

    Teacher   teachers[MAX_TEACHERS];
    int       teacherCount;

    Course* courses[MAX_COURSES];
    int       courseCount;

    Venue     venues[MAX_VENUES];
    int       venueCount;

    Section   sections[MAX_SECTIONS];
    int       sectionCount;

    double coreExamW, coreAssignW, coreQuizW;
    double electiveExamW, electiveAssignW, electiveQuizW;
    double labExamW, labAssignW, labQuizW;


    string* splitLine(string line, char delim, int& count);

public:
    DatabaseManager();
    ~DatabaseManager();

    void loadAll();
    void loadWeightages();
    void loadStudents();
    void loadTeachers();
    void loadCourses();
    void loadVenues();
    void loadSections();
    void loadAssessments();
    void loadFeedback();


    void saveAll();
    void saveStudents();
    void saveTeachers();
    void saveCourses();
    void saveVenues();
    void saveSections();
    void saveAssessments();
    void saveFeedback();


    bool    addStudent(Student* s);
    Student* findStudent(string id);
    bool    deleteStudent(string id);
    void    listStudents() const;
    int     getStudentCount() const;
    Student* getStudent(int index);


    bool     addTeacher(Teacher t);
    Teacher* findTeacher(string id);
    bool     deleteTeacher(string id);
    void     listTeachers() const;
    int      getTeacherCount() const;
    Teacher* getTeacher(int index);


    bool    addCourse(Course* c);
    Course* findCourse(string id);
    bool    deleteCourse(string id);
    void    listCourses() const;
    int     getCourseCount() const;
    Course* getCourse(int index);


    bool   addVenue(Venue v);
    Venue* findVenue(string id);
    void   listVenues() const;
    int    getVenueCount() const;
    Venue* getVenue(int index);


    bool     addSection(Section s);
    Section* findSection(string id);
    void     listSections() const;
    int      getSectionCount() const;
    Section* getSection(int index);


    bool registerStudentForSection(string studentID, string sectionID);
    void applyWeightages(Course* c);
};