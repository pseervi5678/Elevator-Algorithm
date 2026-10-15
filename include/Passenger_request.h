#pragma once
# include <bits/stdc++.h>
using namespace std;

class Passenger_request{
    public:

    int id;
    int from, to;
    int people;
    int dir;

    double req_time;
    double board_time;
    double reach_time;

    Passenger_request(int id, int from, int to, int people, int dir, double req_time);

    bool operator<(const Passenger_request &other) const{
        if(req_time!= other.req_time){
            return req_time< other.req_time;
        }
        return id < other.id;
    }
};