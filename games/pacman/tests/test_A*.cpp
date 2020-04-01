/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** test_A*
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Backtrack.hpp"

static std::vector<std::string> maze = {
    {"XXXXXXXXXXXXXXXXXXXXX"},
    {"X*********X*********X"},
    {"X*XXX*XXX*X*XXX*XXX*X"},
    {"XGXXX*XXX*X*XXX*XXXGX"},
    {"X*XXX*XXX*X*XXX*XXX*X"},
    {"X*******************X"},
    {"X*XXX*X*XXXXX*X*XXX*X"},
    {"X*XXX*X*XXXXX*X*XXX*X"},
    {"X*****X***X***X*****X"},
    {"XXXXX*XXX X XXX*XXXXX"},
    {"    X*X   R   X*X"},
    {"    X*X X---X X*X"},
    {"XXXXX*X X   X X*XXXXX"},
    {"    *  XBOYX  *      "},
    {"XXXXX*X XXXXX X*XXXXX"},
    {"    X*X       X*X"},
    {"    X*X XXXXX X*X"},
    {"XXXXX*X XXXXX X*XXXXX"},
    {"X*********X*********X"},
    {"X*XXX*XXX*X*XXX*XXX*X"},
    {"XG**X*****P*****X**GX"},
    {"XXX*X*X*XXXXX*X*X*XXX"},
    {"XXX*X*X*XXXXX*X*X*XXX"},
    {"X*****X***X***X*****X"},
    {"X*XXXXXXX*X*XXXXXXX*X"},
    {"X*******************X"},
    {"XXXXXXXXXXXXXXXXXXXXX"},
};

static std::pair<float, float> gPos = std::pair<float, float>(1,1);
static std::pair<float, float> gDest = std::pair<float, float>(10,20);

Test(head_test, neq_count)
{
    Backtrack p(gPos, maze, gDest);

    cr_expect_not_null(p.getPath());
}