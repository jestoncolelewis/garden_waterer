cmake_minimum_required(VERSION 3.26)
project(garden_waterer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(garden_waterer
        garden_waterer.ino
        plant.cpp
        plant_cpp.h
        plant.h
        sql.h
        main.c)
