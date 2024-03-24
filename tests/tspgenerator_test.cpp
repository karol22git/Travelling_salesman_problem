#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites


#include "../include/TspGenerator.hpp"
#include "../include/City.hpp"
#include <boost/test/unit_test.hpp>
#include <ctime>

BOOST_AUTO_TEST_SUITE( TspGeneratorClassTest )

BOOST_AUTO_TEST_CASE(test1, *boost::unit_test::description("Testing generating data with TspGenerator class")) {
    std::string exampleseed = "exampleseed";
    unsigned seed2 = 10000000;
    std::seed_seq seed1 (exampleseed.begin(),exampleseed.end());
    std::unique_ptr<TspGenerator> generator = std::make_unique<TspGenerator>();
    //TspGenerator* generator = new TspGenerator();
    std::vector<struct City> test_dataset = generator->GenerateSymmetricTsp(50,5,100);
    generator->SaveDataset("../data/data_test.txt",test_dataset);
}

BOOST_AUTO_TEST_SUITE_END()