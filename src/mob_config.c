#include <stdio.h>

#include "utils.h"
#include "mob_config.h"

static int bind_mobname(mob_config_t *config, const char *keyword, const char *line);
static int bind_mobhealth(mob_config_t *config, const char *keyword, const char *line);
static int bind_mobspeed(mob_config_t *config, const char *keyword, const char *line);
static int bind_mobtexture(mob_config_t *config, const char *keyword, const char *line);

static const mconfig_bind_t MOB_CONFIG_BINDS[] = {
    {
        .keyword = MOBNAME_KEYWORD,
        .bind = &bind_mobname,
    },
    {
        .keyword = MOBHEALTH_KEYWORD,
        .bind = &bind_mobhealth,
    },
    {
        .keyword = MOBSPEED_KEYWORD,
        .bind = &bind_mobspeed,
    },
    {
        .keyword = MOBTEXTURE_KEYWORD,
        .bind = &bind_mobtexture,
    },
};

static int bind_mobname(mob_config_t *config, const char *keyword, const char *line)
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

static int bind_mobhealth(mob_config_t *config, const char *keyword, const char *line)
{
    char *token = goto_next_token(line, strlen(keyword));
    char *nptr;
    float health;

    if (token == NULL) {
        fprintf(stderr, "\"%s\": Syntax error (missing string)\n", line);
        return -1;
    }
    health = strtof(token, &nptr);
    free(token);
    if (nptr == token) {
        fprintf(stderr, "\"%s\": Syntax error (unexpected value)\n", line);
        return -1;
    }
    config->health = health;
    return 0;
}

static int bind_mobspeed(mob_config_t *config, const char *keyword, const char *line)
{
    char *token = goto_next_token(line, strlen(keyword));
    char *nptr;
    float speed;

    if (token == NULL) {
        fprintf(stderr, "\"%s\": Syntax error (missing string)\n", line);
        return -1;
    }
    speed = strtof(token, &nptr);
    free(token);
    if (nptr == token) {
        fprintf(stderr, "\"%s\": Syntax error (unexpected value)\n", line);
        return -1;
    }
    config->speed = speed;
    return 0;
}

static int bind_mobtexture(mob_config_t *config, const char *keyword, const char *line)
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
    config->texture_file = token;
    return 0;
}

static int call_wrapper(mob_config_t *wave, const char *line)
{
    size_t len;
    const char *keyword;

    for (size_t i = 0; i < ARRAY_LENGTH(MOB_CONFIG_BINDS); ++i) {
        keyword = MOB_CONFIG_BINDS[i].keyword;
        len = strlen(keyword);
        if (strncmp(line, keyword, len) == 0) {
            return MOB_CONFIG_BINDS[i].bind(wave, keyword, line);
        }
    }
    fprintf(stderr, "%s: Syntax error (unexpected keyword)\n", line);
    return -1;
}

int mob_config_create_from_file(mob_config_t *mob, config_file_t *file, size_t *offset)
{
    int status;

    memset(mob, 0, sizeof(*mob));
    for (size_t i = *offset; i < file->len; ++i) {
        status = call_wrapper(mob, file->arr[i]);
        if (status == -1)
            return -1;
        if (status == 1)
            break;
        *offset += 1;
    }
    return 0;
}

void mob_config_destroy(mob_config_t *mob)
{
    free(mob->name);
    free(mob->texture_file);
}