#include <iostream>
#include <thread>
#include <future>
#include <tuple>

#include "../include/TspAlgorithms.hpp"
#include "../include/TspGenerator.hpp"

#define ITERATIONS 1000000
double to_seconds(double time_in_nanoseconds);

std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();


std::tuple<std::vector<struct City>, double>
run_2opt_algorithm(std::vector<struct City> cycle, int iterations) {
    std::vector<struct City> current_best_cycle = cycle;
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i < iterations ; ++i){ 
        current_best_cycle = algorithms->_2opt(current_best_cycle);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double p =  std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count(); 
    return std::tuple<std::vector<struct City>,double>{current_best_cycle,p};
}

std::pair<std::vector<struct City>,double>
run_random_route(std::vector<struct City> city_list,unsigned int iterations) {
    auto current_shortest_cycle = city_list;
    auto current_shortest_path = algorithms->CalculateCycle(city_list);
    std::vector<struct City> candidate;
    int candidate_path;
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i < iterations ; ++i) {
        candidate = algorithms->RandomRoute(city_list);
        candidate_path = algorithms->CalculateCycle(candidate);
        if(candidate_path < current_shortest_path) {
            current_shortest_path = candidate_path;
            current_shortest_cycle = candidate;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end -begin).count();
    return std::make_pair(current_shortest_cycle,time);
}

std::pair<std::vector<struct City>,double>
run_nearest_neighbor(std::vector<struct City> city_list) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto result = algorithms->NearestNeighbor(city_list,city_list.at(0));
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return std::make_pair(result,time);
}

std::pair<std::vector<struct City>,double>
run_super_nearest_neighbor(std::vector<struct City> city_list) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto result = algorithms->SuperNearestNeighbor(city_list);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return std::make_pair(result,time);
}

std::pair<std::vector<struct City>,double>
run_tabu_search(std::vector<struct City> city_list,int iterations,int size) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto result = algorithms->TabuSearch(city_list,iterations,size);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return std::make_pair(result,time);
}

std::pair<std::vector<struct City>,double>
run_genetic(std::vector <struct City> city_list,int population_size,int iterations) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto result = algorithms->Genetic(city_list,population_size,iterations);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return std::make_pair(result,time);
}

int add(int a) {
    return 2*a;
}
void example(std::function<int(int)> func, int a ) {
    std::cout<<func(a)<<std::endl;
}

std::pair<std::vector<struct City>,double>
test_parametrized_algorithm(std::function<  std::vector<struct City>  (std::vector<struct City>,int,int)> func,std::vector<struct City> city_list,int size,int iterations) {
    auto begin = std::chrono::high_resolution_clock::now();
    auto result = func(city_list,size,iterations);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return std::make_pair(result,time);
}

int main(int argc, char* argv[]) {
    std::unique_ptr<TspGenerator> cityGeneraotr = std::make_unique<TspGenerator>();
    std::vector<struct City> city_list = cityGeneraotr->GenerateSymmetricTsp(50,10,130);
    auto beginning_cycle = algorithms->CalculateCycle(city_list);
    //std::vector<struct City> result;
    auto tmp_cycle = city_list;
    std::cout<<"Testing 2-opt algorithm."<<std::endl;
    for(auto i = 100 ; i < ITERATIONS ; i = i*10) {
        auto result = run_2opt_algorithm(tmp_cycle,i);
        std::cout<<"We started with: "<<beginning_cycle<<", after "<<i<<" iterations we have: "<<algorithms->CalculateCycle(std::get<0>(result))<<". It tooks us: "<<to_seconds(std::get<1>(result))<<" seconds."<<std::endl;

    }
    std::cout<<"Testing random route algorithm."<<std::endl;
    for(auto i = 100 ; i < ITERATIONS ; i = i*10) {
        auto result =  run_random_route(city_list,i);
        std::cout<<"We started with: "<<beginning_cycle<<", after "<<i<<" iterations we have: "<<algorithms->CalculateCycle(result.first)<<". It tooks us: "<<to_seconds(result.second)<<" seconds."<<std::endl;

    }
    std::cout<<"Testing nearest neighbor algorithm."<<std::endl;
    {
        auto result = run_nearest_neighbor(city_list);
        std::cout<<"We started with: "<<beginning_cycle<<", now we have: "<<algorithms->CalculateCycle(result.first)<<". It tooks us: "<<to_seconds(result.second)<<" seconds."<<std::endl;

    }
    std::cout<<"Testing super nearest neighbor algorithm."<<std::endl;
    {
        auto result = run_super_nearest_neighbor(city_list);
        std::cout<<"We started with: "<<beginning_cycle<<", now we have: "<<algorithms->CalculateCycle(result.first)<<". It tooks us: "<<to_seconds(result.second)<<" seconds."<<std::endl;

    }
    std::cout<<"Testing tabu search."<<std::endl;
    for(auto i  = 100 ; i < ITERATIONS ; i = i*10) {
        auto result = run_tabu_search(city_list,50,i);
        std::cout<<"We started with: "<<beginning_cycle<<", now we have: "<<algorithms->CalculateCycle(result.first)<<". It tooks us: "<<to_seconds(result.second)<<" seconds "<<" with "<<i<<" iterations"<<" and neigbor size of: 50"<<std::endl;
    }
    std::cout<<"Testing genetic."<<std::endl;
    for(auto i = 100 ; i < ITERATIONS ; i = i*10) {
        auto result = run_genetic(city_list,i,25);
        std::cout<<"We started with: "<<beginning_cycle<<", now we have: "<<algorithms->CalculateCycle(result.first)<<". It tooks us: "<<to_seconds(result.second)<<" seconds "<<" with "<< "population size of: "<<i<<std::endl;

    }
    return 0;
}


double to_seconds(double time_in_nanoseconds) {
    return time_in_nanoseconds*0.000000001;
}