#pragma once

#include <stdint.h>

typedef struct settings_s {
    uint32_t fps;
    const char *window_name;
} settings_t;

int fps_setting_handler(settings_t *settings, const char *av[]);
int window_name_setting_handler(settings_t *settings, const char *av[]);