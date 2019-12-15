#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "libfunction.h"

int main() {

    QueueList *list_of_rabbits;
    QueueList *list_of_wolves;
    list_of_wolves = (QueueList*)malloc(sizeof(QueueList));
    list_of_rabbits = (QueueList*)malloc(sizeof(QueueList));
    int quantity_of_rabbits = 2;
    int quantity_of_wolves = 2;
    unsigned int rabbits_starting_age = 1;
    unsigned int wolves_starting_age = 1;
    int rabbits_life_length = 240;
    int wolves_life_length = 580;
    int lifetime = 40;
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

    for (int i = 0; i < quantity_of_rabbits; i++)
    {
        create_linked_list(list_of_rabbits, i, &rabbits_starting_age);
    }
    for (int i = 0; i < quantity_of_wolves; i++)
    {
        create_linked_list(list_of_wolves, i, &wolves_starting_age);
    }


    ///Life simulation///

    for (int i = 0; i < lifetime; i++)
    {

        kill_animal_after_some_time(list_of_rabbits, rabbits_life_length);
        Animal *rabbit = list_of_rabbits->first;
        while (rabbit)
        {
            rabbit->age++;
            if (rabbit->age >= rabbits_ripening_age) rabbit->is_adult = true;
            rabbit = rabbit->next;

        }
        build_pairs(list_of_rabbits);
        pregnancy_run(list_of_rabbits, rabbit_pregnancy_time, rabbits_similarity, rabbits_childrenmin, rabbits_simlen);


        kill_animal_after_some_time(list_of_wolves, wolves_life_length);
        Animal *wolf = list_of_wolves->first;
        while (wolf)
        {
            wolf->age++;
            if (wolf->age >= wolves_ripening_age) wolf->is_adult = true;
            wolf = wolf->next;
        }
        build_pairs(list_of_wolves);
        pregnancy_run(list_of_wolves, wolf_pregnancy_time, wolf_similarity, wolves_childrenmin, wolves_simlen);
        printf("Week: %d\n", i+1);

    }

    print_animal_to_file(list_of_rabbits, "w");
    print_animal_to_file(list_of_wolves, "a");
    free(list_of_rabbits);
    free(list_of_wolves);

    return 0;
}

