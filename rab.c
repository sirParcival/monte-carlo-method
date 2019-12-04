#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"

void generate_rabbits(Rabbit **r, int id);
void print_rabbits(Rabbit *r, double count);
void flush_rabbits_from_memory(Rabbit *r);
void kill_rabbits_after_five_years(Rabbit *r);
void create_linked_list_of_rabbits(Rabbit *r, unsigned int age);
void build_pairs(Rabbit *r);
void pregnancy_run(Rabbit *r);
Rabbit *found_last(Rabbit *ptr);
void generate_young_rabbits(Rabbit *last);

int main(void)
{
    Rabbit *rabbits = NULL;
    double rabbits_per_kic;
    unsigned int quantity_of_rabbits = 9600;
    unsigned int starting_age = 1;
    unsigned int lifetime_in_weeks = 50;
    for(int i = 1; i <= quantity_of_rabbits; i++)
    {
        generate_rabbits(&rabbits, i);
    }
    create_linked_list_of_rabbits(rabbits, starting_age);
    
    for (int i = 0; i < lifetime_in_weeks; i++)
    {
        rabbits_per_kic = 0;
        kill_rabbits_after_five_years(rabbits);
        build_pairs(rabbits);
        pregnancy_run(rabbits);
        Rabbit *ptr = rabbits;
        while (ptr != NULL)
        {
            Rabbit *next = ptr->next;
            ptr->age++;
            ptr = next;
            rabbits_per_kic++;
        }
        kill_rabbits_after_five_years(rabbits);
    }
    print_rabbits(rabbits, rabbits_per_kic);
    flush_rabbits_from_memory(rabbits);
    return 0;
}

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
    char *outfilename = "output.csv";
    outfile = fopen(outfilename, "w");

    Rabbit *first;
    while (r != NULL)
    {
        fprintf(outfile,"%d, %d, %d, %d, %p\n", r->id, r->age, r->is_adult, r->is_paired, r->pair_ptr);
        
        first = r;
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

void build_pairs(Rabbit *r)
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
                Rabbit *tmp_next = ptr->next->next;
                while (tmp != NULL && tmp->next != NULL)
                {
                    if (tmp->is_adult && !tmp->is_paired)
                    {
                        ptr->is_paired = true;
                        tmp->is_paired = true;
                        tmp->pair_ptr = ptr;
                        ptr->pair_ptr = tmp;
                        break;
                    }
                tmp = tmp_next;
                tmp_next = tmp_next->next;
                
                }
            }     
        }
        ptr = next;
    }
    
}

void pregnancy_run(Rabbit *r)
{
    Rabbit *ptr = r;
    while (ptr != NULL)
    {
        Rabbit *next = ptr->next;
        if (ptr->next && ptr->is_adult)
        {
            Rabbit *tmp = ptr->next;
            Rabbit *tmp_next = tmp->next;
            while (tmp != NULL && tmp->next != NULL)
            {
                
                printf("ptr: %d, tmp: %d\n", ptr->id, tmp->id);
                Rabbit *last = found_last(ptr);
                printf("get last %d going forward\n", last->id);

                if ((ptr->pair_ptr == tmp && tmp->pair_ptr == ptr))
                {
                    
                    ptr->pregnancy_week++;
                    tmp->pregnancy_week++;
                    printf("updated pregnancy %d\n", ptr->pregnancy_week);
                    if (ptr->pregnancy_week == 12)
                    {
                        generate_young_rabbits(last);
                        ptr->pregnancy_week = 0;
                        tmp->pregnancy_week = 0;
                        printf("-----------------------made young----------------------------------------------\n");
                    }  
                }break;
                
            }
            
        }
        ptr = next;
    }
    
}

Rabbit *found_last(Rabbit *ptr)
{
    Rabbit *r = ptr;
    Rabbit *last = NULL;
    while (r != NULL)
    {
        Rabbit *next = r->next;
        last = r;
        r = next;
    }
    printf("returning last\n");
    return last;
}

void generate_young_rabbits(Rabbit *last)
{
    Rabbit *young_last = last;
    Rabbit *first = NULL;
    int children = 5;
    
    float similarity[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    int simlen = sizeof(similarity)/sizeof(similarity[0]);
    double random = (double)rand() / (double)RAND_MAX;
    printf("///////////////////random %f\n", random);
    for (int i = 0; i < simlen; i++)
    {
        if (random < similarity[i])
        {
            for (int j = 0; j < children; j++)
            {
                Rabbit *young = malloc(sizeof(Rabbit));
                if(!young)
                {
                    return;
                }
                young->prev = young_last;
                young->id = young_last->id + 1;
                young->age = 0;
                young->pair_ptr = NULL;
                young->is_adult = false;
                young->is_paired = false;
                young_last->next = young;
                young->next = NULL;
                young_last = young;
                printf("==================young created=============\n");
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
        if (ptr->age == 240)
        {
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