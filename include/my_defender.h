#pragma once

#include "settings.h"
#include "LSCENE/lscene.h"

typedef struct my_defender_ctx_s {
    settings_t settings;
    lscene_t scene;
} defender_ctx_t;

int my_defender_ctx_init(defender_ctx_t *ctx);
int my_defender_ctx_run(defender_ctx_t *ctx);
void my_defender_ctx_destroy(defender_ctx_t *ctx);