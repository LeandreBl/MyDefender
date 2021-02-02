#include <stdio.h>
#include <stdlib.h>

#include "settings.h"

int fps_setting_handler(settings_t *settings, const char *av[])
{
    char *np;
    long v = strtol(av[1], &np, 10);

    if (np == av[1] || v <= 0) {
        fprintf(stderr, "\"%s\" is not a valid framerate\n", av[1]);
        return -1;
    }
    settings->fps = (typeof(settings->fps))v;
    return 0;
}

int window_name_setting_handler(settings_t *settings, const char *av[])
{
    settings->window_name = strdup(av[1]);
    if (settings->window_name == NULL)
        return -1;
    return 0;
}

int config_setting_handler(settings_t *settings, const char *av[])
{
    config_file_t file;
    wave_config_t cfg;
    size_t i = 0;

    if (config_file_create(&file, av[1]) == -1) {
        fprintf(stderr, "\"%s\" is not a valid file (%m)\n", av[1]);
        return -1;
    }
    lvector_create(settings->waves, 0, wave_config_destroy);
    while (i < file.len) {
        if (wave_config_create_from_file(&cfg, &file, &i) == -1) {
            config_file_destroy(&file);
            return -1;
        }
        lvector_push_back(settings->waves, cfg);
    }
    config_file_destroy(&file);
    return 0;
}