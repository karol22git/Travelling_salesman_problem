#include <string>
#include <random>
#include <memory>
class TspGenerator {
    private:
        std::unique_ptr<std::mt19937> generator;
    public:
        TspGenerator();
        std::vector<struct City> GenerateSymmetricTsp(unsigned int how_many, unsigned int min, unsigned int max);
        void SaveDataset(std::string file_name, std::vector<City> city_list);
        struct City GenerateRadomCity(unsigned int min, unsigned int max);


};