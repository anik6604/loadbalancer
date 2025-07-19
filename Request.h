#pragma once
#include <string>

struct Request {
    std::string ip_in;
    std::string ip_out;
    int process_time;
    int arrival_time;
};
