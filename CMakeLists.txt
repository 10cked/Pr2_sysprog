cmake_minimum_required(VERSION 3.0)
project(my_console_tool C)

set(CMAKE_C_STANDARD 99)

add_executable(my_console_tool
    main.c
    processes.c
    processes.h
    users.c
    users.h
    help.c
    help.h
    log.c
    log.h
    errors.c
    errors.h
)

# При желании можно добавить дополнительные флаги компиляции:
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
