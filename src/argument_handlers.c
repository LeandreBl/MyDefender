#include <stdlib.h>
#include <stdio.h>

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
    settings->window_name = av[1];
    return 0;
}