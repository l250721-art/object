#pragma once
#include "Assessment.h"
#include <iostream>
using namespace std;

Assessment::Assessment() {
    type = "";
    rawScore = 0;
    maxScore = 100;
    weightage = 0;
}

Assessment::Assessment(string t, double raw, double max, double weight) {
    type = t;
    rawScore = raw;
    maxScore = max;
    weightage = weight;
}

string Assessment::getType()      const { return type; }
double Assessment::getRawScore()  const { return rawScore; }
double Assessment::getMaxScore()  const { return maxScore; }
double Assessment::getWeightage() const { return weightage; }

void Assessment::setRawScore(double s) { rawScore = s; }
void Assessment::setMaxScore(double m) { maxScore = m; }
void Assessment::setWeightage(double w) { weightage = w; }

Assessment::~Assessment() {}
