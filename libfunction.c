//
// Created by cydev on 12.12.2019.
//
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include <string.h>

void generate_young(QueueList *, double *similarity, int children, int array_length);
void get_data_from_datalist(char *key, int value, Data *data);

void create_linked_list(QueueList *queueList, int id, unsigned int age)
{
        Animal *new_animal, *current_animal;
        new_animal = (Animal *) malloc(sizeof(Animal));

        if (new_animal)
        {
            new_animal->prev = NULL;
            new_animal->id = id+1;
            if (queueList->number_of_list_elements == 0)
            {

                new_animal->age = age;
                queueList->first = new_animal;
                queueList->last = new_animal;
                new_animal->next = NULL;
            }
            else
            {
                if (new_animal->id % 40 == 0)
                {
                    (age)++;
                }
                new_animal->age = age;
                current_animal = queueList->last;
                current_animal->next = new_animal;
                new_animal->prev = current_animal;
                queueList->last = new_animal;
            }
            queueList->number_of_list_elements++;
        }
}


void create_list_of_old(QueueList *list, QueueList *list_of_old, int time_of_death)
{
    Animal *animal = list->first;
    while (animal)
    {
        Animal *next = animal->next;
        if (animal->age >= time_of_death)
        {
            if(animal->prev == NULL)
            {
                list->first = animal->next;
                if (animal->next) animal->next->prev = NULL;

            }
            else if (animal->next == NULL)
            {
                list->last = animal->prev;
                if (animal->prev) animal->prev->next = NULL;

            }
            else
            {
                animal->prev->next = animal->next;
                animal->next->prev = animal->prev;
            }
            if(!list_of_old->first)
            {
                list_of_old->first = animal;
                list_of_old->first->prev = NULL;
                list_of_old->last = animal;
                list_of_old->last->next = NULL;
            }
            else
            {
                list_of_old->last->next = animal;
                list_of_old->last->next->prev = list_of_old->last;
                list_of_old->last = animal;
                list_of_old->last->next = NULL;
            }
        }
        animal = next;
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
            if (animal->pregnancy_week >= pregnancy_limit)
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
                young_animal->last_week_wolf_have_eaten = list->last->last_week_wolf_have_eaten;
                young_animal->next = NULL;
                list->last->next = young_animal;
                list->last = young_animal;
            }
            break;
        }
        children++;
    }
}

void print_animal_to_file(char *out_filename, int week, double wolves_density, double rabbits_density)
{
    FILE *outfile = NULL;
    if(week == 0){
        outfile = fopen(out_filename, "w");
        fprintf(outfile,"Week, Wolves density, Rabbits density");
    }else{
        outfile = fopen(out_filename, "a");
        fprintf(outfile, "%d, %f, %f", week, wolves_density, rabbits_density);
    }


    fprintf(outfile, "\n");
    fclose(outfile);
}

