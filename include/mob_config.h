#pragma once

#include "config_file.h"

typedef struct mob_config_s {
    char *name;
    float health;
    float speed;
} mob_config_t;

/*
**  mobname: string
**  health: float
**  speed: float
*/

int mob_config_create_from_file(mob_config_t *mob, config_file_t *file);
void mob_config_destroy(mob_config_t *mob);
