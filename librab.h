//
// Created by cydev on 05.12.2019.
//

#ifndef MONTE_CARLO_METHOD_LIBRAB_H
#define MONTE_CARLO_METHOD_LIBRAB_H


#include "structure.h"

void generate_rabbits(Rabbit **r, int id);
void print_rabbits(Rabbit *r, double count);
void flush_rabbits_from_memory(Rabbit *r);
void kill_rabbits_after_five_years(Rabbit *r);
void create_linked_list_of_rabbits(Rabbit *r, unsigned int age);
void build_rabbits_in_pairs(Rabbit *r);
void pregnancy_run_for_rabbits(Rabbit *r);
Rabbit *found_last_rabbit(Rabbit *ptr);

#endif //MONTE_CARLO_METHOD_LIBRAB_H
