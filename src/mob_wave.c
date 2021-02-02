#include <stdlib.h>
#include <string.h>

#include "mob_wave.h"

int mob_wave_create(mob_wave_t *mw, const char *name, size_t count)
{
    mw->name = strdup(name);
    if (mw->name == NULL) {
        return -1;
    }
    mw->count = count;
    return 0;
}

void mob_wave_destroy(mob_wave_t *mw)
{
    free(mw->name);
}