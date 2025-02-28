#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "users.h"
#include "processes.h"
#include "help.h"
#include "log.h"
#include "errors.h"

int main(int argc, char* argv[]) {
    int opt;
    FILE* log_file = NULL;
    FILE* error_file = stderr;

    struct option long_options[] = {
        {"users", no_argument, 0, 'u'},
        {"processes", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"log", required_argument, 0, 'l'},
        {"errors", required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "uphl:e:", long_options, NULL)) != -1) {
        switch (opt) {
        case 'l':
            // Перенаправляем обычный вывод в файл логов
            log_file = set_log_file(optarg);
            if (!log_file) {
                fprintf(stderr, "Ошибка: не удалось открыть файл логов: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'e':
            // Перенаправляем ошибки в файл
            error_file = set_error_file(optarg);
            if (!error_file) {
                fprintf(stderr, "Ошибка: не удалось открыть файл ошибок: %s\n", optarg);
                exit(EXIT_FAILURE);
            }
            // Меняем стандартный поток ошибок
            dup2(fileno(error_file), STDERR_FILENO);
            break;

        case 'u':
            list_users(stdout, log_file);
            break;

        case 'p':
            list_processes(stdout, log_file);
            break;

        case 'h':
            print_help(stdout);
            if (log_file) {
                print_help(log_file);
            }
            exit(EXIT_SUCCESS);

        default:
            print_help(stderr);
            exit(EXIT_FAILURE);
        }
    }

    // Если не было аргументов или не вызвали ни одну из функций, можно, например, вывести help:
    if (optind == 1) {
        print_help(stdout);
    }

    if (log_file) {
        fclose(log_file);
    }
    if (error_file != stderr) {
        fclose(error_file);
    }

    return 0;
}
