#include "../include/TspAlgorithms.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
TspAlgorithms::TspAlgorithms() {
    generator  = std::make_unique<std::mt19937>(time(NULL));
}



std::vector<struct City> TspAlgorithms::TabuSearch(std::vector<struct City> city_list,int size,int iterations) {
    std::vector<std::vector<struct City>> tabu_list;
    auto beginning_cycle = RandomRoute(city_list);
    tabu_list.push_back(beginning_cycle);
    std::vector<std::vector<struct City>> neighborhood;
    auto current_shortest_path = CalculateCycle(beginning_cycle);
    auto best_candidate = beginning_cycle;
    int candidate_path;
    for(int i = 1 ; i < iterations ; ++i) {
        neighborhood = GenerateNeighborhood(best_candidate,size);
        for(auto r : neighborhood) {
            candidate_path = CalculateCycle(r);
            if(candidate_path < current_shortest_path)  {
                if(std::find(tabu_list.begin(),tabu_list.end(),r) == tabu_list.end()) {
                    current_shortest_path = candidate_path;
                    best_candidate = r;
                }
            }
        }
        if(tabu_list.size() >10) {
             tabu_list.pop_back();
        }
        tabu_list.push_back(best_candidate);
    }
    return best_candidate;
}

std::vector<struct City> TspAlgorithms::SuperNearestNeighbor(std::vector<struct City> city_list) {
    auto current_best_cycle = NearestNeighbor(city_list,city_list.at(0));
    auto shortest_path = CalculateCycle(current_best_cycle);
    std::vector<struct City> candidate;
    int candidate_path;
    for(auto it = city_list.begin() + 1 ; it != city_list.end(); ++it) {
        candidate = NearestNeighbor(city_list,*it);
        candidate_path = CalculateCycle(candidate);
        if(candidate_path < shortest_path) {
            shortest_path = candidate_path;
            current_best_cycle = candidate;
        }
    }
    return current_best_cycle;
}

std::vector<struct City> TspAlgorithms::NearestNeighbor(std::vector<struct City> city_list,struct City start_city) {
    std::vector<struct City> cycle;
    int tmp_distance;
    city_list.erase(std::find(city_list.begin(),city_list.end(),start_city));
    cycle.push_back(start_city);
    auto current_city = start_city;
    int candidate_city_index;
    struct City candidate;
    int candidate_distance;
    std::vector<struct City>::iterator candidate_iterator;
    do {
        candidate_city_index = (*generator)() % city_list.size();
        candidate = city_list.at(candidate_city_index);
        candidate_distance = Distance(current_city,candidate);
        candidate_iterator = city_list.begin() + candidate_city_index;
        for(auto it = city_list.begin() ; it != city_list.end() ; ++it) {
            tmp_distance = Distance(*it,current_city);
            if(tmp_distance < candidate_distance) {
                candidate_distance = tmp_distance;
                candidate = *it;
                candidate_iterator = it;
            }
        }
    cycle.push_back(candidate);
    current_city = candidate;
    city_list.erase(candidate_iterator);
    } while(!city_list.empty()); 

    return cycle;
}

std::vector<struct City> TspAlgorithms::RandomRoute(std::vector<struct City> city_list) {
    std::vector<struct City> cycle;
    int random_number;
    while(!city_list.empty()) {
        random_number = (*generator)() % city_list.size();
        cycle.push_back(city_list.at(random_number));
        city_list.erase(city_list.begin() + random_number);
    }
    return cycle;
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

std::vector<struct City> TspAlgorithms::Genetic(std::vector <struct City> city_list,int population_size,int iterations) {
    std::vector<std::vector<struct City>> population;
    std::map<int,std::vector<struct City>> cycle_to_city_map;;
    std::vector<std::vector<struct City> > next_generation;
    std::vector<int> cycles;
    int cycle;
    for(int i = 0 ; i < population_size ; ++i) {
        population.push_back(RandomRoute(city_list));
    }

    do {
        for(auto c: population) {
            cycle = CalculateCycle(c);
            cycle_to_city_map[cycle] = c;
            cycles.push_back(cycle);
        }
        std::sort(cycles.begin(),cycles.end());
        for(auto it = cycles.begin()+1 ; it!= cycles.end()  ; ++it) {
            next_generation.push_back(Cross(cycle_to_city_map[*(it)],cycle_to_city_map[*(it-1)]));
            //++it;
        }
        cycle_to_city_map.clear();
        cycles.clear();
        population = next_generation;
        next_generation.clear();
        --iterations;
    } while(iterations>1);
    auto best_path = CalculateCycle(population.at(0));
    auto best_cycle = population.at(0);
    for(auto c : population) {
        if(best_path > CalculateCycle(c)) {
            best_path = CalculateCycle(c);
            best_cycle = c;
        }
    }
    return best_cycle;//population.at(0);
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


std::vector<std::vector<struct City>> TspAlgorithms::GenerateNeighborhood(std::vector<struct City> cycle, int neighborhood_size) {
    std::vector<std::vector<struct City>> neighborhood;
    for(int i = 0 ; i < neighborhood_size ; ++i) {
        neighborhood.push_back(_2opt(cycle));
    }
    return neighborhood;
}

std::vector<struct City> TspAlgorithms::Cross(std::vector<struct City> parent_a, std::vector<struct City> parent_b) {
    auto cycle_size = parent_a.size();
    int left,right;
    if(cycle_size%2 != 0) {
        left = (int) cycle_size/2;
        right = cycle_size - left;
    }
    else {
        left = cycle_size/2;
        right = left;
    }
    std::vector<struct City> gens_from_a;
    std::vector<struct City> gens_from_b;
    for(auto it = parent_a.begin() ; it != parent_a.begin() + left; ++it) {
        gens_from_a.push_back(*it);
    }
    for(auto it = parent_b.begin() ;right > 0 ; ++it) {
        if(std::find(gens_from_a.begin(),gens_from_a.end(),*it) == gens_from_a.end()) {
            gens_from_b.push_back(*it);
            --right;
        }
    }
    gens_from_a.insert(gens_from_a.end(),gens_from_b.begin(),gens_from_b.end());
    return gens_from_a;
}