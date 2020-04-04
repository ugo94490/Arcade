/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Backtrack
*/

#include "Backtrack.hpp"

Backtrack::Backtrack(std::pair<float, float> gPos, std::vector<std::string> maze, std::pair<float, float> dest, bool pacDest)
{
    _pacDest = pacDest;
    _cPos.first = gPos.second;
    _cPos.second = gPos.first;
    _dest.first = dest.second;
    _dest.second = dest.first;
    _stack.push(_cPos);
    _maze = maze;
    _maze[_dest.first][_dest.second] = 'T';
    _maze[_cPos.first][_cPos.second] = 'W';
    _tmpMaze = maze;
    ctrBacktracking();
}

void Backtrack::display()
{
    auto it = _maze.begin();

    for (; it != _maze.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "\n";
}


bool Backtrack::checkMazePos(size_t y, size_t x)
{
    if (x >= _maze[y].size() || y >= _maze.size())
        return false;
    if (x <= 0 || y <= 0)
        return false;
    if (_maze[y][x] == 'X' || _maze[y][x] == 'W')
        return false;
    if (_pacDest == true && _maze[y][x] == '-')
        return false;
    return true;
}

int Backtrack::checkOtherWay(int y, int x)
{
    int nb = 0;

    if (checkMazePos(y + 1, x))
        nb++;
    if (checkMazePos(y - 1, x))
        nb++;
    if (checkMazePos(y, x + 1))
        nb++;
    if (checkMazePos(y, x - 1))
        nb++;
    if (nb > 1)
        _stack.push(_cPos);
    return nb;
}

void Backtrack::assignPath(int y, int x)
{
    _maze[y][x] = 'W';
    _cPos.first = y;
    _cPos.second = x;
    _finalPath.push(_cPos);
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
    int nbWay = 0;

    if (!stopLoop())
        return;
    nbWay = checkOtherWay(_cPos.first, _cPos.second);
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
    if (nbWay > 0) {
        deblock();
        return recBacktracking();
    }
}

void Backtrack::newWay()
{
    _cPos = _stack.top();
    if (_finalPath.size() > 1) {
        while (_finalPath.size() > 1 && _finalPath.top() != _stack.top())
            _finalPath.pop();
    }
    if (_stack.size() != 1)
        _stack.pop();
    checkOtherWay(_cPos.first, _cPos.second);
}

void Backtrack::cleanFinalPath()
{
    std::pair<int, int> pos;

    for (size_t i = 0; i != _finalPos.size(); i++) {
        _tmpMaze[_finalPos[i].first][_finalPos[i].second] = 'W';
    }
}

void Backtrack::displayTmp()
{
    auto it = _tmpMaze.begin();
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "final ->" << std::endl;
    for (; it != _tmpMaze.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

bool Backtrack::stopLoop()
{
    if (_pacDest == true && (_cPos.first >= 12 && _cPos.first <= 13
        &&_cPos.second >= 9 && _cPos.second <= 11))
        return false;
    if (_cPos == _dest)
        return false;
    return true;
}

void Backtrack::reverseFinalPath()
{
    std::stack<std::pair<float, float>> tmp;

    while (!_finalPath.empty()) {
        tmp.push(_finalPath.top());
        _finalPath.pop();
    }
    while (!tmp.empty()) {
        _finalPos.push_back(tmp.top());
        tmp.pop();
    }
}

void Backtrack::convertForDisplay()
{
    std::pair<float, float> tmpReverse;

    for (size_t idx = 0; idx != _finalPos.size(); idx++) {
        tmpReverse.first = _finalPos[idx].second * 16;
        tmpReverse.second = _finalPos[idx].first * 16;
        _finalPos[idx].first = tmpReverse.first;
        _finalPos[idx].second = tmpReverse.second;
    }
}

void Backtrack::ctrBacktracking()
{
    while (stopLoop()) {
        newWay();
        recBacktracking();
    }
    reverseFinalPath();
    convertForDisplay();
}

std::vector<std::pair<float, float>> Backtrack::getPath() const
{
    return _finalPos;
}

Backtrack::~Backtrack()
{
}