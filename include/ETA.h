#pragma once
#include <bits/stdc++.h>
#include "Lift.h"
#include "Passenger_request.h"
using namespace std;

class ETA{
    public:

    vector<Lift> L;
    map<pair<int,int>, set<Passenger_request>> mp;

    ETA();

    void request_assign(int id, int from, int to, int people, double req_time);

    int request_down(int from, int to);

    int request_up(int from, int to);

};
