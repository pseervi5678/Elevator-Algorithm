#include "Manager.h"
// #include "Metrics.h"
#include <bits/stdc++.h>
using namespace std;

void Manager ::update_lift_status(Lift &l, Metrics &Mt, ETA &Et, int TimeStamp)
{

    if (l.state == Moving)
    {
        l.pos += l.curr_dir * 0.5;
        l.curr_flore = l.pos/4;
        int tmp = l.pos;
        if(tmp!= l.pos || tmp%4!= 0){
            if(l.curr_dir== 1 && l.curr_flore<= 0){
                l.curr_flore--;
            }
            if(l.curr_dir== -1 && l.curr_flore> 0){
                l.curr_flore++;
            }
        }
        if(l.req_dir== l.curr_dir){
            l.req_flore = l.curr_flore;
        }
        if (l.pos == l.next_flore * 4)
        {
            cout<<"Called Servicing"<<endl;
            Mt.Metrics_Engine(l, Et, TimeStamp);
            l.state = Servicing;
        }
    }
    else if (l.state == Servicing)
    {
        // cout<<"Called"<<endl;
        l.st += 0.5;
        if (l.st == 2)
        {
            l.st = 0;
            // cout<<"Called"<<endl;
            Manager:: manage_lift(l, Mt, Et);
        }
    }
}

void Manager :: manage_lift(Lift &l, Metrics &Mt, ETA &Et)
{
    if (l.stops.size() != 1)
    {
        l.curr_flore = (l.req_dir == 1) ? *l.stops.begin() : *l.stops.rbegin();
        l.stops.erase(l.curr_flore);
        l.next_flore = (l.req_dir == 1) ? *l.stops.begin() : *l.stops.rbegin();
        l.curr_dir = l.req_dir;
        l.state = Moving;
    }
    else if (l.stops.size() == 1 && l.next_stops.size() == 0)
    {
        l.curr_flore = *l.stops.begin();
        l.curr_dir = 0;
        l.req_flore = l.curr_flore;
        l.req_dir = l.curr_dir;
        l.state = Idel;
    }
    else if (l.stops.size() == 1)
    {
        l.curr_flore = *l.stops.begin();
        l.stops = l.next_stops;
        l.temp_dir = l.next_dir;
        l.next_stops.clear();
        l.next_dir = 0;

        int next_flore = (l.temp_dir == 1) ? *l.stops.begin() : *l.stops.rbegin();

        l.req_flore = l.next_flore;
        l.req_dir = l.temp_dir;

        if (next_flore == l.curr_flore)
        {
            l.stops.erase(l.curr_flore);
        }

        l.next_flore = (l.temp_dir == 1) ? *l.stops.begin() : *l.stops.rbegin();
        // l.req_flore = l.next_flore;
        l.req_dir = l.temp_dir;
        l.curr_dir = (l.next_flore > l.curr_flore) ? 1 : -1;
        l.state = Moving;
    }
}
