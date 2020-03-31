/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Backtrack
*/

#ifndef BACKTRACK_HPP_
#define BACKTRACK_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <stack>
#include <unistd.h>

class Backtrack {
    public:
        Backtrack(std::pair<float, float> gPos, std::vector<std::string> maze, std::pair<float, float> dest, bool pacDest);
        void createMaze();
        void recBacktracking();
        void ctrBacktracking();
        void checkDirection();
        void display();
        int checkPosX();
        int checkPosY();
        bool checkMazePos(size_t x, size_t y);
        int checkOtherWay(int y, int x);
        void assignPath(int x, int y);
        void newWay();
        void cleanFinalPath();
        void displayTmp();
        void editWay();
        bool stopLoop();
        void deblock();
        void reverseFinalPath();
        std::vector<std::pair<float, float>> getPath() const;
        void convertForDisplay();
        ~Backtrack();

    private:
        std::stack<std::pair<float, float>> _finalPosTmp;
        std::vector<std::pair<float, float>> _finalPos;
        std::stack<std::pair<int, int>> _finalPath;
        std::pair<int, int> _gPos;
        std::pair<int, int> _dest;
        std::pair<int, int> _cPos;
        std::stack<std::pair<int, int>> _stack;
        std::vector<std::string> _maze;
        std::vector<std::string> _tmpMaze;
        int _sizeX = 21;
        int _sizeY = 26;

        bool _pacDest;
};

#endif /* !BACKTRACK_HPP_ */
