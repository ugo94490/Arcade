/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** CorePacman
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <list>
#include <memory>
#include <vector>
#include "PacObject.hpp"
#include "IGame.hpp"


class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();
        std::list<std::shared_ptr<PacObject>> initGame(void);
        int handleEvents(const unsigned char &c);
        void updateGame(void) {}
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        std::shared_ptr<PacObject> createObject(float posx, float posy, char c) const;
        int move_object(std::shared_ptr<PacObject> obj, int direction);
        bool checkColision(std::pair<float, float> pos);
        void checkStar(std::pair<float, float> pos);
        std::pair<float, float> checkDoor(std::pair<float, float> pos);
        std::list<std::shared_ptr<PacObject>> filleObj();
        int checkGameOver();
        int getScore() const;
        int getBlockSize() const;
        std::pair<float, float> deblockNewPos(std::pair<float, float> pos);

        void animPacman();

        //GHOST
        void moveGhost(std::list<std::shared_ptr<PacObject>> obj);
        void setPath(int gh);
        void setGhostPos(std::list<std::shared_ptr<PacObject>> obj);
        bool ghColisionPac(int gh);
        void checkTimers();
        void setGhostAnim(int gh);
        void isGhMeetPac();
        void isNewGhostPath();
        bool inJail(int gh);
        std::pair<float, float> randMoveJail(std::shared_ptr<PacObject> obj);
        bool checkColisionJail(std::pair<float, float> pos);
        void setFirstPath();
        void PathAgain(std::pair<float, float> curPos, std::pair<float, float> dest, int gh);
        void setFirst(int gh);
        //FIN GHOST

    protected:
        std::list<std::shared_ptr<PacObject>> objects;
    private:
        int _lost = 0;
        int _score = 0;
        size_t _dir = 2;
        size_t idxAnimPac = 0;
        bool _pacgum = false;
        clock_t _timerGum = clock();
        size_t _star = 188;
        size_t _nbPacgum = 4;
        int oldDir = 0;

        //GHOST
        std::vector<bool> _canExitJail = {false, false, false, false};
        std::vector<std::vector<std::pair<float, float>>> _ghostPath;
        std::vector<std::pair<float, float>> _curPos;
        std::vector<std::string> _maze;
        std::vector<bool> _isJail = {false, false, false, false};
        bool _isScare = false;
        std::vector<clock_t> _timerJail = {clock(), clock(), clock(), clock()};
        std::pair<float, float> _pacPos;
        std::pair<float, float> _jailPos;
        bool _firstPath = true;
        clock_t _moveGhosts = clock();
        clock_t _startGame = clock();
        clock_t _movePacGh = clock();
};

extern "C" {
    IGame *maker() {
        return new Pacman();
    }
}