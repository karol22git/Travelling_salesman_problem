#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites


#include "../include/TspGenerator.hpp"
#include "../include/City.hpp"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE( TspGeneratorClassTest )

BOOST_AUTO_TEST_CASE(test1, *boost::unit_test::description("Testing generating data with TspGenerator class")) {
    std::unique_ptr<TspGenerator> generator = std::make_unique<TspGenerator>();
    auto min = 5;
    auto max = 100;
    auto n = 50;

    std::vector<struct City> test_dataset = generator->GenerateSymmetricTsp(n, min, max);
    BOOST_CHECK(test_dataset.size() == n);
    for(auto v : test_dataset) {
        BOOST_CHECK(v.x <= max && v.x >= min);
        BOOST_CHECK(v.y <= max && v.y >= min);
    }

}

BOOST_AUTO_TEST_SUITE_END()

