#include <iostream>
#include "LoadBalancer.h"

int main() {
    int num_servers, num_cycles;

    std::cout << "Enter number of servers: ";
    std::cin >> num_servers;

    std::cout << "Enter number of clock cycles: ";
    std::cin >> num_cycles;

    LoadBalancer lb(num_servers, num_cycles);
    lb.run();

    return 0;
}