void hunting_on_rabbits(QueueList *rabbits, QueueList *wolves,QueueList *dead_rabbits,QueueList *dead_wolves, int week,
        double rabbits_per_kits)
{
    double x = (double)rand()/(double)RAND_MAX;
    Animal *rabbit = rabbits->first;
    Animal *wolf = wolves->first;
    while (wolf)
    {
        Animal *next_wolf = wolf->next;
        double lambda = 1 / (rabbits_per_kits * 0.01);
        double s = -lambda*log(x);
        for (int day = 0; day < 7; day++)
        {
            if((week - wolf->last_week_wolf_have_eaten) >= 4)
            {
                if(wolf->prev == NULL)
                {
                    wolves->first = wolf->next;
                    if (wolf->next) wolf->next->prev = NULL;
                }
                else if (wolf->next == NULL)
                {
                    wolves->last = wolf->prev;
                    if (wolf->prev) wolf->prev->next = NULL;
                }
                else
                {
                    wolf->prev->next = wolf->next;
                    wolf->next->prev = wolf->prev;
                }
                if (!wolf->next && !wolf->prev)
                {
                    wolves->first = NULL;
                    wolves->last = NULL;
                }

                if (!dead_wolves->first)
                {
                    dead_wolves->first = wolf;
                    dead_wolves->first->prev = NULL;
                    dead_wolves->last = wolf;
                    dead_wolves->last->next = NULL;
                    break;
                }
                else
                {
                    dead_wolves->last->next = wolf;
                    dead_wolves->last->next->prev = dead_wolves->last;
                    dead_wolves->last = wolf;
                    dead_wolves->last->next = NULL;
                    break;
                }

            }
            if (rabbit)
            {

                if (s < 1)
                {
                    double chance = (double)rand() / (double)RAND_MAX;
                    if (chance < (0.8 - 0.2 * (week - wolf->last_week_wolf_have_eaten)))
                    {

                        if (rabbit->next)
                        {
                            rabbits->first = rabbit->next;
                            rabbits->first->prev = NULL;
                        } else{
                            rabbits->first = NULL;
                            rabbits->last = NULL;
                        }

                        if (!dead_rabbits->first)
                        {
                            dead_rabbits->first = rabbit;
                            dead_rabbits->first->prev = NULL;
                            dead_rabbits->last = rabbit;

                            wolf->last_week_wolf_have_eaten = week+1;
                            rabbit = rabbit->next;
                            dead_rabbits->last->next = NULL;
                            break;
                        }
                        else
                        {
                            dead_rabbits->last->next = rabbit;
                            dead_rabbits->last->next->prev = dead_rabbits->last;
                            dead_rabbits->last = rabbit;

                            wolf->last_week_wolf_have_eaten = week+1;
                            rabbit = rabbit->next;
                            dead_rabbits->last->next = NULL;
                            break;
                        }



                }
                }else{
                    s--;
                }
            }
        }wolf = next_wolf;

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
    list->first = NULL;
    list->last = NULL;
}


void parse_input_file(char *filename, Data *data) {
    FILE *file;
    file = fopen(filename, "r");
    if(!file){
        return;
    }
    char string[50] = {0};
    while(fgets(string, 50, file) != NULL){
        char key_string[20] = {0};
        char s[1];
        char value_string[10] = {0};
        for (unsigned int i = 0; i < strlen(string); i++){
            if(string[i] >= '0' && string[i] <= '9'){

                s[0] = string[i];
                strncat(value_string, s, 1);
            } else if (string[i] == '\n'){
                get_data_from_datalist(key_string, atoi(value_string),  data);
            } else{
                if (string[i] != ':' && string[i] != ' '){
                    s[0] = string[i];
                    strncat(key_string, s, 1);
                }
            }
        }
    }
    free(file);
}


void simulate_life(QueueList *list, QueueList *death_note, int life_length, int ripening_age, int pregnancy_time,
                   double *similarity, int childrenmin, int simlen, int week, int area, double *rabbits_per_kits, double *wolves_per_kits,
                   QueueList *rabbits_death_note, QueueList *list_of_rabbits)

{

    double animal_per_kits = 0;
    create_list_of_old(list, death_note, life_length);

    Animal *animal = list->first;
    while (animal)
    {
        animal->age++;
        if (animal->age >= ripening_age) animal->is_adult = true;
        animal = animal->next;
        animal_per_kits++;
    }
    animal_per_kits = animal_per_kits/area;
    build_pairs(list);
    pregnancy_run(list, pregnancy_time, similarity, childrenmin, simlen);
    if (list_of_rabbits != NULL)
    {
        *wolves_per_kits = animal_per_kits;
        hunting_on_rabbits(list_of_rabbits, list, rabbits_death_note, death_note, week, *rabbits_per_kits);
        flush_animals_from_memory(rabbits_death_note);
    } else{
        *rabbits_per_kits = animal_per_kits;
    }
    flush_animals_from_memory(death_note);
    printf("Week: %d\n", week+1);
}

void get_data_from_datalist(char *key, int value, Data *data){

        if(strcmp(key, "quantity_of_rabbits") == 0){
            data->quantity_of_rabbits = value;
        } else if (strcmp(key, "quantity_of_wolves") == 0){
            data->quantity_of_wolves = value;
        } else if (strcmp(key, "rabbits_starting_age") == 0){
            data->rabbits_starting_age = value;
        } else if (strcmp(key, "wolves_starting_age") == 0){
            data->wolves_starting_age = value;
        } else if (strcmp(key, "rabbits_life_length") == 0){
            data->rabbits_life_length = value;
        } else if (strcmp(key, "wolves_life_length") == 0){
            data->wolves_life_length = value;
        } else if (strcmp(key, "rabbits_ripening_age") == 0){
            data->rabbits_ripening_age = value;
        } else if (strcmp(key, "wolves_ripening_age") == 0){
            data->wolves_ripening_age = value;
        } else if (strcmp(key, "rabbits_pregnancy_time") == 0){
            data->rabbit_pregnancy_time = value;
        } else if (strcmp(key, "wolves_pregnancy_time") == 0){
            data->wolf_pregnancy_time = value;
        } else if (strcmp(key, "rabbits_childrenmin") == 0){
            data->rabbits_childrenmin = value;
        } else if (strcmp(key, "wolves_childrenmin") == 0){
            data->wolves_childrenmin = value;
        } else if (strcmp(key, "lifetime") == 0){
            data->lifetime = value;
        } else if (strcmp(key, "area") == 0){
            data->area = value;
        }


}