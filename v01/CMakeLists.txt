cmake_minimum_required(VERSION 3.20)
project(LP_redone C)

set(CMAKE_C_STANDARD 99)

add_executable(LP_redone main.c menu_admin.c menu_admin.h structs.h auxilio.c auxilio.h cliente.c cliente.h ficheiros.c ficheiros.h principal.c principal.h)
