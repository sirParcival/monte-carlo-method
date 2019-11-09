#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"

void add_rabbits(rabbit **r, int id);
void print_rabbits(rabbit *r, double count);
void free_rabbits(rabbit *r);
void delete_rabbits(rabbit *r);
void count_rabbits(rabbit *r, unsigned int age);
void build_pairs(rabbit *r);
void generate_young_rabbits(rabbit *r);
rabbit *found_last(rabbit *ptr);
void make_young(rabbit *last);

int main(void)
{
    rabbit *rabbits = NULL;
    double number_of_rabbits;
    for(int i = 1; i <= 9600; i++)
    {
        add_rabbits(&rabbits, i);
    }
    count_rabbits(rabbits, 1);
    
    for (int i = 0; i < 20; i++)
    {
        number_of_rabbits = 0;
        delete_rabbits(rabbits);
        build_pairs(rabbits);
        generate_young_rabbits(rabbits);
        rabbit *ptr = rabbits;
        while (ptr != NULL)
        {
            rabbit *next = ptr->next;
            ptr->age++;
            ptr = next;
            number_of_rabbits++;
        }
        delete_rabbits(rabbits);
    }
    print_rabbits(rabbits, number_of_rabbits);
    free_rabbits(rabbits);
    return 0;
}

void add_rabbits(rabbit **r, int id)
{
    rabbit *r_list = malloc(sizeof(rabbit));
    if(!r_list)
    {
        return;
    }
    rabbit *last = *r;
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

void print_rabbits(rabbit *r, double count)
{
    FILE *outfile = NULL;
    char *outfilename = "output.csv";
    outfile = fopen(outfilename, "w");

    rabbit *first;
    while (r != NULL)
    {
        fprintf(outfile,"%d, %d, %d, %d, %d\n", r->id, r->age, r->adult, r->paired, r->pair_id);
        
        first = r;
        r = r->next;
    }
    fprintf(outfile, "Density: %f rabbits/kic^2\n", count/100);
    fclose(outfile);
}

void count_rabbits(rabbit *r, unsigned int age)
{
    rabbit *ptr = r;
    while (ptr != NULL)
    {
        ptr->age = age;
        ptr->adult = false;
        ptr->paired = false;
        rabbit *next = ptr->next;
        if (ptr->id % 40 == 0)
        {
            age++;
        }
        
        
        ptr = next;
    }
}

void build_pairs(rabbit *r)
{
    rabbit *ptr = r;
    
    while (ptr != NULL)
    {
        if (ptr->age >= 12)
        {
            ptr->adult = true;
        }
        rabbit *next = ptr->next;
        if (ptr->adult && !ptr->paired)
        {
            if (ptr->next)
            {
                rabbit *tmp = ptr->next;
                rabbit *tmp_next = ptr->next->next;
                while (tmp != NULL && tmp->next != NULL)
                {
                    if (tmp->adult && !tmp->paired)
                    {
                        ptr->paired = true;
                        tmp->paired = true;
                        tmp->pair_id = ptr->id;
                        ptr->pair_id = tmp->id;
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

void generate_young_rabbits(rabbit *r)
{
    rabbit *ptr = r;
    while (ptr != NULL)
    {
        rabbit *next = ptr->next;
        if (ptr->next && ptr->adult)
        {
            rabbit *tmp = ptr->next;
            rabbit *tmp_next = tmp->next;
            while (tmp != NULL && tmp->next != NULL)
            {   
                
                printf("ptr: %d, tmp: %d\n", ptr->id, tmp->id);
                rabbit *last = found_last(ptr);
                printf("get last %d going forward\n", last->id);

                if ((ptr->pair_id == tmp->id && tmp->pair_id == ptr->id))
                {
                    
                    ptr->pregnancy_week++;
                    tmp->pregnancy_week++;
                    printf("updated pregnancy %d\n", ptr->pregnancy_week);
                    if (ptr->pregnancy_week == 12)
                    {
                        make_young(last);
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

rabbit *found_last(rabbit *ptr)
{
    rabbit *r = ptr;
    rabbit *last = NULL;
    while (r != NULL)
    {
        rabbit *next = r->next;
        last = r;
        r = next;
    }
    printf("returning last\n");
    return last;
}

void make_young(rabbit *last)
{
    rabbit *young_last = last;
    rabbit *first = NULL;
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
                rabbit *young = malloc(sizeof(rabbit));
                if(!young)
                {
                    return;
                }
                young->prev = young_last;
                young->id = young_last->id + 1;
                young->age = 0;
                young->pair_id = 0;
                young->adult = false;
                young->paired = false;
                young_last->next = young;
                young->next = NULL;
                young_last = young;
                printf("==================young created=============\n");
            }break;
            
        }
        children++;
    }

}

void delete_rabbits(rabbit *r)
{
    rabbit *ptr = r;
    while (ptr != NULL)
    {
        rabbit *next = ptr->next;
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

void free_rabbits(rabbit *r)
{
    rabbit *ptr = r;
    while(ptr != NULL)
    {
        rabbit *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}