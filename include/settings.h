#pragma once

#include <stdint.h>

#include "waves.h"

typedef struct settings_s {
    uint32_t fps;
    char *window_name;
    waves_t waves;
} settings_t;

#define DEFAULT_FPS 30
#define DEFAULT_WINDOW_NAME "MyDefender"

int fps_setting_handler(settings_t *settings, const char *av[]);
int window_name_setting_handler(settings_t *settings, const char *av[]);
int config_setting_handler(settings_t *settings, const char *av[]);