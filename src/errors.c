#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "errors.h"

FILE* set_error_file(const char* path) {
    FILE* file = fopen(path, "w");
    if (!file) {
        fprintf(stderr, "Ошибка: не удалось открыть файл ошибок: %s\n", path);
        return NULL;
    }
    return file;
}
