cmake_minimum_required(VERSION 3.15)
project(monte-carlo-method C)

set(CMAKE_C_STANDARD 99)

add_executable(monte-carlo-method structure.h  main.c rab.c wolves.c librab.h libwolf.h)
target_link_libraries(monte-carlo-method m)