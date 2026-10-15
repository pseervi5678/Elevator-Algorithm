#pragma once
#include "Lift.h"
#include "ETA.h"

class Metrics{
    public:

    double AWT, ATT;
    double S_AWT, S_ATT;
    double c;

    Metrics();
    void Metrics_Engine(Lift &l, ETA &Et, int &TimeStamp);
};

