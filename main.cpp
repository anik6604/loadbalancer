#include <iostream>
#include "LoadBalancer.h"

int main() {
    int servers, cycles;
    std::cout << "Enter number of servers: ";
    std::cin >> servers;
    std::cout << "Enter number of cycles: ";
    std::cin >> cycles;

    LoadBalancer lb(servers, cycles);
    lb.run();

    return 0;
}
