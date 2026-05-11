#include "Feedback.h"
#include <iostream>
using namespace std;

Feedback::Feedback() {
    studentID = "";
    teacherID = "";
    rating = 0;
    comment = "";
}

Feedback::Feedback(string sID, string tID, int r, string c) {
    studentID = sID;
    teacherID = tID;
    rating = r;
    comment = c;
}

string Feedback::getStudentID() const { return studentID; }
string Feedback::getTeacherID() const { return teacherID; }
int    Feedback::getRating()    const { return rating; }
string Feedback::getComment()   const { return comment; }

void Feedback::display() const {
    cout << "  Student: " << studentID
        << "  Rating: " << rating << "/5"
        << "  Comment: " << comment << endl;
}