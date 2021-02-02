#include <stdlib.h>
#include <string.h>

#include "lbl-libc.h"
#include "utils.h"

char *goto_next_token(const char *src, size_t n)
{
    char *newstr;

    newstr = strdup(src + n);
    if (newstr == NULL)
        return NULL;
    epur_str(newstr);
    if (newstr[0] == '\0') {
        free(newstr);
        return NULL;
    }
    return newstr;
}

void remove_after(char *src, const char *pattern)
{
    size_t len = strlen(src);
    char *p = strstr(src, pattern);

    if (p == NULL)
        return;
    shift_right(src, len - (p - src));
}

char *find_next_token(const char *src, const char *pattern)
{
    char *pstr = strstr(src, pattern);

    if (pstr == NULL)
        return NULL;
    return goto_next_token(src, pstr - src + strlen(pattern));
}