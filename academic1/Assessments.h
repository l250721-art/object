#pragma once
#include "Assessment.h"


class Exam : public Assessment {
public:
    Exam();
    Exam(double raw, double max, double weight);

    double getWeightedScore() const override;
    void   display()          const override;
};

class Quiz : public Assessment {
public:
    Quiz();
    Quiz(double raw, double max, double weight);

    double getWeightedScore() const override;
    void   display()          const override;
};
class Assignment : public Assessment {
public:
    Assignment();
    Assignment(double raw, double max, double weight);

    double getWeightedScore() const override;
    void   display()          const override;
};