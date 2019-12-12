#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"


Rabbit *found_last_rabbit(Rabbit *ptr);
void generate_young_rabbits(Rabbit *last);


void generate_rabbits(Rabbit **r, int id)
{
    Rabbit *r_list = malloc(sizeof(Rabbit));
    if(!r_list)
    {
        return;
    }
    Rabbit *last = *r;
    r_list->id = id;
    r_list->next = NULL;

    if (!*r)
    {
        r_list->prev = NULL;
        *r = r_list;
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

void print_rabbits(Rabbit *r, double count)
{
    FILE *outfile = NULL;
    char *outfilename = "../output.csv";
    outfile = fopen(outfilename, "a");


    while (r != NULL)
    {
        fprintf(outfile,"%d, %d, %d, %d, %p, %p\n", r->id, r->age, r->is_adult, r->is_paired, r->pair_ptr, r);
        

        r = r->next;
    }
    fprintf(outfile, "Density: %f rabbits/kic^2\n", count/100);
    fclose(outfile);
}

void create_linked_list_of_rabbits(Rabbit *r, unsigned int age)
{
    Rabbit *ptr = r;
    while (ptr != NULL)
    {
        ptr->age = age;
        ptr->is_adult = false;
        ptr->is_paired = false;
        Rabbit *next = ptr->next;
        if (ptr->id % 40 == 0)
        {
            age++;
        }
        
        
        ptr = next;
    }
}

void build_rabbits_in_pairs(Rabbit *r)
{
    Rabbit *ptr = r;
    
    while (ptr != NULL)
    {
        if (ptr->age >= 12)
        {
            ptr->is_adult = true;
        }
        Rabbit *next = ptr->next;
        if (ptr->is_adult && !ptr->is_paired)
        {
            if (ptr->next)
            {
                Rabbit *tmp = ptr->next;
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

void pregnancy_run_for_rabbits(Rabbit *r)
{
    Rabbit *ptr = r;
    while (ptr != NULL)
    {
        Rabbit *next = ptr->next;
        if (ptr->next && ptr->is_adult)
        {
            Rabbit *tmp = ptr->next;
            Rabbit *tmp_next = tmp->next;

                //printf("ptr: %d, tmp: %d\n", ptr->id, tmp->id);
                Rabbit *last = found_last_rabbit(ptr);
                //printf("get last %d going forward\n", last->id);

                if ((ptr->pair_ptr == tmp && tmp->pair_ptr == ptr))
                {
                    
                    ptr->pregnancy_week++;
                    tmp->pregnancy_week++;
                  //  printf("updated pregnancy %d\n", ptr->pregnancy_week);
                    if (ptr->pregnancy_week >= 12)
                    {
                        generate_young_rabbits(last);
                        ptr->pregnancy_week = 0;
                        tmp->pregnancy_week = 0;
                    //    printf("-----------------------made young_rabbits----------------------------------------------\n");
                    }  
                }

            tmp = tmp_next;
        }
        ptr = next;
    }
    
}

Rabbit *found_last_rabbit(Rabbit *ptr)
{
    Rabbit *r = ptr;
    Rabbit *last = NULL;
    while (r != NULL)
    {
        Rabbit *next = r->next;
        last = r;
        r = next;
    }
   // printf("returning last\n");
    return last;
}

void generate_young_rabbits(Rabbit *last)
{
    Rabbit *young_rabbits_last = last;
    int children = 5;
    
    float similarity[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    int simlen = sizeof(similarity)/sizeof(similarity[0]);
    double random = (double)rand() / (double)RAND_MAX;
    //printf("///////////////////random %f\n", random);
    for (int i = 0; i < simlen; i++)
    {
        if (random < similarity[i])
        {
            Rabbit *young_rabbits = NULL;


            for (int j = 0; j < children; j++)
            {
                young_rabbits = malloc(sizeof(Rabbit));
                if(!young_rabbits)
                {
                    return;
                }
                young_rabbits->prev = young_rabbits_last;
                young_rabbits->id = young_rabbits_last->id + 1;
                young_rabbits->age = 0;
                young_rabbits->pair_ptr = NULL;
                young_rabbits->is_adult = false;
                young_rabbits->is_paired = false;
                young_rabbits_last->next = young_rabbits;
                young_rabbits->next = NULL;
                young_rabbits_last = young_rabbits;
      //          printf("==================young_rabbits created=============\n");
            }break;

        }
        children++;
    }

}

void kill_rabbits_after_five_years(Rabbit *r)
{
    Rabbit *ptr = r;
    while (ptr != NULL)
    {
        Rabbit *next = ptr->next;
        if (ptr->age >= 240)
        {
            if(ptr->prev)
                ptr->prev->next = ptr->next;
            if(ptr->next != NULL)
                ptr->next->prev = ptr->prev;
            free(ptr);
        }
        ptr = next;
    }
    
}

void flush_rabbits_from_memory(Rabbit *r)
{
    Rabbit *ptr = r;
    while(ptr != NULL)
    {
        Rabbit *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}