#pragma once
#include <vector>
#include <queue>
#include <random>
#include "WebServer.h"
#include "Request.h"

/**
 * @brief Manages a pool of web servers and a queue of incoming requests.
 */
class LoadBalancer {
private:
    std::vector<WebServer*> servers;      
    std::queue<Request> request_queue;     
    int total_cycles;                    
    int current_time;                     
    int min_task_time;                     
    int max_task_time;                    
    int initial_queue_size;                
    std::default_random_engine rng;        
    std::uniform_int_distribution<int> time_dist;
    std::uniform_int_distribution<int> ip_octet;

public:
    LoadBalancer(int num_servers, int cycles, int min_task_time = 1, int max_task_time = 10);
    ~LoadBalancer();

    void run();                   
    void generateRequest();        
    void assignRequests();        
    void processServers();         
    void logStatus() const;        
    std::string randomIP();       
};
