cmake_minimum_required(VERSION 3.15)
project(1d_gridworld CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(xtensor REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(1d_gridworld main.cpp)
target_link_libraries(1d_gridworld PRIVATE
    xtensor
    SQLite3::SQLite3
)

install(TARGETS 1d_gridworld DESTINATION bin)