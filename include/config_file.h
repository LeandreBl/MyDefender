#pragma once

#include "lvector.h"

typedef lvector(char *) config_file_t;

int config_file_create(config_file_t *file, const char *filename);
void config_file_destroy(config_file_t *file);