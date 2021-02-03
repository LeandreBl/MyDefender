#pragma once

#include "config_file.h"

typedef struct mob_config_s {
    char *name;
    char *texture_file;
    float health;
    float speed;
} mob_config_t;

typedef struct mob_config_bind_s {
	const char *keyword;
	int (*bind)(mob_config_t *config, const char *keyword, const char *line);
} mconfig_bind_t;

/*
**  mobname: string
**  health: float
**  speed: float
*/

#define MOBNAME_KEYWORD "mobname: "
#define MOBHEALTH_KEYWORD "health: "
#define MOBSPEED_KEYWORD "speed: "
#define MOBTEXTURE_KEYWORD "texture-file: "

int mob_config_create_from_file(mob_config_t *mob, config_file_t *file, size_t *offset);
void mob_config_destroy(mob_config_t *mob);
