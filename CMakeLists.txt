cmake_minimum_required(VERSION 3.9)
project(knapsack_problem)

set(CMAKE_CXX_STANDARD 11)

add_executable(knapsack_problem pmr.cpp pmr.h pmr_e_h.cpp pmr_e_h.h gurobi_c++.h gurobi_c.h)

target_link_libraries(knapsack_problem ${CMAKE_SOURCE_DIR}/libgurobi_c++.a)
