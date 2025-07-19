#include "LoadBalancer.h"
#include <iostream>

/**
 * @brief Construct a new LoadBalancer object.
 * Initializes servers and fills the initial request queue.
 *
 * @param num_servers Number of web servers to create.
 * @param cycles Total number of clock cycles to simulate.
 * @param min_task Minimum task duration for requests.
 * @param max_task Maximum task duration for requests.
 */
LoadBalancer::LoadBalancer(int num_servers, int cycles, int min_task, int max_task)
    : total_cycles(cycles), current_time(0),
      min_task_time(min_task), max_task_time(max_task),
      rng(std::random_device{}()),
      time_dist(min_task_time, max_task_time),
      ip_octet(0, 255)
{
    for (int i = 0; i < num_servers; ++i) {
        servers.push_back(new WebServer());
    }

    // Fill initial queue (servers * 100)
    int initial = num_servers * 100;
    for (int i = 0; i < initial; ++i) {
        generateRequest();
    }
    initial_queue_size = request_queue.size();
}

/**
 * @brief Destroy the LoadBalancer object.
 * Frees all dynamically allocated web servers.
 */
LoadBalancer::~LoadBalancer() {
    for (auto server : servers) {
        delete server;
    }
}

/**
 * @brief Generates a random IPv4 address.
 * @return std::string A formatted IP string like "192.168.0.1"
 */
std::string LoadBalancer::randomIP() {
    return std::to_string(ip_octet(rng)) + "." +
           std::to_string(ip_octet(rng)) + "." +
           std::to_string(ip_octet(rng)) + "." +
           std::to_string(ip_octet(rng));
}
/**
 * @brief Generates a new request with random IPs and processing time.
 */
void LoadBalancer::generateRequest() {
    Request req;
    req.ip_in = randomIP();
    req.ip_out = randomIP();
    req.process_time = time_dist(rng);
    req.arrival_time = current_time;
    request_queue.push(req);
}

/**
 * @brief Assigns available requests to any idle servers.
 */
void LoadBalancer::assignRequests() {
    for (auto& server : servers) {
        if (!request_queue.empty() && !server->isBusy()) {
            Request req = request_queue.front();
            request_queue.pop();
            server->assignRequest(req);
        }
    }
}

/**
 * @brief Processes one cycle on each server (decrement time).
 */
void LoadBalancer::processServers() {
    for (auto& server : servers) {
        server->processCycle();
    }
}
