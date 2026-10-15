#ifndef INPUT_LOADER_H
#define INPUT_LOADER_H

#include <vector>
#include <string>
#include "Request.h"

class InputLoader
{
public:
    static std::vector<Request> loadRequests(const std::string& filename);
};

#endif