//
// Created by cydev on 12.12.2019.
//

#ifndef MONTE_CARLO_METHOD_STRUCTURE_H
#define MONTE_CARLO_METHOD_STRUCTURE_H

#include <stdbool.h>

typedef struct Animal
{
    struct Animal *pair_ptr;
    struct Animal *prev;
    struct Animal *next;

    double last_week_wolf_have_eaten;

    unsigned int id;
    unsigned int age;
    unsigned int pregnancy_week;

    bool is_adult;
    bool is_paired;


}Animal;



typedef struct QueueList
{
    Animal *first;
    Animal *last;

    unsigned int number_of_list_elements;
}QueueList;

#endif //MONTE_CARLO_METHOD_STRUCTURE_H
