/*
** EPITECH PROJECT, 2020
** Encapsulation.hpp
** File description:
** Encapsulation.hpp
*/

#pragma once

#include <dirent.h>
#include <dlfcn.h>

class Encapsulation
{
    public:
        static void *fct_dlopen(const char *filename, int flag);
        static int fct_dlclose(void *handle);
        static void *fct_dlsym(void *handle, const char *symbol);
        static DIR *fct_opendir(const char *name);
        static struct dirent *fct_readdir(DIR *dir);
        static int fct_closedir(DIR *dir);
};