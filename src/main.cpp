#include <bits/stdc++.h>
#include "ETA.h"
#include "Manager.h"
#include "Metrics.h"
#include "InputLoader.h"
#include "Request.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <windows.h>
using namespace std;

int main()
{

    ETA Et;
    Manager M;
    Metrics Mt;

    // Start Python simulation ONCE
    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};

    si.cb = sizeof(si);

    CreateProcessA(
        NULL,
        (LPSTR)"python simulation/main.py",
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    );

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    const double TIME_STEP = 0.5;
    int id = 1;
    double s_time;
    cin >> s_time;

    // s_time = 0;

    vector<Request> requests = InputLoader::loadRequests("test/requests.csv");
    for (const Request R : requests)
    {
        cout << R.timestamp << " " << R.from << " " << R.to << " " << R.people << endl;
    }
    
    
    int i = 0;
    for(double t = 0; t<= s_time; ){ 

        while(i< requests.size() && requests[i].timestamp== t){
            Et.request_assign(id, requests[i].from, requests[i].to, requests[i].people, requests[i].timestamp);
            id++;
            i++;
        }


        // for(int i=0;i< 4; i++){
        //     for(auto it: Et.L[i].stops){
        //         cout<<it<<" ";
        //     }
        //     cout<<endl;
        // }

        // Clear file and write current state
        ofstream out("simulation/Input_coordinate.txt", ios::trunc);

        for(int i=0;i< 4; i++){
            M.update_lift_status(Et.L[i], Mt, Et, t);
            cout<<Et.L[i].pos<<" ";
               // File output for Python
            int fl = (Et.L[i].state== Moving)? 1: 0;
            out << Et.L[i].pos<<" "<< fl<<" ";
        }

        cout<<endl;
        out << endl;
        out.close();

        t += TIME_STEP;

        Sleep(250);
    }

    for(int i=0;i< 4; i++){
        for(auto it: Et.L[i].stops){
            cout<<it<<" ";
        }
        cout<<endl;
    }

    cout<<"Result"<<endl;
    cout<<Mt.ATT<<" "<<Mt.AWT<<endl;

    for(auto it: Et.mp){
        cout<<it.first.first<<" "<<it.first.second<<endl;
    }

}

// g++ src/main.cpp src/InputLoader.cpp src/ETA.cpp src/Metrics.cpp src/Manager.cpp src/Passenger_request.cpp src/Lift.cpp -Iinclude -o main.exe
