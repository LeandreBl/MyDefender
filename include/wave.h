#pragma once

#include "lvector.h"
#include "mob.h"
#include "config_file.h"

typedef struct mob_config_s {
    char *name;
    float health;
    float speed;
} mob_config_t;

typedef struct mob_wave_s {
    char *name;
    size_t count;
} mob_wave_t;

typedef struct wave_config_s {
    char *name;
    lvector(mob_wave_t) mobs_settings;
    size_t difficulty;
} wave_config_t;

typedef lvector(wave_config_t) waves_t;

/*
**  wavename: string
**  - string (mob name): uint (count)
**  ...
*/

/*
**  mobname: string
**  health: float
**  speed: float
*/

int wave_config_create_from_file(wave_config_t *wave, config_file_t *file);
int mob_config_create_from_file(mob_config_t *mob, config_file_t *file);
void wave_config_destroy(wave_config_t *wave);
void mob_wave_destroy(mob_wave_t *mw);