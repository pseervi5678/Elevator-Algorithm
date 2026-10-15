#include "InputLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Request> InputLoader::loadRequests(const string& filename)
{
    vector<Request> requests;

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file: "
             << filename << endl;

        return requests;
    }

    string line;

    // Skip header
    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string value;

        Request req;

        // timestamp
        getline(ss, value, ',');
        req.timestamp = stod(value);

        // from
        getline(ss, value, ',');
        req.from = stoi(value);

        // to
        getline(ss, value, ',');
        req.to = stoi(value);

        // people
        getline(ss, value, ',');
        req.people = stoi(value);

        requests.push_back(req);
    }

    return requests;
}