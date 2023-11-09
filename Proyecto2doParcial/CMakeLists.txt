cmake_minimum_required(VERSION 3.26)
project(SfmlBala)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto2doParcial main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(Proyecto2doParcial PRIVATE box2d::box2d)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(Proyecto2doParcial PRIVATE sfml-system sfml-network sfml-graphics sfml-window)