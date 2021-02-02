#pragma once

#include <stddef.h>

typedef struct mob_wave_s {
    char *name;
    size_t count;
} mob_wave_t;

int mob_wave_create(mob_wave_t *mw, const char *name, size_t count);
void mob_wave_destroy(mob_wave_t *mw);