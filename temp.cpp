#include <bits/stdc++.h>
#include "ETA.h"
#include "Manager.h"
#include "Metrics.h"
#include "InputLoader.h"
#include "Request.h"
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

int main(){
    

    ETA Et;
    Manager M;
    Metrics Mt;

    const double TIME_STEP = 0.5;
    int id = 1;
    double s_time;
    cin>> s_time;

    // s_time = 0;

    vector<Request> requests = InputLoader :: loadRequests("test/requests.csv");
    for(const Request R: requests){
        cout<<R.timestamp<<" "<<R.from<<" "<<R.to<<" "<<R.people<<endl;
    }


    // for(auto it: requests){
    //     cout<<it.timestamp<<" "<<it.from<<" "<<it.to<<" "<<it.people<<endl;
    // }

    int i = 0;
    for(double t = 0; t<= s_time; ){

        // incorporate the request functionality
        // serving the request with time through the comming input requests

        // requests is comming in sorted order according to timestamp
        while(i< requests.size() && requests[i].timestamp== t){
            Et.request_assign(id, requests[i].from, requests[i].to, requests[i].people, requests[i].timestamp);
            id++;
            i++;
        }


        // Managing lift status per 0.5 seconds
        for(int l = 0; l< 4; l++){
            M.update_lift_status(Et.L[l], Mt, Et, t);
            cout<<Et.L[i].curr_flore<<" ";
        }
        cout<<endl;


        t += TIME_STEP;
        // this_thread::sleep_for(chrono::milliseconds(500));
        Sleep(500);
    }


    // Results

    cout<<Mt.AWT<<" "<<Mt.ATT<<endl;

}