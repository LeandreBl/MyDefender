#include <stdio.h>

#include "utils.h"
#include "wave_config.h"

static int bind_wavename(wave_config_t *config, const char *keyword,
                         const char *line);
static int bind_mobs(wave_config_t *config, const char *keyword,
                     const char *line);

static int bind_difficulty(wave_config_t *config, const char *keyword,
                           const char *line);

static const wconfig_bind_t WAVE_CONFIG_BINDS[] = {
    {
        .keyword = WAVENAME_KEYWORD,
        .bind = &bind_wavename,
    },
    {
        .keyword = MOB_KEYWORD,
        .bind = &bind_mobs,
    },
    {
        .keyword = DIFFICULTY_KEYWORD,
        .bind = &bind_difficulty,
    },
};

static int bind_wavename(wave_config_t *config, const char *keyword,
                         const char *line)
{
    char *token = goto_next_token(line, strlen(keyword));

    if (token == NULL) {
        fprintf(stderr, "\"%s\": Syntax error (missing string)\n", line);
        return -1;
    }
    if (config->name != NULL) {
        free(token);
        return 1;
    }
    config->name = token;
    return 0;
}

static int bind_mobs(wave_config_t *config, const char *keyword,
                     const char *line)
{
    char *token;
    char *count;
    char *nptr;
    size_t value;

    if (config->name == NULL) {
        fprintf(
            stderr,
            "\"%s\": Unexpected mob declaration without a leading wavename\n",
            line);
        return -1;
    }
    token = goto_next_token(line, strlen(keyword));
    if (token == NULL) {
        fprintf(stderr, "\"%s\": Syntax error (missing identifier)\n", line);
        return -1;
    }
    count = find_next_token(token, ": ");
    if (count == NULL) {
        fprintf(stderr,
                "\"%s\": Syntax error (missing count after identifier)\n",
                line);
        free(token);
        return -1;
    }
    value = strtoul(count, &nptr, 10);
    free(count);
    if (nptr == count) {
        fprintf(stderr, "\"%s\": Syntax error (invalid value)\n", line);
        free(token);
        return -1;
    }
    remove_after(token, ": ");
    lvector_emplace_back(config->mobs_settings, mob_wave_create, token, value);
    free(token);
    return 0;
}

static int bind_difficulty(wave_config_t *config, const char *keyword,
                           const char *line)
{
    char *token = goto_next_token(line, strlen(keyword));
    char *nptr;
    size_t difficulty;

    if (token == NULL) {
        fprintf(stderr, "\"%s\": Syntax error (missing string)\n", line);
        return -1;
    }
    difficulty = strtoul(token, &nptr, 10);
    free(token);
    if (nptr == token) {
        fprintf(stderr, "\"%s\": Syntax error (unexpected value)\n", line);
        return -1;
    }
    config->difficulty = difficulty;
    return 0;
}

static int call_wrapper(wave_config_t *wave, const char *line)
{
    size_t len;
    const char *keyword;

    for (size_t i = 0; i < ARRAY_LENGTH(WAVE_CONFIG_BINDS); ++i) {
        keyword = WAVE_CONFIG_BINDS[i].keyword;
        len = strlen(keyword);
        if (strncmp(line, keyword, len) == 0) {
            return WAVE_CONFIG_BINDS[i].bind(wave, keyword, line);
        }
    }
    fprintf(stderr, "%s: Syntax error (unexpected keyword)\n", line);
    return -1;
}

int wave_config_create_from_file(wave_config_t *wave, config_file_t *file,
                                 size_t *offset)
{
    int status;

    memset(wave, 0, sizeof(*wave));
    lvector_create(wave->mobs_settings, 0, mob_wave_destroy);
    for (size_t i = *offset; i < file->len; ++i) {
        status = call_wrapper(wave, file->arr[i]);
        if (status == -1)
            return -1;
        if (status == 1)
            break;
        *offset += 1;
    }
    return 0;
}

void wave_config_destroy(wave_config_t *wave)
{
    free(wave->name);
    lvector_destroy(wave->mobs_settings);
}