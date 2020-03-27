/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Backtrack
*/

#include "Backtrack.hpp"

Backtrack::Backtrack(std::pair<float, float> gPos, std::vector<std::string> maze)
{
    _gPos = gPos;
    _dest = std::make_pair(10, 10);
    _stack.push(gPos);
    createMaze();
    _cPos = gPos;
    _maze = maze;
    _maze[_cPos.first][_cPos.second] = 'W';
    _finalPath.push(gPos);
    ctrBacktracking();
}

/* void Backtrack::display()
{
    auto it = _maze.begin();

    for (; it != _maze.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "\n\n\n\n";
} */

//0 = egal ; 1 = toLow ; 2 = toHigh
//0 = egal ; 1 = toRight ; 2 = toLeft

bool Backtrack::checkMazePos(int y, int x)
{
    if (x >= _sizeX || y >= _sizeY)
        return false;
    if (x <= 0 || y <= 0)
        return false;
    if (_maze[y][x] != 'X' && _maze[y][x] != 'W')
        return true;
    return false;
}

void Backtrack::checkOtherWay()
{
    int nb = 0;

    if (checkMazePos(_cPos.first + 1, _cPos.second))
        nb++;
    if (checkMazePos(_cPos.first - 1, _cPos.second))
        nb++;
    if (checkMazePos(_cPos.first, _cPos.second + 1))
        nb++;
    if (checkMazePos(_cPos.first, _cPos.second - 1))
        nb++;
    if (nb > 1) {
        _nbWay = nb;
        _stack.push(_cPos);
    }
}

void Backtrack::assignPath(int y, int x)
{
    _maze[y][x] = 'W';
    _cPos.first = y;
    _cPos.second = x;
    _finalPath.push(_cPos);
}

//first = y; second = x

void Backtrack::editWay()
{
    if (_cPos.first == _dest.first && _cPos.second == _dest.second) {
        _dest.first = 12;
        _dest.second = 12;
    }
}

void Backtrack::deblock()
{
    if (checkMazePos(_cPos.first, _cPos.second + 1)) {
        assignPath(_cPos.first, _cPos.second + 1);
        return;
    }
    if (checkMazePos(_cPos.first + 1, _cPos.second)) {
        assignPath(_cPos.first + 1, _cPos.second);
        return;
    }
    if (checkMazePos(_cPos.first - 1, _cPos.second)) {
        assignPath(_cPos.first - 1, _cPos.second);
        return;
    }
    if (checkMazePos(_cPos.first, _cPos.second - 1)) {
        assignPath(_cPos.first, _cPos.second - 1);
        return;
    }
}

void Backtrack::recBacktracking()
{
    checkOtherWay();
    editWay();
    std::cout << "first pos " << _cPos.first << "second pos " << _cPos.second << "dest first" << _dest.first << "dest second" << _dest.second << std::endl;
    if (_cPos.first < _dest.first && checkMazePos(_cPos.first + 1, _cPos.second)) {
            assignPath(_cPos.first + 1, _cPos.second);
            return recBacktracking();
    }
    else {
        if (checkMazePos(_cPos.first - 1, _cPos.second)) {
            assignPath(_cPos.first - 1, _cPos.second);
            return recBacktracking();
        }
    }
    if (_cPos.second < _dest.second && checkMazePos(_cPos.first, _cPos.second + 1)) {
            assignPath(_cPos.first, _cPos.second + 1);
            return recBacktracking();
        }
    else {
        if (checkMazePos(_cPos.first, _cPos.second - 1)) {
            assignPath(_cPos.first, _cPos.second - 1);
            return recBacktracking();
        }
    }
    if (_nbWay > 0) {
        assignPath(_gPos.first, _gPos.second);
        deblock();
        _nbWay = 0;
        return recBacktracking();
    }
}

void Backtrack::newWay()
{
    _cPos = _stack.top();
    if (_finalPath.size() != 1) {
        while (_finalPath.size() > 1 && _finalPath.top() != _stack.top())
            _finalPath.pop();
    }
    if (_stack.size() != 1)
        _stack.pop();
}

void Backtrack::cleanFinalPath()
{
    std::pair<int, int> pos;

    if (_finalPath.empty())
        return;
    pos = _finalPath.top();
    _tmpMaze[pos.first][pos.second] = 'W';
    _finalPath.pop();
    cleanFinalPath();
}

/* void Backtrack::displayTmp()
{
    auto it = _tmpMaze.begin();
    std::cout << "\n\n\n\n\n\n\n\n\n";
    std::cout << "final ->" << std::endl;
    for (; it != _tmpMaze.end(); ++it) {
        std::cout << *it << std::endl;
    }
} */

bool Backtrack::stopLoop()
{
    if (_cPos.first >= 12 && _cPos.first <= 13
    &&_cPos.second >= 9 && _cPos.second <= 11)
        return false;
    return true;
}

void Backtrack::ctrBacktracking()
{
    while (stopLoop()) {
        /* usleep(1000000); */
        newWay();
        recBacktracking();
        /* display(); */
    }
    cleanFinalPath();
    /* displayTmp(); */
}

Backtrack::~Backtrack()
{
}