#pragma once
#include <string>

/**
 * @brief Represents a single request with input/output IPs and processing time.
 */
struct Request {
    std::string ip_in;        ///< IP address of the requester
    std::string ip_out;       ///< Destination IP address
    int process_time;         ///< Time needed to process the request
    int arrival_time;         ///< The cycle at which the request arrived
};
