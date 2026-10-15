#include "Passenger_request.h"
#include <bits/stdc++.h>
using namespace std;



Passenger_request :: Passenger_request(int id, int from, int to, int people, int dir, double req_time){
    this-> id = id;
    this-> from = from;
    this-> to = to;
    this-> people = people;
    this-> dir = dir;
    this-> req_time = req_time;
    board_time = -1;
    reach_time = -1;
}
