/*
** EPITECH PROJECT, 2020
** Exception
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception
{
    public:
        Exception(std::string const &str) {message = str;}
        std::string what() {return (message);}
    private:
        std::string message;
};
