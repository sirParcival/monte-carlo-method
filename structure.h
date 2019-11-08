#include <stdbool.h>

typedef struct rabbit
{
    struct rabbit *prev;
    unsigned int id;
    unsigned int age;
    int pair_id;
    bool adult;
    bool paired;

    struct rabbit *next;
}rabbit;
