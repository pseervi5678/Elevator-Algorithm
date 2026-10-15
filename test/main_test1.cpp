#include <bits/stdc++.h>
#include "ETA.h"
// #include "Manager.h"
// #include "Metrics.h"
#include "InputLoader.h"
#include "Request.h"
// #include <thread>
// #include <chrono>
// #include <windows.h>
using namespace std;

int main(){
    

    ETA Et;

    const double TIME_STEP = 0.5;
    int id = 1;
    double s_time;
    cin>> s_time;

    // s_time = 0;

    vector<Request> requests = InputLoader :: loadRequests("test/requests.csv");
    for(const Request R: requests){
        cout<<R.timestamp<<" "<<R.from<<" "<<R.to<<" "<<R.people<<endl;
    }

    Et.request_assign(1, 1, 3, 2, 1.5);
    Et.request_assign(2, 4, 8, 1, 2);
    

    // for(auto it: requests){
    //     cout<<it.timestamp<<" "<<it.from<<" "<<it.to<<" "<<it.people<<endl;
    // }

    // cout<<s_time<<endl;

    Et.L[2].curr_flore = 8;
    Et.L[2].stops.clear();
    Et.L[2].stops.insert(8);
    Et.L[2].stops.insert(0);
    Et.L[2].curr_dir = -1;

    Et.L[3].curr_flore = 6;
    Et.L[3].stops.clear();
    Et.L[3].stops.insert(6);
    Et.L[3].stops.insert(0);
    Et.L[3].curr_dir = -1;

    Et.request_assign(3, 7, 0, 1, 6);
    Et.request_assign(4, 2, 4, 1, 7);
    Et.request_assign(5, 5, 4, 3, 8);
    Et.request_assign(6, 4, 3, 2, 9);
    Et.request_assign(7, 2, 0, 3, 10);
    Et.request_assign(8, 1, 0, 2, 11);


    for(int i=0;i< 4; i++){
        for(auto it: Et.L[i].stops){
            cout<<it<<" ";
        }
        cout<<endl;
    }

}

// g++ src\main.cpp src\InputLoader.cpp src\ETA.cpp src\Lift.cpp src\Passenger_request.cpp -Iinclude -o main.exe