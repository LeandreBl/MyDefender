#include <stdio.h>
#include "config_file.h"

static void free_pstr(char **pstr)
{
    free(*pstr);
}

int config_file_create(config_file_t *file, const char *filename)
{
    FILE *f = fopen(filename, "r");
    char *line;
    size_t n;
    ssize_t rd;

    if (f == NULL) {
        fprintf(stderr, "\"%s\" is not a valid file\n");
        return -1;
    }
    lvector_create(file->lines, 0, free_pstr);
    do {
        n = 0;
        line = NULL;
        rd = getline(&line, &n, f);
        if (rd == -1) {
            fclose(f);
            return -1;
        }
        lvector_push_back(file->lines, line);
    } while (rd != 0);
    file->offset = 0;
    fclose(f);
    return 0;
}

void config_file_destroy(config_file_t *file)
{
    lvector_destroy(file->lines);
}