//
// Created by cydev on 04.12.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "librab.h"
#include "structure.h"

void eat_rabbit(Rabbit *r);
Wolf *found_last_wolf(Wolf *ptr);
void generate_young_wolves_wolves(Wolf *last, double random);





void generate_wolves(Wolf **pWolves, int id)
{
    Wolf *r_list = malloc(sizeof(Wolf));
    if(!r_list)
    {
        return;
    }
    Wolf *last = *pWolves;
    r_list->id = id;
    r_list->next = NULL;

    if (!*pWolves)
    {
        r_list->prev = NULL;
        *pWolves = r_list;
    }
    else
    {
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = r_list;
        r_list->prev = last;
    }
}

void create_linked_list_of_wolves(Wolf *w, unsigned int age)
{
    Wolf *ptr = w;
    while (ptr != NULL)
    {
        ptr->age = age;
        ptr->is_adult = false;
        ptr->is_paired = false;
        ptr->last_week_wolf_have_eaten = 0;
        Wolf *next = ptr->next;
        if (ptr->id % 40 == 0)
        {
            age++;
        }


        ptr = next;
    }
}

void kill_wolves_after_ten_years(Wolf *w)
{
    Wolf *ptr = w;
    while (ptr != NULL)
    {
        Wolf *next = ptr->next;
        if (ptr->age >= 480)
        {
            if(ptr->prev)
                ptr->prev->next = ptr->next;
            if(ptr->next)
                ptr->next->prev = ptr->prev;
            free(ptr);
        }
        ptr = next;
    }

}

void build_wolves_in_pairs(Wolf *w)
{
    Wolf *ptr = w;

    while (ptr != NULL)
    {
        if (ptr->age >= 36)
        {
            ptr->is_adult = true;
        }
        Wolf *next = ptr->next;
        if (ptr->is_adult && !ptr->is_paired)
        {
            if (ptr->next)
            {
                Wolf *tmp = ptr->next;
                while (tmp != NULL)
                {
                    if (tmp->is_adult && !tmp->is_paired)
                    {
                        ptr->is_paired = true;
                        tmp->is_paired = true;
                        tmp->pair_ptr = ptr;
                        ptr->pair_ptr = tmp;
                        break;
                    }
                    tmp = tmp->next;

                }
            }
        }
        ptr = next;
    }

}

int hunting_on_rabbits(int week, Rabbit *r, double rabbits_per_kic, Wolf *w)
{
    double x = (double)rand() / (double)RAND_MAX;
    printf("%d\n", week);
    while (w != NULL)
    {
        double lambda = 1 / (rabbits_per_kic * 0.01);
        double s = -lambda*log(x);
        //double probability_density_of_encountering_rabbits = (1/lambda) * exp(-s/lambda);
        Wolf *next = w->next;
        for (int day = 0; day < 7; day++)
        {
            if(r) {
                /* if(week - w->last_week_wolf_have_eaten == 4)
                 {
                     w = NULL;
                     free(w);
                     break;
                 }
                 if(s > 1)
                 {
                     s--;
                     continue;
                 }
                 else
                 {
                     double chance = (double)rand() / (double)RAND_MAX;
                     if (chance < (0.8-0.2*(week - w->last_week_wolf_have_eaten)))
                     {
                         if(r->prev)
                             r->prev->next = r->next;
                         if(r->next)
                             r->next->prev = r->prev;
                         free(r);

                         break;



                 }
             }*/
            }
        }
        w = next;
    }
    return 0;
}


void pregnancy_run_for_wolves(Wolf *w)
{
    double random = (double)rand() / (double)RAND_MAX;
    Wolf *ptr = w;
    while (ptr != NULL)
    {
        Wolf *next = ptr->next;
        if (ptr->next && ptr->is_adult)
        {
            Wolf *tmp = ptr->next;
            Wolf *tmp_next = tmp->next;
                //printf("ptr: %d, tmp: %d\n", ptr->id, tmp->id);
                Wolf *last = found_last_wolf(ptr);
                //printf("get last %d going forward\n", last->id);

                if ((ptr->pair_ptr == tmp && tmp->pair_ptr == ptr))
                {

                    ptr->pregnancy_week++;
                    tmp->pregnancy_week++;
                    //printf("updated pregnancy %d\n", ptr->pregnancy_week);
                    if (ptr->pregnancy_week >= 24)
                    {
                        generate_young_wolves_wolves(last, random);
                        ptr->pregnancy_week = 0;
                        tmp->pregnancy_week = 0;
                      //  printf("-----------------------made young_wolves----------------------------------------------\n");
                    }
                }

                tmp = tmp_next;

        }
        ptr = next;
    }

}

Wolf *found_last_wolf(Wolf *ptr)
{
    Wolf *r = ptr;
    Wolf *last = NULL;
    while (r != NULL)
    {
        Wolf *next = r->next;
        last = r;
        r = next;
    }
   // printf("returning last\n");
    return last;
}

void generate_young_wolves_wolves(Wolf *last, double random)
{
    Wolf *young_wolves_last = last;
    int children = 4;

    float similarity[] = {0.2, 0.4, 0.6, 0.8, 1.0};
    int simlen = sizeof(similarity)/sizeof(similarity[0]);

    //printf("///////////////////random %f\n", random);
    for (int i = 0; i < simlen; i++)
    {
        if (random < similarity[i])
        {
            Wolf *young_wolves = NULL;
            for (int j = 0; j < children; j++)
            {
                young_wolves = malloc(sizeof(Wolf));
                if(!young_wolves)
                {
                    return;
                }
                young_wolves->prev = young_wolves_last;
                young_wolves->id = young_wolves_last->id + 1;
                young_wolves->pregnancy_week = 0;
                young_wolves->age = 0;
                young_wolves->pair_ptr = NULL;
                young_wolves->is_adult = false;
                young_wolves->is_paired = false;
                young_wolves_last->next = young_wolves;
                young_wolves->next = NULL;
                young_wolves_last = young_wolves;
     //           printf("==================young_wolves created=============\n");
            }break;

        }
        children++;
    }

}

void print_wolves(Wolf *w, double count)
{
    FILE *outfile = NULL;
    char *outfilename = "../output.csv";
    outfile = fopen(outfilename, "w");


    while (w != NULL && w->id != 0)
    {
        fprintf(outfile,"%d, %d, %d, %d, %p, %p\n", w->id, w->age, w->is_adult, w->is_paired, w->pair_ptr, w);

        w = w->next;
    }
    fprintf(outfile, "Density: %f wolves/kic^2\n", count/100);
    fclose(outfile);
}

void flush_wolves_from_memory(Wolf *w)
{
    Wolf *ptr = w;
    while(ptr != NULL)
    {
        Wolf *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}