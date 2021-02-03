#pragma once

#include "LSCENE/lgameobject.h"

typedef struct mob_s {
    lgameobject_t base_object;
    char *texture;
    float last_animation_time;
    float delay_between_animation;
    float max_health;
    float health;
    float speed;
} mob_t;

lgameobject_t *mob_create(const char *name, size_t max_health, float speed, const char *texture);
