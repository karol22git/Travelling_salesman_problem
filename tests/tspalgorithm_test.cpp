#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites


#include "../include/TspAlgorithms.hpp"
#include <boost/test/unit_test.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE (TspAlgorithmsClassTests )

BOOST_AUTO_TEST_CASE(test1, *boost::unit_test::description("testing calculating cycle")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();
    std::vector<struct City> cycle;
    struct City city_a{0,0};
    struct City city_b{2,0};
    BOOST_CHECK(algorithms->Distance(city_a,city_b)==2);
    
    city_a = {0,0};
    city_b = {0,2};
    BOOST_CHECK(algorithms->Distance(city_a,city_b)==2);

    city_a = {15,20};
    city_b = {3,4};
    BOOST_CHECK(algorithms->Distance(city_a,city_b)==20);

    struct City city_c {15,20};
    city_a = {1,1};
    city_b = {5,5};
    cycle.push_back(city_c);
    cycle.push_back(city_a);
    cycle.push_back(city_b);

    BOOST_CHECK(algorithms->CalculateCycle(cycle)==30);
}

BOOST_AUTO_TEST_CASE(test2, *boost::unit_test::description("testing 2opt algorithm")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();
    std::vector<struct City> cycle;
    for(auto i = 0 ; i < 50; ++i) {
        struct City new_city {i,i};
        cycle.push_back(new_city);
    }
    struct City city_a {100,100};
    cycle.push_back(city_a);


    algorithms->_2optSwap(&cycle,50,0);
    BOOST_CHECK(cycle.at(0) == city_a);

    algorithms->_2optSwap(&cycle,0,25);
    BOOST_CHECK(cycle.at(25)==city_a);

    auto _2opt_cycle = algorithms->_2opt(cycle);
    BOOST_CHECK(_2opt_cycle.size() == cycle.size());
    
}

BOOST_AUTO_TEST_SUITE_END()