cmake_minimum_required(VERSION 3.15)
project(polynomial)

set(CMAKE_CXX_STANDARD 17)                                                                   
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -fsanitize=undefined -O0 -g")

find_package(GSL REQUIRED)
find_package(Boost REQUIRED)

add_library(poly_lib
    src/utils.cpp
    src/Multivariate.cpp
    src/Univariate.cpp
    src/LinAlgb.cpp
    src/Numerical.cpp                                                                        
    src/Methods.cpp
)

target_include_directories(poly_lib PUBLIC src/)
target_link_libraries(poly_lib PUBLIC 
    GSL::gsl 
    GSL::gslcblas
    Boost::boost
)

add_executable(test_case test/test_case.cpp)
target_link_libraries(test_case PRIVATE poly_lib)

add_executable(test_mult test/mult.cpp)
target_link_libraries(test_mult PRIVATE poly_lib)