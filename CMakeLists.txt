cmake_minimum_required(VERSION 3.12)
project(wayloChorderUtility)


find_package(Boost 1.68.0 COMPONENTS system filesystem serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(wayloChorderUtility main.cpp)
target_link_libraries(wayloChorderUtility ${Boost_LIBRARIES})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -lboost_system ")


