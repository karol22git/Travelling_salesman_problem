#include "../include/TspGenerator.hpp"
#include "../include/City.hpp"
#include <iostream>
#include <fstream>

TspGenerator::TspGenerator() {
    generator  = std::make_unique<std::mt19937>(125230);
}

std::vector<struct City> TspGenerator::GenerateSymmetricTsp(unsigned int how_many, unsigned int min, unsigned int max) {
    std::vector<struct City> city_list;
    for(int i = 0 ; i < how_many ; ++i) {
        struct City new_city;
        new_city.x = ((*generator)() % max) + min;
        new_city.y = ((*generator)() % max) + min;
        city_list.push_back(new_city);
    }
    return city_list;
}

void TspGenerator::SaveDataset(std::string file_name,std::vector<City> city_list) {
    std::ofstream file(file_name);
    for(auto it = begin(city_list) ; it != end(city_list) ; ++it) {
        file << it->x;
        file << ";";
        file << it->y;
        file << ";\n"; 
    }
    file.close();
    return;
}