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

    BOOST_CHECK(algorithms->CalculateCycle(_2opt_cycle) <= algorithms->CalculateCycle(cycle));
    
}

BOOST_AUTO_TEST_CASE(test3, *boost::unit_test::description("testing random rounte algorithms")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();
    std::vector<struct City> cycle;
    for(auto i = 0 ; i < 50; ++i) {
        struct City new_city {i,i};
        cycle.push_back(new_city);
    }
    auto random_route_cycle = algorithms->RandomRoute(cycle);

    BOOST_CHECK(random_route_cycle.size() == random_route_cycle.size());
    for(auto c : cycle) {
        BOOST_CHECK(std::find(cycle.begin(), cycle.end(),c) != cycle.end());
    }
    auto it = std::adjacent_find(random_route_cycle.begin(),random_route_cycle.begin()+random_route_cycle.size());
    BOOST_CHECK(it == random_route_cycle.end());
}

BOOST_AUTO_TEST_CASE(test4, *boost::unit_test::description("testing naerest neighbor algorithm")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();

    std::unique_ptr<std::mt19937> generator = std::make_unique<std::mt19937>(time(NULL));
    std::vector<struct City> cycle = {{0,0},{1,1},{2,2},{10,10}};
    
    struct City city_a = {0,0};

    auto nearest_neighbor_cycle = algorithms->NearestNeighbor(cycle,city_a);
    BOOST_CHECK(nearest_neighbor_cycle.at(0) == city_a);
    city_a = {1,1};
    BOOST_CHECK(nearest_neighbor_cycle.at(1) == city_a);
    city_a = {2,2};
    BOOST_CHECK(nearest_neighbor_cycle.at(2) == city_a);
    city_a = {10,10};
    BOOST_CHECK(nearest_neighbor_cycle.at(3) == city_a);
}

BOOST_AUTO_TEST_CASE(test5,*boost::unit_test::description("testing super nearest neighbor algorithm")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();
    std::vector<struct City> cycle = {{10,10},{2,2},{1,1},{0,0}};
    std::vector<struct City> shortest_cycle = {{0,0},{1,1},{2,2},{10,10}};
    auto super_nearest_neighbor_cycle = algorithms->SuperNearestNeighbor(cycle);
    BOOST_CHECK(super_nearest_neighbor_cycle.size() == shortest_cycle.size());
    BOOST_CHECK(algorithms->CalculateCycle(shortest_cycle)==algorithms->CalculateCycle(super_nearest_neighbor_cycle));
}

BOOST_AUTO_TEST_CASE(test6, *boost::unit_test::description("testing tabu search")) {
    /*
    ????
    */
}

BOOST_AUTO_TEST_CASE(test7,*boost::unit_test::description("testing genetic algorithm")) {
    std::unique_ptr<TspAlgorithms> algorithms = std::make_unique<TspAlgorithms>();
    std::vector<struct City> parent_a ;
    std::vector<struct City> parent_b;
    auto population_size = 50000;
    
    for(auto i = 0 ; i < 25; ++i) {
        struct City new_city {i,i};
        parent_a.push_back(new_city);
    }
    for(auto i = 0 ; i < 25 ; ++i) {
        struct City new_city {i,i};
        parent_b.push_back(new_city);
    }
    std::vector<struct City> descendant = algorithms->Cross(parent_a,parent_b);
    BOOST_CHECK(descendant.size() == parent_a.size());
    for(auto c: parent_a) {
        BOOST_CHECK(std::find(descendant.begin(),descendant.end(),c) != descendant.end());
    }
    BOOST_CHECK(std::adjacent_find(descendant.begin(),descendant.end()) == descendant.end());
    auto result = algorithms->Genetic(parent_a,population_size,5);
    BOOST_CHECK(result.size() == parent_a.size());
    BOOST_CHECK(std::adjacent_find(result.begin(),result.end()) == result.end());
    for(auto c: parent_a) {
        BOOST_CHECK(std::find(result.begin(),result.end(),c) != result.end());
    }
}
BOOST_AUTO_TEST_SUITE_END()