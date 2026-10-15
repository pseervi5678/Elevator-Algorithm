# include "Lift.h"
# include <bits/stdc++.h>
using namespace std;

Lift :: Lift(){

    n = 0;
    pos = 0.0;
    curr_dir = 0, next_dir = 0;
    curr_flore = 0;
    next_flore = 0;
    req_flore = 0;
    temp_dir = 0;
    req_dir = 0;
    st = 0;
    
    trips = 0;

    state = LiftState::Idel;

    stops.clear();
    next_stops.clear();

    stops.insert(0);
};