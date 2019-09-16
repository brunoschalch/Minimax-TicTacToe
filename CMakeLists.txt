cmake_minimum_required(VERSION 3.14)
project(TicTacToeMinimax)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToeMinimax main.cpp Tree.cpp Tree.h Node.cpp Node.h)