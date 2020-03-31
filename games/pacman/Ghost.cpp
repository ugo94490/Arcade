/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Ghost
*/

#include "Ghost.hpp"

Ghost::Ghost()
{
}

void setPath(int gh)
{
    std::pair<float, float> ghPos = _ghostPath[gh][0];
    std::pair<float, float> dest;

    if (_isJail[gh] == false) {
        dest = _pacPos;
    else
        dest = _jailPos;
    Backtrack g(ghPos, _maze, dest);
    _ghostPath[gh] = g.getPath();
}

void isNewGhostPath()
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == false)
            setPath(gh)
    }
}

void setGhostAnim(int gh)
{
    if (_curPos[gh].first < _ghostPath[gh][0].first)
        pacRects[gh+3] = downAnim[gh];
    if (_curPos[gh].first > _ghostPath[gh][0].first)
        pacRects[gh+3] = upAnim[gh];
    if (_curPos[gh].second < _ghostPath[gh][0].second)
        pacRects[gh+3] = rightAnim[gh];
    if (_curPos[gh].second > _ghostPath[gh][0].second)
        pacRects[gh+3] = leftAnim[gh];
}

void setGhostPos(std::list<std::shared_ptr<PacObject>> obj)
{
    std::shared_ptr<PacObject> tmp;
    auto it = obj.begin();

    for (size_t gh = 0; gh != 4; gh++) {
        tmp = *it;
        setGhostAnim(gh + 1);
        tmp->setPos(_ghostPath[gh][0])
        _ghostPath[gh].pop();
        ++it;
    }
}

bool ghColisionPac(int gh)
{
    if (_curPos[0].first == _pacPos.first
    && _curPos[0].second == _pacPos.second)
        return true;
    return false;
}

void isGhMeetPac()
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == true)
            continue;
        if (_pacgum == false && ghColisionPac(gh)) {
            _lost = true;
            return;
        }
        else if (_pacgum == true && ghColisionPac(gh)) {
            _isJail[gh] = true;
            setPath(gh);
        }
    }
}

/* void jailPath()
{

} */

void jailGhost(int gh)
{
    for (size_t gh = 0; gh != 4; gh++) {
        if (_isJail[gh] == true) {
            return;
        }
    }
}

void checkTimers()
{
    if (_timerPath >=3)
        _timerPath = 0;
    for (size_t i = 0; i != 4; i++) {
        if (_timerJail[gh] >= 10) {
            _timerJail[gh] = 0;
            _isJail[gh] = false;
            setPath(gh);
        }
    }
}

void moveGhost(std::list<std::shared_ptr<PacObject>> obj)
{
    if (_timerPath >= 3)
        isNewGhostPath();   //get Path
    setGhostPos(obj);       //set Path
    isGhMeetPac();        //checkJail
    jailGhost();            //behavior in jail
    checkTimers();          //restar clock
}

Ghost::~Ghost()
{
}

