//
// Created by cydev on 12.12.2019.
//

#ifndef MONTE_CARLO_METHOD_LIBFUNCTION_H
#define MONTE_CARLO_METHOD_LIBFUNCTION_H

void create_linked_list(QueueList *queueList, int id, unsigned int *age);
void kill_animal_after_some_time(QueueList *animal_list, int time_of_death);
void print_animal_to_file(QueueList *animal_list, char *mode);
void build_pairs(QueueList *list);
void pregnancy_run(QueueList *list, int pregnancy_limit, double *similarity, int children, int array_length);

#endif //MONTE_CARLO_METHOD_LIBFUNCTION_H
