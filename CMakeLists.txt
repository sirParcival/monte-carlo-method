cmake_minimum_required(VERSION 3.10)
project(monte_carlo_method C)

set(CMAKE_C_STANDARD 99)

add_executable(monte_carlo_method main.c structure.h libfunction.c libfunction.h)
target_link_libraries(monte_carlo_method m)
install(TARGETS monte_carlo_method DESTINATION /usr/bin/)
