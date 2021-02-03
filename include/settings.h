#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "waves.h"
#include "mobs.h"

typedef struct settings_s {
    uint32_t fps;
    char *window_name;
    waves_t waves;
    mobs_t mobs;
    bool verbose;
} settings_t;

#define DEFAULT_FPS 30
#define DEFAULT_WINDOW_NAME "MyDefender"

int fps_setting_handler(settings_t *settings, const char *av[]);
int window_name_setting_handler(settings_t *settings, const char *av[]);
int waves_setting_handler(settings_t *settings, const char *av[]);
int mobs_setting_handler(settings_t *settings, const char *av[]);
int verbose_setting_handler(settings_t *settings, const char *av[]);

void settings_print(const settings_t *settings);