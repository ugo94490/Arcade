/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Backtrack
*/

#include "Backtrack.hpp"

Backtrack::Backtrack(std::pair<float, float> gPos, std::vector<std::string> maze, std::pair<float, float> dest)
{
    _gPos = gPos;
    _dest = dest;
    _stack.push(gPos);
    _finalPath.push(gPos);
    _cPos = gPos;
    _maze = maze;
    _tmpMaze = maze;
    _maze[_cPos.first][_cPos.second] = 'W';
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

//first = y; second = x

/* void Backtrack::editWay()
{
    if (_cPos.first == _dest.first && _cPos.second == _dest.second) {
        _dest.first = 13;
        _dest.second = 11;
    }
} */

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
    int nbWay = checkOtherWay(_cPos.first, _cPos.second);

    /* editWay(); */
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
    if (_finalPath.size() != 1) {
        while (_finalPath.size() > 1 && _finalPath.top() != _stack.top())
            _finalPath.pop();
    }
    if (_stack.size() != 1 && checkOtherWay(_stack.top().first, _stack.top().second) > 0)
        _stack.pop();
}

void Backtrack::cleanFinalPath()
{
    std::pair<int, int> pos;

    for (size_t i = 0; i != _finalPos.size(); i++) {
        _tmpMaze[_finalPos[i].first][_finalPos[i].second];
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
    if (_cPos.first >= 12 && _cPos.first <= 13
    &&_cPos.second >= 9 && _cPos.second <= 11)
        return false;
    return true;
}

void Backtrack::reverseFinalPath()
{
    std::stack<std::pair<float, float>> tmp;
    std::cout << "A" << std::endl;
    while (!_finalPath.empty()) {
        tmp.push(_finalPath.top());
        _finalPath.pop();
    }
    std::cout << "B" << std::endl;
    while (!tmp.empty()) {
        _finalPos.push_back(tmp.top());
        tmp.pop();
    }
    std::cout << "C" << std::endl;
    for (size_t idx = 0; idx != _finalPos.size(); idx++) {
        _finalPos[idx].first *= 32;
        _finalPos[idx].second *= 32;
    }
    std::cout << "D" << std::endl;
}

void Backtrack::ctrBacktracking()
{
    while (stopLoop()) {
        /* usleep(1000000); */
        newWay();
        recBacktracking();
        /* display(); */
    }
    std::cout << "finish1" << std::endl;
    reverseFinalPath();
/*     cleanFinalPath();
    displayTmp(); */
    std::cout << "finish2" << std::endl;
}

std::vector<std::pair<float, float>> Backtrack::getPath() const
{
    return _finalPos;
}

Backtrack::~Backtrack()
{
}

/* int main(void)
{
    std::pair<int, int> pos = std::make_pair(1, 1);
    std::pair<int, int> dest = std::make_pair(12, 11);
    std::ifstream myfile ("map.txt");
    std::vector<std::string> maze;
    std::string line;

    if (!myfile.is_open())
        throw(std::string("Could not open pacman map"));
    for (int i = 0; !myfile.eof(); i++) {
        getline (myfile, line);
        maze.push_back(line + '\n');
    }
    myfile.close();
    Backtrack p(pos, maze, dest);
    std::vector<std::vector<std::pair<float, float>>> tmpTmp;
    std::vector<std::pair<float, float>> tmp = p.getPath();

    for (size_t i = 0; i != tmp.size(); i++) {
        std::cout << tmp[i].first << " ; " << tmp[i].second << std::endl;
    }
    tmpTmp.resize(1);
    tmpTmp[0] = tmp;
    return 0;
} */