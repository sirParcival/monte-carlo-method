#include <stdio.h>
#include <stdlib.h>
#define ARRAY_SIZE(arr)  (sizeof(arr) / sizeof((arr)[0]))
#include "structure.h"
#include "libfunction.h"



int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("Usage: ./monte_carlo_method existing_input_filename output_filename\n");
        return 1;
    }
    char *input_filename = argv[1];
    char *output_filename = argv[2];


    // initialising double-linked lists for wolves and rabbits
    QueueList *list_of_rabbits;
    QueueList *list_of_wolves;
    QueueList *rabbits_death_note; //list for dead rabbits
    QueueList *wolves_death_note; //list for dead wolves

    // allocating memory for lists
    list_of_wolves = (QueueList*)malloc(sizeof(QueueList));
    list_of_rabbits = (QueueList*)malloc(sizeof(QueueList));
    rabbits_death_note = (QueueList*)malloc(sizeof(QueueList));
    wolves_death_note = (QueueList*)malloc(sizeof(QueueList));

    double rabbits_similarity[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double wolf_similarity[] = {0.2, 0.4, 0.6, 0.8, 1.0};

    // animals density for output file
    double rabbits_per_kits = 0;
    double wolves_per_kits = 0;
    Data data = {0};

    // getting data from input file
    parse_input_file(input_filename, &data);


    ///Linking rabbits and wolves to double-linked list///
    for (int i = 0; i < data.quantity_of_rabbits; i++){
        create_linked_list(list_of_rabbits, 'r', data.rabbits_starting_age);
    }
    for (int i = 0; i < data.quantity_of_wolves; i++){
        create_linked_list(list_of_wolves, 'w', data.wolves_starting_age);
    }

    ///Life simulation///

    for (int week = 0; week < data.lifetime; week++)
    {
        //This one is for rabbits
        simulate_life(list_of_rabbits, rabbits_death_note, data.rabbits_life_length, data.rabbits_ripening_age,
                      data.rabbit_pregnancy_time, rabbits_similarity, data.rabbits_children_min, ARRAY_SIZE(rabbits_similarity),
                      week, data.area,
                      &rabbits_per_kits, NULL, NULL, NULL);

        //This one is for wolves
        simulate_life(list_of_wolves, wolves_death_note, data.wolves_life_length, data.wolves_ripening_age,
                      data.wolf_pregnancy_time, wolf_similarity, data.wolves_children_min, ARRAY_SIZE(wolf_similarity), week,
                      data.area, &rabbits_per_kits, &wolves_per_kits, rabbits_death_note, list_of_rabbits);
        //Printing result of experiment to file
        print_animal_to_file(output_filename, week, wolves_per_kits, rabbits_per_kits);
    }

    flush_animals_from_memory(list_of_rabbits);
    flush_animals_from_memory(list_of_wolves);
    free(list_of_rabbits);
    free(list_of_wolves);
    free(rabbits_death_note);
    free(wolves_death_note);
    return 0;
}





