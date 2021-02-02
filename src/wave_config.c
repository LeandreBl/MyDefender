#include <stdio.h>

#include "wave.h"
#include "lbl-libc.h"

struct wave_config_bind_s {
    const char *keyword;
    int (*bind)(wave_config_t *config, const char *keyword, const char *line, size_t lineno);
};

static int emplace_wave(wave_config_t *wave, char *name)
{
    wave->name = name;
    lvector_create(wave->mobs_settings, 0, NULL);
    //toset destructor
    return 0;
}

static int bind_wavename(waves_t *config, const char *keyword, const char *line, size_t lineno)
{
    char *p = strstr(line, keyword);
    char *name;
    size_t n;

    name = strdup(p);
    if (name == NULL)
        return -1;
    epur_str(name);
    n = strlen(name);
    if (n == 0) {
        fprintf(stderr, "%zu: Syntax error (missing string)\n", lineno);
        free(name);
        return -1;
    }
    lvector_foreach(wave, *config) {
        if (strcmp(wave->name, name) == 0) {
            fprintf(stderr, "%zu: Error: (%s already exists)\n", lineno, name);
            free(name);
            return -1;
        }
    }
    return 0;
}

static int bind_mobs(wave_config_t *config, const char *keyword, const char *line, size_t lineno)
{

}

static const struct wave_config_bind_s WAVE_CONFIG_BINDS[] = {
    {
        .keyword = "wavename: ",
        .bind = &bind_wavename,
    },
    {
        .keyword = "- ",
        .bind = &bind_mobs,
    }
};

int wave_config_create_from_file(wave_config_t *wave, config_file_t *file)
{
    size_t keyword_len;

    lvector_foreach(line, *file) {
        for (size_t i = 0; i < ARRAY_LENGTH(WAVE_CONFIG_BINDS); ++i) {
            keyword_len = strlen(WAVE_CONFIG_BINDS[i].keyword);
            if (strncmp(*line, WAVE_CONFIG_BINDS[i].keyword, keyword_len) == 0 && WAVE_CONFIG_BINDS[i].bind(config, *line) != 0) {
                fprintf(stderr, "Syntax error: \"%s\"\n", *line);
                return -1;
            }
        }
    }
    return 0;
}

void wave_config_destroy(wave_config_t *wave)
{

}