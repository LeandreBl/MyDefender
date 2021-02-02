#pragma once

#include "LSCENE/lgameobject.h"

typedef struct tower_s {
    lgameobject_t base_object;
} tower_t;

lgameobject_t *tower_create(sfVector2f position, const sfTexture *texture);