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

     int cost = 1e9;
    int ans;
    for (int i = 0; i < 4; i++)
    {
        if (L[i].req_dir == 0)
        {
            int nf = abs(L[i].req_flore - u);
            // int buffer = (L[i].cur_flore> u)? 1: 0;

            int ncost = (nf - 1) * 2 + 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == -1 && L[i].req_flore > u)
        {
            int nf = L[i].req_flore - u;
            int cnt = 0;
            for (auto it : L[i].stop)
            {
                cnt += (it > u);
            }
            int e = (L[i].stop.size() - cnt) + L[i].next_stop.size();
            int ncost = (cnt + 1) * 3 + (nf - cnt) * 2 + cnt * 5 + e * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == 1 && L[i].next_dir != 1)
        {
            int nf1 = (*L[i].stop.rbegin()) - L[i].req_flore;
            int cnt1 = L[i].stop.size();
            int ncost = (cnt1 + 1) * 3 + (nf1 - cnt1) * 2 + cnt1 * 5;
            int st = u;
            if (L[i].next_stop.size())
            {
                st = max(st, *L[i].next_stop.rbegin());
            }
            int nf2 = abs(st - *L[i].stop.rbegin());
            ncost += nf2 * 2;
            nf2 = st - u;
            int cnt2 = 0;
            for (auto it : L[i].next_stop)
            {
                cnt2 += (it > u);
            }
            ncost += (cnt2 + 1) * 3 + (nf2 - cnt2) * 2 + cnt2 * 5 + (L[i].next_stop.size() - cnt2) * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == -1 && L[i].cur_flore < u && L[i].next_dir != 1)
        {
            int nf1 = abs(L[i].cur_flore - *L[i].stop.begin());
            int cnt1 = L[i].stop.size();
            int ncost = (cnt1 + 1) * 3 + (nf1 - cnt1) * 2 + cnt1 * 5;
            int st = u;
            if (L[i].next_stop.size())
            {
                st = max(st, *L[i].next_stop.rbegin());
            }
            int nf2 = abs(st - *L[i].stop.begin());
            ncost += nf2 * 2;
            nf2 = st - u;
            int cnt2 = 0;
            for (auto it : L[i].next_stop)
            {
                cnt2 += (it > u);
            }
            ncost += (cnt2 + 1) * 3 + (nf2 - cnt2) * 2 + cnt2 * 5 + (L[i].next_stop.size() - cnt2) * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
    }

    int l = ans-1;

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
     int cost = 1e9;
    int ans;
    for (int i = 0; i < 4; i++)
    {
        if (L[i].req_dir == 0)
        {
            int nf = abs(L[i].req_flore - u);
            // int buffer = (L[i].cur_flore> u)? 1: 0;

            int ncost = (nf - 1) * 2 + 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == 1 && L[i].req_flore < u)
        {
            int nf = abs(L[i].req_flore - u);
            int cnt = 0;
            for (auto it : L[i].stop)
            {
                cnt += (it < u);
            }
            int e = (L[i].stop.size() - cnt) + L[i].next_stop.size();
            int ncost = (cnt + 1) * 3 + (nf - cnt) * 2 + cnt * 5 + e * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == -1 && L[i].next_dir != -1)
        {
            int nf1 = abs((*L[i].stop.begin()) - L[i].req_flore);
            int cnt1 = L[i].stop.size();
            int ncost = (cnt1 + 1) * 3 + (nf1 - cnt1) * 2 + cnt1 * 5;
            int st = u;
            if (L[i].next_stop.size())
            {
                st = min(st, *L[i].next_stop.begin());
            }
            int nf2 = abs(st - *L[i].stop.begin());
            ncost += nf2 * 2;
            nf2 = u - st;
            int cnt2 = 0;
            for (auto it : L[i].next_stop)
            {
                cnt2 += (it < u);
            }
            ncost += (cnt2 + 1) * 3 + (nf2 - cnt2) * 2 + cnt2 * 5 + (L[i].next_stop.size() - cnt2) * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
        if (L[i].req_dir == 1 && L[i].req_flore > u && L[i].next_dir != -1)
        {
            int nf1 = abs(L[i].req_flore - *L[i].stop.rbegin());
            int cnt1 = L[i].stop.size();
            int ncost = (cnt1 + 1) * 3 + (nf1 - cnt1) * 2 + cnt1 * 5;
            int st = u;
            if (L[i].next_stop.size())
            {
                st = min(st, *L[i].next_stop.begin());
            }
            int nf2 = abs(st - *L[i].stop.rbegin());
            ncost += nf2 * 2;
            nf2 = st - u;
            int cnt2 = 0;
            for (auto it : L[i].next_stop)
            {
                cnt2 += (it < u);
            }
            ncost += (cnt2 + 1) * 3 + (nf2 - cnt2) * 2 + cnt2 * 5 + (L[i].next_stop.size() - cnt2) * 3;
            if (ncost < cost)
            {
                cost = ncost;
                ans = i + 1;
            }
        }
    }

    int l = ans-1;
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
