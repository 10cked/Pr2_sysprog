#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

int compare_users(const void* a, const void* b) {
    return strcmp((*(struct passwd**)a)->pw_name, (*(struct passwd**)b)->pw_name);
}

void list_users(FILE* console_output, FILE* log_output) {
    struct passwd* pw;
    struct passwd** pw_list = NULL;
    size_t count = 0;

    setpwent();
    while ((pw = getpwent()) != NULL) {
        if (!pw->pw_dir || strcmp(pw->pw_dir, "/nonexistent") == 0) {
            continue; // Пропускаем пользователей без домашней папки
        }

        struct passwd* copy = malloc(sizeof(struct passwd));
        if (!copy) {
            fprintf(stderr, "Ошибка: недостаточно памяти\n");
            endpwent();
            return;
        }

        copy->pw_name = strdup(pw->pw_name);
        copy->pw_dir = strdup(pw->pw_dir);

        if (!copy->pw_name || !copy->pw_dir) {
            fprintf(stderr, "Ошибка: недостаточно памяти\n");
            free(copy->pw_name);
            free(copy->pw_dir);
            free(copy);
            endpwent();
            return;
        }

        struct passwd** temp = realloc(pw_list, sizeof(struct passwd*) * (count + 1));
        if (!temp) {
            fprintf(stderr, "Ошибка: недостаточно памяти\n");
            free(copy->pw_name);
            free(copy->pw_dir);
            free(copy);
            endpwent();
            return;
        }
        pw_list = temp;
        pw_list[count++] = copy;
    }
    endpwent();

    qsort(pw_list, count, sizeof(struct passwd*), compare_users);

    for (size_t i = 0; i < count; i++) {
        fprintf(console_output, "Пользователь: %s, Домашняя директория: %s\n",
            pw_list[i]->pw_name, pw_list[i]->pw_dir);
        if (log_output) {
            fprintf(log_output, "Пользователь: %s, Домашняя директория: %s\n",
                pw_list[i]->pw_name, pw_list[i]->pw_dir);
        }
        free(pw_list[i]->pw_name);
        free(pw_list[i]->pw_dir);
        free(pw_list[i]);
    }
    free(pw_list);
}
