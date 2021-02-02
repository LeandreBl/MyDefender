#pragma once

#define ARRAY_LENGTH(array) sizeof(array) / sizeof(*array)

char *goto_next_token(const char *src, size_t n);

char *find_next_token(const char *src, const char *pattern);

void remove_after(char *src, const char *pattern);