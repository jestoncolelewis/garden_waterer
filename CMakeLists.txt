cmake_minimum_required(VERSION 3.26)
project(garden_waterer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(garden_waterer
        main.c
        serial_tool.h
        sql_tool.h
)
