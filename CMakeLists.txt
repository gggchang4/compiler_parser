cmake_minimum_required(VERSION 3.10)
project(ToyCParser CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(SOURCES
    main.cpp
    lexer.cpp
    parser.cpp
)

add_executable(parser ${SOURCES})

install(TARGETS parser DESTINATION bin)

