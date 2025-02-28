
Это консольная утилита на языке C, которая обрабатывает аргументы командной строки и выполняет различные действия:

- При `-u` или `--users` утилита выводит перечень пользователей и их домашние директории (отсортированные по имени).
- При `-p` или `--processes` утилита выводит список запущенных процессов (отсортированный по PID).
- При `-h` или `--help` утилита выводит справку.
- При `-l PATH` или `--log PATH` вывод перенаправляется в заданный файл.
- При `-e PATH` или `--errors PATH` ошибки перенаправляются в заданный файл.

Утилита разбирает аргументы командной строки при помощи `getopt_long`.
Сборка проекта осуществляется с помощью **CMake**.

## Инструкция по сборке и использованию

1. **Клонировать репозиторий и перейти в корневой каталог:**
   ```bash
   git clone https://github.com/10cked/Pr2_sysprog.git
   cd my_console_tool
   ```
2. **Создать и перейти в директорию сборки:**
   ```bash
   mkdir build
   cd build
   ```
3. **Запустить CMake и собрать проект:**
   ```bash
   cmake ..
   make
   ```
4. **Запустить утилиту:**
   ```bash
   ./my_console_tool -h
   ```
   Пример использования:
   ```bash
   ./my_console_tool --users
   ./my_console_tool --processes
   ./my_console_tool --help
   ./my_console_tool --log out.txt --users
   ./my_console_tool --errors err.txt --processes
   ```

