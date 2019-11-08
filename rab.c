#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"

void add_rabbits(rabbit **r, int id);
void print_rabbits(rabbit *r);
void free_rabbits(rabbit *r);
void delete_rabbits(rabbit *r);
void count_rabbits(rabbit *r, unsigned int age);
void build_pairs(rabbit *r);

int main(void)
{
    rabbit *rabbits = NULL;

    for(int i = 1; i <= 9600; i++)
    {
        add_rabbits(&rabbits, i);
    }
    count_rabbits(rabbits, 1);
    delete_rabbits(rabbits);
    build_pairs(rabbits);
    print_rabbits(rabbits);
    free_rabbits(rabbits);
    return 0;
}

void add_rabbits(rabbit **r, int id)
{
    rabbit *r_list = malloc(sizeof(rabbit));
    if(!r_list)
    {
        return -1;
    }
    rabbit *last = *r;
    r_list->id = id;
    r_list->next = NULL;

    if (!*r)
    {
        r_list->prev = NULL;
        *r = r_list;
        return;
    }
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = r_list;
    r_list->prev = last;
}

void print_rabbits(rabbit *r)
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
        if (ptr->age >= 12)
        {
            ptr->adult = true;
        }
        
        ptr = next;
    }
}

void build_pairs(rabbit *r)
{
    rabbit *ptr = r;
    while (ptr != NULL)
    {
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