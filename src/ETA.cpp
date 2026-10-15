#include "ETA.h"
#include <bits/stdc++.h>
using namespace std;

ETA ::ETA()
{
    L.clear();
    L.resize(4);
    L[0].n = 1;
    L[1].n = 2;
    L[2].n = 3;
    L[3].n = 4;

    mp.clear();
}

//  We can make this ETA algorithm as sophisticated as needed by incorporating factors such as 
// passenger waiting time, existing passengers' delays, elevator occupancy, remaining capacity, traffic patterns, 
// energy consumption, and predicted demand. We can also implement dynamic dispatch with adaptive 
// traffic modes (Peak Up, Peak Down, Inter-floor, and Off-peak), real-time demand analysis, 
// and sensor-based occupancy estimation. More advanced versions could leverage machine learning to predict passenger demand and continuously optimize elevator assignments.

void ETA ::request_assign(int id, int u, int v, int people, double req_time)
{

    int l = (u > v) ? request_down(u, v) : request_up(u, v);

    int dir = (u > v) ? -1 : 1;
    mp[{u, (l+1)*dir}].insert(Passenger_request(id, u, v, people, dir, req_time));
    mp[{v, (l+1)*dir}].insert(Passenger_request(id, u, v, people, dir, req_time));
}

int ETA ::request_down(int u, int v)
{

    int ans = 0;
    int cost = 1e9;

    for (int i = 0; i < 4; i++)
    {
        if (L[i].req_dir == 0)
        {
            int rem = abs(L[i].req_flore - u);
            int buffer = ((L[i].req_flore > u) ? 0 : 0); // buffer can be calculated by RL
            int ncost = (rem - 1) * 2 + (buffer + 1) * 3 + buffer * 5;
            if (cost > ncost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == -1 && L[i].req_flore > u)
        {

            int rem = L[i].req_flore - u;
            int cnt = 0;
            for (auto it : L[i].stops)
            {
                cnt += (it > u);
            }
            int ncost = cnt * 3 + cnt * 5 + (rem - cnt) * 2;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == 1 && (L[i].next_dir == -1 || L[i].next_dir == 0))
        {
            int up_rem = (*L[i].stops.rbegin()) - L[i].req_flore;
            int cnt = L[i].stops.size();
            int ncost = (up_rem - cnt) * 2 + cnt * 3 + cnt * 5;
            int buffer = (((*L[i].stops.rbegin()) > u) ? 0 : 0); // buffer we can calculate with RL
            int down_rem = abs(u - (*L[i].stops.rbegin()));
            cnt = 0;
            for (auto it : L[i].next_stops)
            {
                cnt += (it > u);
            }
            ncost += (down_rem - cnt - buffer) * 2 + max(buffer, 1) * 5 + cnt * 8;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == -1 && L[i].req_flore < u && (L[i].next_dir == -1 || L[i].next_dir == 0))
        {
            int down_rem = L[i].req_flore - (*L[i].stops.begin());
            int cnt = L[i].stops.size();
            int ncost = (down_rem - cnt) * 2 + cnt * 8;
            int mx = u;
            if (L[i].next_stops.size())
            {
                mx = max(mx, (*L[i].next_stops.rbegin()));
            }
            int up_rem = abs(mx - (*L[i].stops.begin()));
            ncost += up_rem * 2;
            int down_rem1 = mx - u;
            cnt = 0;
            for (auto it : L[i].next_stops)
            {
                cnt += (it > u);
            }
            ncost += (down_rem1 - cnt) * 2 + cnt * 8;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
    }

    int l = ans;

    if (L[l].req_dir == 0)
    {
        L[l].req_dir = -1;
        L[l].stops.insert(u);
        L[l].stops.insert(v);
        L[l].next_flore = (*L[l].stops.rbegin());
        L[l].trips += 2;
    }
    else if (L[l].req_dir == -1 && L[l].req_flore > u)
    {
        L[l].stops.insert(u);
        L[l].stops.insert(v);
        L[l].trips += 2;
    }
    else if (L[l].req_dir == 1 && (L[l].next_dir == -1 || L[l].next_dir == 0))
    {
        L[l].next_dir = -1;
        L[l].next_stops.insert(u);
        L[l].next_stops.insert(v);
    }
    else
    {
        L[l].next_dir = -1;
        L[l].next_stops.insert(u);
        L[l].next_stops.insert(v);
    }
    if(L[l].stops.find(L[l].curr_flore)!= L[l].stops.end()){
        auto tmp = L[l].stops.find(L[l].curr_flore);
        L[l].stops.erase(tmp);
    }
    L[l].next_flore = (L[l].req_dir == 1) ? *L[l].stops.begin() : *L[l].stops.rbegin();
    L[l].req_flore = L[l].next_flore;
    L[l].curr_dir = (L[l].next_flore > L[l].curr_flore) ? 1 : -1;
    L[l].state = Moving;
    


    return ans;
};

int ETA ::request_up(int u, int v)
{
    int ans = 0;
    int cost = 1e9;

    for (int i = 0; i < 4; i++)
    {
        if (L[i].req_dir == 0)
        {
            int rem = abs(L[i].req_flore - u);
            int buffer = (L[i].req_flore < u) ? 0 : 0; // buffer can be calculated by RL
            int ncost = (rem - 1) * 2 + (buffer + 1) * 3 + buffer * 5;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == 1 && L[i].req_flore < u)
        {
            int rem = u - L[i].req_flore;
            int cnt = 0;
            for (auto it : L[i].stops)
            {
                cnt += (it < u);
            }
            int ncost = cnt * 8 + (rem - cnt) * 2;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == -1 && (L[i].next_dir == 1 || L[i].next_dir == 0))
        {
            int down_rem = L[i].req_flore - (*L[i].stops.begin());
            int cnt = L[i].stops.size();
            int ncost = (down_rem - cnt) * 2 + cnt * 8;
            int up_rem = abs((*L[i].stops.begin()) - u);
            cnt = 0;
            for (auto it : L[i].next_stops)
            {
                cnt += (it < u);
            }
            ncost += (up_rem - cnt) * 2 + cnt * 8;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
        if (L[i].req_dir == 1 && L[i].req_flore > u && (L[i].next_dir == 1 || L[i].next_dir == 0))
        {
            int up_rem = (*L[i].stops.rbegin()) - L[i].req_flore;
            int cnt = L[i].stops.size();
            int ncost = (up_rem - cnt) * 2 + cnt * 8;
            int mn = u;
            if (L[i].next_stops.size())
            {
                mn = min((*L[i].next_stops.begin()), mn);
            }
            int ex = abs(mn - (*L[i].stops.rbegin()));
            ncost += ex * 2;
            cnt = 0;
            for (auto it : L[i].next_stops)
            {
                cnt += (it < u);
            }
            int up_rem1 = u - mn;
            ncost += (up_rem1 - cnt) * 2 + cnt * 8;

            if (ncost < cost)
            {
                cost = ncost;
                ans = i;
            }
        }
    }

    int l = ans;
    if (L[l].req_dir == 0)
    {
        L[l].req_dir = 1;
        L[l].stops.insert(u);
        L[l].stops.insert(v);
        L[l].next_flore = (*L[l].stops.begin());
        L[l].trips += 2;
    }
    else if (L[l].req_dir == 1 && L[l].req_flore < u)
    {
        L[l].stops.insert(u);
        L[l].stops.insert(v);
        L[l].trips += 2;
    }
    else if (L[l].req_dir == -1 && (L[l].next_dir == 1 || L[l].next_dir == 0))
    {
        L[l].next_dir = 1;
        L[l].next_stops.insert(u);
        L[l].next_stops.insert(v);
    }
    else
    {
        L[l].next_dir = 1;
        L[l].next_stops.insert(u);
        L[l].next_stops.insert(v);
    }
    if(L[l].stops.find(L[l].curr_flore)!= L[l].stops.end()){
        auto tmp = L[l].stops.find(L[l].curr_flore);
        L[l].stops.erase(tmp);
    }
    L[l].next_flore = (L[l].req_dir == 1) ? *L[l].stops.begin() : *L[l].stops.rbegin();
    L[l].req_flore = L[l].next_flore;
    L[l].curr_dir = (L[l].next_flore > L[l].curr_flore) ? 1 : -1;
    L[l].state = Moving;

    return ans;
}
