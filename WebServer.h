#pragma once
#include "Request.h"

/**
 * @brief Represents a web server that can process requests.
 */
class WebServer {
private:
    bool busy;
    Request current_request;
    int time_remaining;

public:
    WebServer();
    bool isBusy() const;
    void assignRequest(const Request& req);
    void processCycle();
    bool isDone() const;
};
