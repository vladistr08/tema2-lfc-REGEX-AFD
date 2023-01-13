cmake_minimum_required(VERSION 3.23)
project(tema2_lfc_REGEX_AFD)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp DeterministicFiniteAutomaton.h FiniteAutomaton.h UsefulMethods.h DeterministicFiniteAutomaton.cpp FiniteAutomaton.cpp UsefulMethods.cpp)

add_executable(tema2_lfc_REGEX_AFD ${SOURCES})
