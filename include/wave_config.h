#pragma once

#include "lvector.h"
#include "mob.h"
#include "config_file.h"
#include "mob_wave.h"

typedef struct wave_config_s {
	char *name;
	lvector(mob_wave_t) mobs_settings;
	size_t difficulty;
} wave_config_t;

typedef struct wave_config_bind_s {
	const char *keyword;
	int (*bind)(wave_config_t *config, const char *keyword, const char *line);
} wconfig_bind_t;

/*
**  wavename: string
**	difficulty: integer
**  - string (mob name): uint (count)
**  ...
*/

#define WAVENAME_KEYWORD "wavename: "
#define MOB_KEYWORD "- "
#define DIFFICULTY_KEYWORD "difficulty: "

int wave_config_create_from_file(wave_config_t *wave, config_file_t *file, size_t *offset);
void wave_config_destroy(wave_config_t *wave);