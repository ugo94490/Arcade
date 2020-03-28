/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Ghost
*/

#ifndef GHOST_HPP_
#define GHOST_HPP_

class Ghost {
    public:
        Ghost();
        void moveGhost(std::list<std::shared_ptr<PacObject>> obj);
        void setPath();
        void setGhostPos(std::list<std::shared_ptr<PacObject>> obj);
        void checkColisionGhostPac();
        void jailGhost();
        void checkTimers();
        void setGhostAnim();
        void isGhMeetPac();

        ~Ghost();

    protected:
    private:
        std::pair<float, float> _curPos;
        std::vector<string> _maze;
        clock_t _timerPath;
        std::vector<bool> _isJail;
        std::vector<std::vector<std::pair<float, float>>> _ghostPath;
        std::vector<clock_t> _timerJail;
        std::pair<float, float> _pacPos;
        std::pair<float, float> _jailPos;


};

#endif /* !GHOST_HPP_ */
