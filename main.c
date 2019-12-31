#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "libfunction.h"

void simulate_life(QueueList *list, QueueList *death_note, int life_length, int ripening_age, int pregnancy_time,
                   double *similarity, int childrenmin, int simlen, int week, int area, double *rabbits_per_kits,
                   QueueList *rabbits_death_note, QueueList *list_of_rabbits);

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
    double rabbits_per_kits = 0;

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
        simulate_life(list_of_rabbits, rabbits_death_note, rabbits_life_length, rabbits_ripening_age,
                rabbit_pregnancy_time, rabbits_similarity, rabbits_childrenmin, rabbits_simlen, week, area,
                &rabbits_per_kits, NULL, NULL);

        simulate_life(list_of_wolves, wolves_death_note, wolves_life_length, wolves_ripening_age, wolf_pregnancy_time,
                wolf_similarity, wolves_childrenmin, wolves_simlen, week, area, &rabbits_per_kits, rabbits_death_note, list_of_rabbits);
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




void simulate_life(QueueList *list, QueueList *death_note, int life_length, int ripening_age, int pregnancy_time,
                   double *similarity, int childrenmin, int simlen, int week, int area, double *rabbits_per_kits,
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
        hunting_on_rabbits(list_of_rabbits, list, rabbits_death_note, death_note, week, *rabbits_per_kits);
        flush_animals_from_memory(rabbits_death_note);
    } else{
        *rabbits_per_kits = animal_per_kits;
    }
    flush_animals_from_memory(death_note);
    printf("Week: %d\n", week+1);
}
