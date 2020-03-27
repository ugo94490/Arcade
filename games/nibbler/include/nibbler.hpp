/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#pragma once

#include <iostream>
#include <list>
#include <memory>
#include "NibObject.hpp"
#include "IGame.hpp"

class Nibbler : public IGame {
    public:
        Nibbler();
        ~Nibbler();
        std::list<std::shared_ptr<NibObject>> initGame(void) const;
        void handleEvents(const unsigned char &c);
        void updateGame(void);
        Rect getAppearanceRectIdx(int idx);
        char getAppearanceCharIdx(int idx);
        std::list<std::shared_ptr<IGameObject>> getObjects(void) const;
        std::shared_ptr<NibObject> createObject(float posx, float posy, char c) const;
        std::shared_ptr<NibObject> check_free(std::pair<float, float> pos) const;
        int move_object(std::shared_ptr<NibObject> obj, int direction);
        void SetRandItems(void);
        std::list<std::shared_ptr<NibObject>> generatePlayer(std::list<std::shared_ptr<NibObject>> obj) const;
        std::list<std::shared_ptr<NibObject>> new_body(std::shared_ptr<NibObject> old_ptr, std::list<std::shared_ptr<NibObject>> obj, int count) const;
        std::vector<std::pair<float, float>> fill_pair(std::shared_ptr<NibObject> old_ptr) const;
        std::vector<std::pair<float, float>> check_dispo(std::vector<std::pair<float, float>> pos, std::list<std::shared_ptr<NibObject>> obj) const;
        int move_snake(std::shared_ptr<NibObject> obj, std::pair<float, float> pos) const;
        int moveAdd_snake(std::shared_ptr<NibObject> obj, std::pair<float, float> pos);
    protected:
        std::list<std::shared_ptr<NibObject>> objects;
    private:
        int nb_fruit;
};

extern "C" {
    IGame *maker() {
        return new Nibbler();
    }
}
