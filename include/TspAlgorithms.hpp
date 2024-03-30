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
        // void NearestNeighbor(struct City first_city);
        // void SuperNearestNeighbor();
        // std::vector<struct City> RandomRoute();
        //void TabuSearch();
        //void Genetic();
        void _2optSwap(std::vector<struct City> *cycle,int i , int j);
        int CalculateCycle(std::vector<struct City> cycle);
        int Distance(struct City A, struct City B);
};