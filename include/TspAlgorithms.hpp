#pragma once
#include <memory>
#include <random>
#include <ctime>
#include "City.hpp"
class TspAlgorithms {
    private:
        std::unique_ptr<std::mt19937> generator;
    public:
        TspAlgorithms();
        std::vector<struct City> _2opt(std::vector<struct City> cycle);
        std::vector<struct City> RandomRoute(std::vector<struct City> city_list);
        std::vector<struct City> NearestNeighbor(std::vector<struct City> city_list,struct City start_city);
        std::vector<struct City> SuperNearestNeighbor(std::vector<struct City> city_list);
        std::vector<struct City> TabuSearch(std::vector<struct City> city_list,int iterations,int size);
        std::vector<struct City> Genetic(std::vector<struct City> city_list,int population_size,int iterations);

        std::vector<struct City> Cross(std::vector<struct City> parent_a, std::vector<struct City> parent_b);
        std::vector<std::vector<struct City>> GenerateNeighborhood(std::vector<struct City> cycle, int neighborhood_size);
        void _2optSwap(std::vector<struct City> *cycle,int i , int j);
        int CalculateCycle(std::vector<struct City> cycle);
        int Distance(struct City A, struct City B);
};