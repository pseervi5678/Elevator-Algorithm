#pragma
#include "ETA.h"
#include "Metrics.h"
#include <bits/stdc++.h>
using namespace std;

class Manager{
    public:
    
    void update_lift_status(Lift &l, Metrics &Mt, ETA &Et, int TimeStamp);

    void manage_lift(Lift &l, Metrics &Mt, ETA &Et);

    
};