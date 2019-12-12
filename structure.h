#include <stdbool.h>

typedef struct Rabbit
{
    struct Rabbit *pair_ptr;
    struct Rabbit *prev;
    struct Rabbit *next;
    
    unsigned int id;
    unsigned int age;
    unsigned int pregnancy_week;

    bool is_adult;
    bool is_paired;


}Rabbit;

typedef struct Wolf
{
    struct Wolf *pair_ptr;
    struct Wolf *prev;
    struct Wolf *next;

    double last_week_wolf_have_eaten;

    unsigned int id;
    unsigned int age;
    unsigned int pregnancy_week;


    bool is_adult;
    bool is_paired;


}Wolf;


