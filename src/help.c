#include <stdio.h>
#include "help.h"

void print_help(FILE* output) {
    fprintf(output, "Использование: my_console_tool [ОПЦИИ]\n");
    fprintf(output, "Опции:\n");
    fprintf(output, "  -u, --users            Вывести список пользователей (отсортированных по имени)\n");
    fprintf(output, "  -p, --processes        Вывести список процессов (отсортированных по PID)\n");
    fprintf(output, "  -h, --help             Показать эту справку и завершить работу\n");
    fprintf(output, "  -l PATH, --log PATH    Записывать обычный вывод в файл\n");
    fprintf(output, "  -e PATH, --errors PATH Записывать ошибки в файл\n");
}
