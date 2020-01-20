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

    //unsigned int id;
    char id;
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



typedef struct Data{
    //  initialising life required variables
    int quantity_of_rabbits;
    int quantity_of_wolves;
    unsigned int rabbits_starting_age;
    unsigned int wolves_starting_age;
    int rabbits_life_length;
    int wolves_life_length;
    int lifetime; // weeks
    int rabbits_ripening_age;
    int wolves_ripening_age;
    int rabbit_pregnancy_time;
    int wolf_pregnancy_time;
    int rabbits_children_min;// minimal amount of children in rabbits pair
    int wolves_children_min;// minimal amount of children in wolves pair
    int area;
}Data;

#endif //MONTE_CARLO_METHOD_STRUCTURE_H
