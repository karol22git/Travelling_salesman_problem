#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites

#include "../include/TspReader.hpp"
#include "../include/City.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (TspReaderClassTest ) 

BOOST_AUTO_TEST_CASE(test1, *boost::unit_test::description("Testing parsing data with TspReader class")) {
    int* numbers;
    std::unique_ptr<TspReader> reader = std::make_unique<TspReader>();
    std::string string_array[3] = {"34;35", "100000;12354","123456;9999999"};

    numbers = reader->ParseCoordinates(string_array[0]);
    BOOST_CHECK(numbers[0] == 34);
    BOOST_CHECK(numbers[1] == 35);
    
    numbers = reader->ParseCoordinates(string_array[1]);
    BOOST_CHECK(numbers[0] == 100000);
    BOOST_CHECK(numbers[1] == 12354);

    numbers = reader->ParseCoordinates(string_array[2]);
    BOOST_CHECK(numbers[0] == 123456);
    BOOST_CHECK(numbers[1] == 9999999);
}


BOOST_AUTO_TEST_SUITE_END()