cmake_minimum_required(VERSION 3.14)
project(TeoriaDosGrafos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TeoriaDosGrafos
        Aresta.cpp
        Aresta.h
        Grafo.cpp
        Grafo.h
        main.cpp
        No.cpp
        No.h

        )
