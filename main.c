//
// Created by cydev on 05.12.2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "librab.h"
#include "libwolf.h"


int main(void)
{
    unsigned int quantity_of_rabbits = 2;
    unsigned int starting_age_rabbits = 100;
    unsigned int starting_age_wolves = 50;
    unsigned int lifetime_in_weeks = 140;
    unsigned int quantity_of_wolves = 2;

    Rabbit *rabbits = NULL;
    double rabbits_per_kic;
    Wolf *wolves = NULL;
    double wolves_per_kic;

    for(int i = 1; i <= quantity_of_rabbits; i++)
        generate_rabbits(&rabbits, i);

    create_linked_list_of_rabbits(rabbits, starting_age_rabbits);

    for(int i = 1; i <= quantity_of_wolves; i++)
        generate_wolves(&wolves, i);

    create_linked_list_of_wolves(wolves, starting_age_wolves);

    for (int weeks = 0; weeks < lifetime_in_weeks; weeks++)
    {
        rabbits_per_kic = 0;
        kill_rabbits_after_five_years(rabbits);
        build_rabbits_in_pairs(rabbits);
        pregnancy_run_for_rabbits(rabbits);
        Rabbit *rptr = rabbits;
        while (rptr != NULL)
        {
            Rabbit *next = rptr->next;
            rptr->age++;
            rptr = next;
            rabbits_per_kic++;
        }
        kill_rabbits_after_five_years(rabbits);



    //Wolves


        wolves_per_kic = 0;
        kill_wolves_after_ten_years(wolves);
        if (hunting_on_rabbits(weeks, rabbits, rabbits_per_kic/100, wolves) == -1)
        {
            printf("There are no rabbits more\n");
            return 0;
        }
        build_wolves_in_pairs(wolves);
        pregnancy_run_for_wolves(wolves);
        Wolf *wptr = wolves;
        while (wptr != NULL)
        {
            Wolf *next = wptr->next;
            wptr->age++;
            wptr = next;
            wolves_per_kic++;
        }
        kill_wolves_after_ten_years(wolves);

    }


    if(wolves)
    {
        print_wolves(wolves, wolves_per_kic);
        flush_wolves_from_memory(wolves);
    }


    if(rabbits)
    {
        print_rabbits(rabbits, rabbits_per_kic);
        flush_rabbits_from_memory(rabbits);
    }


    return 0;
}