#include <stddef.h>

const char *path_to_file_name(const char * path)
{
    size_t i = 0;
    size_t pos = 0;
    char * p = (char *)path;
    while (*p) {
        i++;
        if (*p == '/' || *p == '\\') {
            pos = i;
        }
        p++;
    }
    return path + pos;
}
