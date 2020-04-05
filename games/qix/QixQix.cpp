/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** QixQix
*/

#include "QixQix.hpp"

QixQix::QixQix(float posx, float posy)
{
    timer_move = 15;
    nodes.clear();
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 16.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 32.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 48.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 64.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 80.0, posy)));
}

QixQix::~QixQix()
{

}

void QixQix::setPos(float posx, float posy)
{
    nodes.clear();
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 16.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 32.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 48.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 64.0, posy)));
    nodes.push_back(std::shared_ptr<QixQixNode>(new QixQixNode(posx + 80.0, posy)));
}

int QixQix::check_can_move(std::list<std::shared_ptr<QixGround>> tiles)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if ((*it)->check_can_move(tiles) == 0) {
            return 0;
        }
    }
    return 1;
}

void QixQix::move(std::list<std::shared_ptr<QixGround>> tiles)
{
    int direction = 0;

    timer_move++;
    if (timer_move < 8)
        return;
    direction = rand() % 4 + 1;
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        (*it)->setDirection(direction);
    if (check_can_move(tiles) != 1) {
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
            (*it)->setDirection(0);
    }
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        (*it)->move_direction();
    timer_move = 0;
}

std::list<std::shared_ptr<QixQixNode>> QixQix::getNodes(void) const
{
    return nodes;
}