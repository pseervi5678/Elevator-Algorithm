# pragma once
# include <bits/stdc++.h>
using namespace std;

enum LiftState{
    Idel,
    Servicing,
    Moving
};

class Lift{
    public:

    int n;
    double pos;
    int curr_dir, next_dir;
    int req_dir;
    int curr_flore;
    int next_flore;
    int req_flore;
    int temp_dir;
    int trips;
    double st;

    LiftState state;

    set<int> stops;
    set<int> next_stops;

    Lift();
};