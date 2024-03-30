#include "../include/TspAlgorithms.hpp"
#include <cmath>
#include <iostream>
//struct City* TspAlgorithms::RandomRoute() {

//}
TspAlgorithms::TspAlgorithms() {
    generator  = std::make_unique<std::mt19937>(time(NULL));
}

std::vector<struct City> TspAlgorithms::_2opt(std::vector<struct City> cycle) {
    auto i = (*generator)() % cycle.size();
    auto j = (*generator)() % cycle.size();
    while(i==j) {
        j = (*generator)() % cycle.size();
    }
    auto cycle_length = CalculateCycle(cycle);
    _2optSwap(&cycle,i,j);
    auto cycle_length_after_2opt = CalculateCycle(cycle);
    if(cycle_length_after_2opt > cycle_length) {
        _2optSwap(&cycle,j,i);
    }
    return cycle;
}

int TspAlgorithms::CalculateCycle(std::vector<struct City> cycle) {
    auto result = 0;
    for(auto it = cycle.begin() + 1 ; it != cycle.end() ; ++it) {
        result = result + Distance(*it,*(it-1));
    }
    return result;
}

int TspAlgorithms::Distance(struct City A, struct City B) {
    return std::round(std::sqrt((A.x - B.x)*(A.x-B.x) + (A.y - B.y)*(A.y - B.y)));
}

void TspAlgorithms::_2optSwap(std::vector<struct City> *cycle, int i, int j) {
    iter_swap(cycle->begin() +i, cycle->begin() +j);
}