#pragma once
#include <string>
using namespace std;
 
class Feedback {
private:
    string studentID;
    string teacherID;
    int    rating;    // 1 to 5
    string comment;
 
public:
    Feedback();
    Feedback(string sID, string tID, int rating, string comment);
 
    string getStudentID() const;
    string getTeacherID() const;
    int    getRating()    const;
    string getComment()   const;
 
    void display() const;
};