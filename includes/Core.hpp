/*
** EPITECH PROJECT, 2022
** Core
** File description:
** header
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <vector>
#include "IDisplayModule.hpp"
#include "IGamesModule.hpp"
#include <filesystem>

class Core {
public:
    void run();
    void setActualGame(std::string game);
    void runGame(std::string game, bool createmap);
    void setMenu(int change);
    bool change(int i);
    bool changeGame(std::string game);
    std::vector <ADisplayModule *> _lib;
    std::vector <AGamesModule *> _games;
    ADisplayModule *ActualLib;
    AGamesModule *ActualGame;
};

#endif /* !CORE_HPP_ */
