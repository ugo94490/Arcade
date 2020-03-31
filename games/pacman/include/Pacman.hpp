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
        void handleEvents(const unsigned char &c);
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
        bool gameOver();
        bool isPriority(std::shared_ptr<PacObject> tmpObj);
        void animPacman();

        //GHOST
        void moveGhost(std::list<std::shared_ptr<PacObject>> obj);
        void setPath(int gh);
        void setGhostPos(std::list<std::shared_ptr<PacObject>> obj);
        bool ghColisionPac(int gh);
        void jailGhost();
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
        bool _lost = false;
        size_t _dir = 2;
        size_t idxAnimPac = 0;
        bool _pacgum = false;
        clock_t _timerGum = 0;
        size_t _star = 188;
        size_t _nbPacgum = 4;

        //GHOST
        std::vector<std::vector<std::pair<float, float>>> _ghostPath;
        std::vector<std::pair<float, float>> _curPos;
        std::vector<std::string> _maze;
        size_t _timerPath = 0;
        std::vector<bool> _isJail = {false, false, false, false};
        std::vector<clock_t> _timerJail = {0, 0, 0, 0};
        std::pair<float, float> _pacPos;
        std::pair<float, float> _jailPos;
};

extern "C" {
    IGame *maker() {
        return new Pacman();
    }
}