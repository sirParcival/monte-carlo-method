//
// Created by cydev on 05.12.2019.
//

#ifndef MONTE_CARLO_METHOD_LIBWOLF_H
#define MONTE_CARLO_METHOD_LIBWOLF_H



void generate_wolves(Wolf **pWolves, int id);
void create_linked_list_of_wolves(Wolf *w, unsigned int age);
void kill_wolves_after_ten_years(Wolf *w);
void build_wolves_in_pairs(Wolf *w);
void pregnancy_run_for_wolves(Wolf *w);
Wolf *found_last_wolf(Wolf *ptr);

void print_wolves(Wolf *w, double count);
void flush_wolves_from_memory(Wolf *w);

int hunting_on_rabbits(int week, Rabbit *r, double rabbits_per_kic, Wolf *w);
#endif //MONTE_CARLO_METHOD_LIBWOLF_H
