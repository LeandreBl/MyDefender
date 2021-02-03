#include <stdio.h>

#include "settings.h"

void settings_print(const settings_t *set)
{
    settings_t *settings = (settings_t *)set;

    printf(
        "FPS: %u\n"
        "WindowName: %s\n"
        "Waves: %zu\n",
        settings->fps,
        settings->window_name,
        settings->waves.len
    );
    lvector_foreach(wave, settings->waves) {
        printf("\tName: %s, difficulty: %zu\n", wave->name, wave->difficulty);
        lvector_foreach(ms, wave->mobs_settings) {
            printf("\t\tName: %s, count: %zu\n", ms->name, ms->count);
        }
    }
    printf("Mobs: %zu\n", settings->mobs.len);
    lvector_foreach(mob, settings->mobs) {
        printf("\tName: %s, Health: %0.2f, Speed: %0.2f, Texture-file: %s\n", mob->name, mob->health, mob->speed, mob->texture_file);
    }
}