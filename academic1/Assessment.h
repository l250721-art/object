#pragma once
#include <string>
using namespace std;


class Assessment {
protected:
    string type;       
    double rawScore;
    double maxScore;
    double weightage; 

public:
    Assessment();
    Assessment(string type, double raw, double max, double weight);

    string getType()      const;
    double getRawScore()  const;
    double getMaxScore()  const;
    double getWeightage() const;

    void setRawScore(double s);
    void setMaxScore(double m);
    void setWeightage(double w);

   
    virtual double getWeightedScore() const = 0;

    virtual void display() const = 0;

    virtual ~Assessment();
};