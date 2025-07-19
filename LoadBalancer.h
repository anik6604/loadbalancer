#pragma once
#include <vector>
#include <queue>
#include "Request.h"
#include "WebServer.h"

class LoadBalancer {
private:
    std::vector<WebServer*> servers;
    std::queue<Request> request_queue;
    int total_cycles;
    int current_time;
    int min_task_time;
    int max_task_time;

public:
    LoadBalancer(int num_servers, int cycles, int min_task_time = 1, int max_task_time = 10);
    ~LoadBalancer();
    void run();
    void generateRequest();
    void assignRequests();
    void processServers();
    void logStatus();
};
