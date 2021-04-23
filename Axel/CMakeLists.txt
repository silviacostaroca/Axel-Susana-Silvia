cmake_minimum_required(VERSION 3.19)
project(Axel C)

set(CMAKE_C_STANDARD 99)

add_executable(Axel main.c avl.c avl.h catalogo_users.c catalogo_users.h catalogo_bussines.c catalogo_bussines.h catalogo_reviews.c catalogo_reviews.h leitura.c leitura.h SGR.c SGR.h menu.c menu.h user.c user.h avl.c avl.h paginacao.c paginacao.h bussines.c bussines.h reviews.c reviews.h)