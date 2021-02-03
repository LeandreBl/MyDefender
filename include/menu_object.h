#pragma once

#include "LSCENE/lgameobject.h"

typedef struct menu_object_s {
    lgameobject_t base_object;
} menu_object_t;

typedef struct menu_button_s {
    const char *name;
} menu_button_t;

lgameobject_t *menu_object_create(void);