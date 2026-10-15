#include "Metrics.h"
#include <bits/stdc++.h>
using namespace std;

Metrics :: Metrics(){
    AWT = 0, ATT = 0;
    S_AWT = 0, S_ATT = 0;
    c = 0;
};

void Metrics :: Metrics_Engine(Lift &l, ETA &Et, int &TimeStamp){
    int flore = l.curr_flore;
    int dir = l.curr_dir;

    vector<Passenger_request> tmp;
    for(auto it: Et.mp[{flore, l.n*dir}]){
        if(it.board_time== -1){
            it.board_time = TimeStamp;
            S_ATT += (it.board_time- it.req_time);
        }
        else{
            it.reach_time = TimeStamp;
            S_AWT += (it.reach_time- it.board_time);
            c += it.people;
            tmp.push_back(it);
        }
    }
    for(auto it: tmp){
        Et.mp[{flore, l.n*dir}].erase(it);
    }
}