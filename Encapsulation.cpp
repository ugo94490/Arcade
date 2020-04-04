/*
** EPITECH PROJECT, 2020
** Encapsulation.cpp
** File description:
** Encapsulation.cpp
*/

#include "Encapsulation.hpp"
#include "Exception.hpp"

void *Encapsulation::fct_dlopen(const char *filename, int flag)
{
    return (dlopen(filename, flag));
}

int Encapsulation::fct_dlclose(void *handle)
{
    return (dlclose(handle));
}

void *Encapsulation::fct_dlsym(void *handle, const char *symbol)
{
    return (dlsym(handle, symbol));
}

DIR *Encapsulation::fct_opendir(const char *name)
{
    DIR *dir = opendir(name);

    if (!dir)
        throw(Exception ("Can't open directory"));
    return (dir);
}

struct dirent *Encapsulation::fct_readdir(DIR *dir)
{
    return (readdir(dir));
}

int Encapsulation::fct_closedir(DIR *dir)
{
    return (closedir(dir));
}