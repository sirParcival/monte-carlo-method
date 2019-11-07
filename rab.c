#include <stdio.h>
#include <stdlib.h>

#include "structure.h"

void add_rabbits(rabbit **r, int id);
void print_rabbits(rabbit *r);
void free_rabbits(rabbit *r);
void delete_rabbits(rabbit *r);
void count_rabbits(rabbit *r, unsigned int age);

int main(void)
{
    rabbit *rabbits = NULL;
    for(int i = 1; i <= 9600; i++)
    {
        add_rabbits(&rabbits, i);
    }
    count_rabbits(rabbits, 1);
    delete_rabbits(rabbits);
    print_rabbits(rabbits);
    free_rabbits(rabbits);
    return 0;
}

void add_rabbits(rabbit **r, int id)
{
    rabbit *r_list = malloc(sizeof(rabbit));
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
    rabbit *first;
    while (r != NULL)
    {
        printf("%d, %d\n", r->id, r->age);
        first = r;
        r = r->next;
    }


}

void count_rabbits(rabbit *r, unsigned int age)
{
    rabbit *ptr = r;
    while (ptr != NULL)
    {
        ptr->age = age;
        rabbit *next = ptr->next;
        if (ptr->id % 40 == 0)
        {
            age++;
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
