#include <stdbool.h>
#include <stdio.h>

#include "config_file.h"
#include "lbl-libc.h"

static void free_pstr(char **pstr)
{
    free(*pstr);
}

static int retrieve_next_line(FILE *f, char **pline)
{
    size_t n = 0;
    char *line = NULL;

    if (getline(&line, &n, f) <= 0) {
        free(line);
        return -1;
    }
    epur_str(line);
    remove_str(line, "\n");
    if (line[0] == '\0') {
        free(line);
        return 0;
    }
    *pline = line;
    return 1;
}

int config_file_create(config_file_t *file, const char *filename)
{
    FILE *f = fopen(filename, "r");
    char *line;
    int status;

    if (f == NULL)
        return -1;
    lvector_create(*file, 0, free_pstr);
    do {
        status = retrieve_next_line(f, &line);
        if (status == 1)
            lvector_push_back(*file, line);
    } while (status != -1);
    fclose(f);
    return 0;
}

void config_file_destroy(config_file_t *file)
{
    lvector_destroy(*file);
}