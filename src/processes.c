#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "processes.h"

static int compare_pids(const void* a, const void* b) {
    int pidA = *(const int*)a;
    int pidB = *(const int*)b;
    return (pidA - pidB);
}

void list_processes(FILE* console_output, FILE* log_output) {
    DIR* dp = opendir("/proc");
    if (dp == NULL) {
        fprintf(console_output, "Ошибка: не удалось открыть /proc\n");
        if (log_output) {
            fprintf(log_output, "Ошибка: не удалось открыть /proc\n");
        }
        return;
    }

    // Динамический массив для хранения PID
    int* pid_list = NULL;
    size_t pid_count = 0;

    struct dirent* entry;
    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
            int pid = atoi(entry->d_name);
            int* temp = realloc(pid_list, (pid_count + 1) * sizeof(int));
            if (!temp) {
                fprintf(console_output, "Ошибка: не хватает памяти для списка PID\n");
                if (log_output) {
                    fprintf(log_output, "Ошибка: не хватает памяти для списка PID\n");
                }
                free(pid_list);
                closedir(dp);
                return;
            }
            pid_list = temp;
            pid_list[pid_count++] = pid;
        }
    }
    closedir(dp);

    // Сортируем массив PID
    qsort(pid_list, pid_count, sizeof(int), compare_pids);

    // Выводим процессы по возрастанию PID
    for (size_t i = 0; i < pid_count; i++) {
        char path[256];
        snprintf(path, sizeof(path), "/proc/%d/cmdline", pid_list[i]);

        FILE* cmd_file = fopen(path, "r");
        if (cmd_file) {
            char cmdline[256] = { 0 };
            if (fgets(cmdline, sizeof(cmdline), cmd_file) != NULL) {
                fprintf(console_output, "PID: %d | Процесс: %s\n", pid_list[i], cmdline);
                if (log_output) {
                    fprintf(log_output, "PID: %d | Процесс: %s\n", pid_list[i], cmdline);
                }
            }
            else {
                fprintf(console_output, "PID: %d | Процесс: [неизвестно]\n", pid_list[i]);
                if (log_output) {
                    fprintf(log_output, "PID: %d | Процесс: [неизвестно]\n", pid_list[i]);
                }
            }
            fclose(cmd_file);
        }
        else {
            fprintf(console_output, "PID: %d | Процесс: [неизвестно]\n", pid_list[i]);
            if (log_output) {
                fprintf(log_output, "PID: %d | Процесс: [неизвестно]\n", pid_list[i]);
            }
        }
    }

    free(pid_list);
}
