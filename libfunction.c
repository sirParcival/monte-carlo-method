//
// Created by cydev on 12.12.2019.
//
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "structure.h"

void generate_young(QueueList *, double *similarity, int children, int array_length);

void create_linked_list(QueueList *queueList, int id, unsigned int *age)
{
        Animal *new_animal, *current_animal;
        new_animal = (Animal *) malloc(sizeof(Animal));

        if (new_animal)
        {
            new_animal->prev = NULL;
            new_animal->id = id+1;
            if (queueList->number_of_list_elements == 0)
            {

                new_animal->age = *age;
                queueList->first = new_animal;
                queueList->last = new_animal;
                new_animal->next = NULL;
            }
            else
            {
                if (new_animal->id % 40 == 0)
                {
                    (*age)++;
                }
                new_animal->age = *age;
                current_animal = queueList->last;
                current_animal->next = new_animal;
                new_animal->prev = current_animal;
                queueList->last = new_animal;
            }
            queueList->number_of_list_elements++;
        }
}

void kill_animal_after_some_time(QueueList *animal_list, int time_of_death)
{

    Animal *animal = animal_list->first;
    while (animal)
    {
        if (animal->age >= time_of_death)
        {
            if(animal->prev == NULL)
            {
                animal_list->first = animal->next;
                if (animal->next) animal->next->prev = NULL;

                free(animal);
            }
            else if (animal->next == NULL)
            {
                animal_list->last = animal->prev;
                if (animal->prev) animal->prev->next = NULL;

                free(animal);
            }
            else
            {
                animal->prev->next = animal->next;
                animal->next->prev = animal->prev;
                free(animal);
            }
        }
        animal = animal->next;
    }
}

void build_pairs(QueueList *list)
{
    Animal *animal = list->first;
    while (animal)
    {
        if(animal->is_adult && !animal->is_paired)
        {
            if (animal->next)
            {
                Animal *pair_animal = animal->next;
                while (pair_animal)
                {
                    if (pair_animal->is_adult && !pair_animal->is_paired)
                    {
                        animal->is_paired = true;
                        pair_animal->is_paired = true;
                        animal->pair_ptr = pair_animal;
                        break;
                    }
                    pair_animal = pair_animal->next;
                }
            }
        }
        animal = animal->next;
    }
}

void pregnancy_run(QueueList *list, int pregnancy_limit, double *similarity, int children, int array_length)
{

    Animal *animal = list->first;
    while (animal)
    {
        if (animal->is_adult && animal->pair_ptr)
        {
            animal->pregnancy_week++;
            animal->pair_ptr->pregnancy_week++;
            if (animal->pregnancy_week == pregnancy_limit)
            {
                generate_young(list, similarity, children, array_length);
                animal->pregnancy_week = 0;
                animal->pair_ptr->pregnancy_week = 0;
            }
        }
        animal = animal->next;
    }
}

void generate_young(QueueList *list, double *similarity, int children, int array_length)
{

    double random = (double)rand() / (double)RAND_MAX;
    for (int i = 0; i < array_length; i++)
    {
        if (random < similarity[i])
        {
            Animal *young_animal = NULL;
            for (int j = 0; j < children; j++)
            {
                young_animal = (Animal *)malloc(sizeof(Animal));
                if (!young_animal)
                {
                    return;
                }
                young_animal->prev = list->last;
                young_animal->id = list->last->id+1;
                young_animal->pair_ptr = NULL;
                young_animal->age = 0;
                young_animal->is_adult = false;
                young_animal->is_paired = false;
                young_animal->next = NULL;
                list->last->next = young_animal;
                list->last = young_animal;
            }
            break;
        }
        children++;
    }
}

void print_animal_to_file(QueueList *animal_list, char *mode)
{
    FILE *outfile = NULL;
    char *outfilename = "../output.csv";
    outfile = fopen(outfilename, mode);
    Animal *animal = animal_list->first;
    while (animal)
    {
        fprintf(outfile,"%d, %d, %d, %d, %p, %p\n", animal->id, animal->age, animal->is_adult, animal->is_paired, animal->pair_ptr, animal);
        animal = animal->next;
    }
    fprintf(outfile, "\n");
    fclose(outfile);
}

void hunting_on_rabbits(QueueList *rabbits, QueueList *wolves, int week, double rabbits_per_kits)
{
    double x = (double)rand()/(double)RAND_MAX;
    Animal *rabbit = rabbits->first;
    Animal *wolf = wolves->first;
    while (wolf)
    {
        double lambda = 1 / (rabbits_per_kits * 0.01);
        double s = -lambda*log(x);
        for (int day = 0; day < 7; day++)
        {
            if (rabbit)
            {
                if((week - wolf->last_week_wolf_have_eaten) >= 4)
                {
                    if(wolf->prev == NULL)
                    {
                        wolves->first = wolf->next;
                        if (wolf->next) wolf->next->prev = NULL;

                         free(wolf);
                    }
                    else if (wolf->next == NULL)
                    {
                        wolves->last = wolf->prev;
                        if (wolf->prev) wolf->prev->next = NULL;

                        free(wolf);
                    }
                    else
                    {
                        wolf->prev->next = wolf->next;
                        wolf->next->prev = wolf->prev;
                        free(wolf);
                    }
                }
                if (s > 1)
                {
                    s--;
                    continue;
                } else{
                    double chance = (double)rand() / (double)RAND_MAX;
                    if (chance < (0.8 - 0.2 * (week - wolf->last_week_wolf_have_eaten)))
                    {
                        rabbits->first = rabbit->next;
                        if (rabbit->next)
                        {
                            rabbit->next->prev = NULL;
                            rabbit = rabbit->next;
                            free(rabbit);
                        } else{
                            rabbits->first = NULL;
                            rabbits->last = NULL;
                        }


                        wolf->last_week_wolf_have_eaten = week;
                    }
                }
            }
        }
        wolf = wolf->next;
    }

}

void flush_animals_from_memory(QueueList *list)
{
    Animal *animal = list->first;
    while (animal)
    {
        Animal *animal_next = animal->next;
        free(animal);
        animal = animal_next;
    }
}