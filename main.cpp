#include <iostream>
#include "LoadBalancer.h"

int main() {
    int num_servers=10;
    int num_cycles=100000;

    std::cout << "Starting Load Balancer Simulation\n";
    std::cout << "Servers: " << num_servers << ", Cycles: " << num_cycles << "\n";

    LoadBalancer lb(num_servers, num_cycles);
    lb.run();

    return 0;
}
