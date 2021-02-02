#pragma once

#include "LSCENE/lgameobject.h"

typedef struct mob_s {
    lgameobject_t base_object;
    float max_health;
    float health;
    float speed;
} mob_t;

lgameobject_t *mob_create(const char *name, size_t max_health, float speed);