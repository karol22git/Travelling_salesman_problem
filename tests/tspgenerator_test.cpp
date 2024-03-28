#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites


#include "../include/TspGenerator.hpp"
#include "../include/City.hpp"
#include <boost/test/unit_test.hpp>
#include <ctime>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE( TspGeneratorClassTest )

BOOST_AUTO_TEST_CASE(test1, *boost::unit_test::description("Testing generating data with TspGenerator class")) {
    std::unique_ptr<TspGenerator> generator = std::make_unique<TspGenerator>();

    unsigned int min = 5;
    unsigned int max = 100;
    unsigned int n = 50;
    
    std::string file = "../data/data_test.txt";
    std::vector<struct City> test_dataset = generator->GenerateSymmetricTsp(n,min,max);
    generator->SaveDataset(file,test_dataset);
    std::ifstream MyFile(file);



}

BOOST_AUTO_TEST_SUITE_END()