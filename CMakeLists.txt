cmake_minimum_required(VERSION 3.10)
project(untitled1)

include_directories(${CMAKE_SOURCE_DIR}/listac_funciones)
include_directories(${CMAKE_SOURCE_DIR}/poker_funciones)
include_directories(${CMAKE_SOURCE_DIR}/cola_funciones)


set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(untitled1 main.c)

# Agregar archivos.c de las bibliotecas
# Ejemplo para la carpeta "listac_funciones"
file(GLOB_RECURSE lista_funciones_sources RELATIVE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/listac_funciones/*.c")
add_library(lista_funciones ${lista_funciones_sources})

# Repite el paso anterior para otras carpetas de bibliotecas

# Vincular las bibliotecas con el ejecutable principal
target_link_libraries(untitled1 lista_funciones poker_funciones cola_funciones)
