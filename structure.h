#include <stdbool.h>

typedef struct Rabbit
{

    
    unsigned int id;
    unsigned int age;
    unsigned int pregnancy_week;

    bool is_adult;
    bool is_paired;

    struct Rabbit *pair_ptr;
    struct Rabbit *prev;
    struct Rabbit *next;
}Rabbit;
