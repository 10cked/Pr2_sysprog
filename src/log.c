#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "log.h"

FILE* set_log_file(const char* path) {
    FILE* file = fopen(path, "w");
    if (!file) {
        fprintf(stderr, "Ошибка: не удалось открыть лог-файл: %s\n", path);
        return NULL;
    }
    return file;
}
