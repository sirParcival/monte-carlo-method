#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "libfunction.h"

int main() {

    QueueList *list_of_rabbits;
    QueueList *list_of_wolves;
    QueueList *rabbits_death_note;
    QueueList *wolves_death_note;
    list_of_wolves = (QueueList*)malloc(sizeof(QueueList));
    list_of_rabbits = (QueueList*)malloc(sizeof(QueueList));
    rabbits_death_note = (QueueList*)malloc(sizeof(QueueList));
    wolves_death_note = (QueueList*)malloc(sizeof(QueueList));
    int quantity_of_rabbits = 900;
    int quantity_of_wolves = 26;
    unsigned int rabbits_starting_age = 1;
    unsigned int wolves_starting_age = 1;
    int rabbits_life_length = 240;
    int wolves_life_length = 580;
    int lifetime = 100;
    int rabbits_ripening_age = 12;
    int wolves_ripening_age = 36;
    int rabbit_pregnancy_time = 12;
    int wolf_pregnancy_time = 24;
    double rabbits_similarity[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double wolf_similarity[] = {0.2, 0.4, 0.6, 0.8, 1.0};
    int rabbits_childrenmin = 5;
    int wolves_childrenmin = 4;
    int rabbits_simlen = sizeof(rabbits_similarity)/sizeof(rabbits_similarity[0]);
    int wolves_simlen = sizeof(wolf_similarity)/sizeof(wolf_similarity[0]);
    int area = 100;

    for (int i = 0; i < quantity_of_rabbits; i++)
    {
        create_linked_list(list_of_rabbits, i, &rabbits_starting_age);
    }
    for (int i = 0; i < quantity_of_wolves; i++)
    {
        create_linked_list(list_of_wolves, i, &wolves_starting_age);
    }


    ///Life simulation///

    for (int week = 0; week < lifetime; week++)
    {
        double rabbits_per_kits = 0;

        create_list_of_old(list_of_rabbits, rabbits_death_note, rabbits_life_length);
        flush_animals_from_memory(rabbits_death_note);
        Animal *rabbit = list_of_rabbits->first;
        while (rabbit)
        {
            rabbit->age++;
            if (rabbit->age >= rabbits_ripening_age) rabbit->is_adult = true;
            rabbit = rabbit->next;
            rabbits_per_kits++;
        }
        rabbits_per_kits = rabbits_per_kits/area;
        printf("%f\n", rabbits_per_kits);
        build_pairs(list_of_rabbits);
        pregnancy_run(list_of_rabbits, rabbit_pregnancy_time, rabbits_similarity, rabbits_childrenmin, rabbits_simlen);


        create_list_of_old(list_of_wolves, wolves_death_note, wolves_life_length);
        flush_animals_from_memory(wolves_death_note);
        Animal *wolf = list_of_wolves->first;
        while (wolf)
        {
            wolf->age++;
            if (wolf->age >= wolves_ripening_age) wolf->is_adult = true;
            wolf = wolf->next;
        }
        build_pairs(list_of_wolves);
        pregnancy_run(list_of_wolves, wolf_pregnancy_time, wolf_similarity, wolves_childrenmin, wolves_simlen);
        hunting_on_rabbits(list_of_rabbits, list_of_wolves, rabbits_death_note, wolves_death_note, week, rabbits_per_kits);
        printf("Week: %d\n", week+1);

    }

    print_animal_to_file(list_of_rabbits, "w");
    print_animal_to_file(list_of_wolves, "a");
    flush_animals_from_memory(list_of_rabbits);
    flush_animals_from_memory(list_of_wolves);
    free(list_of_rabbits);
    free(list_of_wolves);
    free(rabbits_death_note);
    free(wolves_death_note);

    return 0;
}

