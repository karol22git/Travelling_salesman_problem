#include "../include/TspReader.hpp"
#include <iostream>
#include <fstream>
#include <vector>

TspReader::TspReader(){}

void TspReader::RaedFile(std::string file) {
    std::vector<struct City> city_list;
    std::string line;
    int* nubmers;
    ifstream MyFile(file);
    while(getline(MyFile,line)) {
        if(line.compare("Data:")==0) {
            break;
        }
    }
    while(getline(MyFile,line)) {
        numbers = ParseCoordinates(line);
        struct City new_city;
        new_city.x = numbers[0];
        new_city.y = numbers[1];
        city_list.push_back(new_city);`
    }
    return city_list;
}

int* TspReader::ParseCoordinates(std::string line) {
    int* result = (int*) malloc(2*sizeof(int));
    std::string string_formatted_numbers[2];
    unsigned int index = 0;
    for(int i = 0 ; i < line.length() ; ++i) {
        if(line[i] == ';' ) {
            index = i;
            break;
        }
    }
    string_formatted_numbers[0] = line.substr(0,index);
    string_formatted_numbers[1] = line.substr(index+1,line.length());

    result[0] = std::stoi(string_formatted_numbers[0]);
    result[1] = std::stoi(string_formatted_numbers[1]);

    return result;
}`