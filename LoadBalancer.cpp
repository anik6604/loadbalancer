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
    detailed_log.open("log.txt");
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
    detailed_log.close();
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
    detailed_log << "[Cycle " << current_time << "] New Request — From: " 
             << req.ip_in << " To: " << req.ip_out 
             << " | Time: " << req.process_time << " cycles\n";
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
            detailed_log << "[Cycle " << current_time << "] Assigned to Server — From: " 
                << req.ip_in << " To: " << req.ip_out 
                << " | Duration: " << req.process_time << " cycles\n";
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
/**
 * @brief Runs the main simulation loop for the configured number of clock cycles.
 */
void LoadBalancer::run() {
    std::cout << "Starting simulation for " << total_cycles << " cycles...\n";
    std::cout << "Initial queue size: " << initial_queue_size << "\n";

    for (current_time = 0; current_time < total_cycles; ++current_time) {
        // Generate a new request every 3 cycles
        if (current_time % 3 == 0) {
            generateRequest();
        }

        assignRequests();
        processServers();
    }

    logStatus();
}

/**
 * @brief Logs key stats at the end of the simulation.
 */
void LoadBalancer::logStatus() {
    int active_servers = 0;
    int idle_servers = 0;

    for (const auto& server : servers) {
        if (server->isBusy()) active_servers++;
        else idle_servers++;
    }

    std::cout << "Simulation complete.\n";
    std::cout << "Final queue size: " << request_queue.size() << "\n";
    std::cout << "Task time range: " << min_task_time << " - " << max_task_time << "\n";
    std::cout << "Active servers at end: " << active_servers << "\n";
    std::cout << "Idle servers at end: " << idle_servers << "\n";
    detailed_log << "\n================== Simulation Summary ==================\n";
    detailed_log << "Total Cycles: " << total_cycles << "\n";
    detailed_log << "Initial Queue Size: " << initial_queue_size << "\n";
    detailed_log << "Final Queue Size: " << request_queue.size() << "\n";
    detailed_log << "Task Time Range: " << min_task_time << " - " << max_task_time << "\n";
    detailed_log << "Active Servers at End: " << active_servers << "\n";
    detailed_log << "Idle Servers at End: " << idle_servers << "\n";
    detailed_log << "========================================================\n";
}
