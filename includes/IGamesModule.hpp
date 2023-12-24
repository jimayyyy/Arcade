/*
** EPITECH PROJECT, 2022
** Games
** File description:
** header
*/

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#define PACMAN_PATH "sources/games/pacman/pacman_map.txt"
#define NIBBLER_PATH "sources/games/nibbler/nibbler_map.txt"

#include <iostream>
#include <vector>
#include "IDisplayModule.hpp"

class IGamesModule {
public:
    virtual ~IGamesModule() = default;
    virtual void setLib(ADisplayModule *) = 0;
    virtual void createmap(std::string path) = 0;
    virtual std::vector<std::string> returnmap() = 0;
    virtual bool ismapexists() = 0;
    virtual void drawmap() = 0;
    virtual void getInput() = 0;
    virtual std::string getName() = 0;
};

class AGamesModule : public IGamesModule {
public:
    std::vector<std::string> returnmap() override {return this->map;};
    bool ismapexists() override {return this->isMap;};
    void setLib(ADisplayModule *lib) override { this->ActualLib = lib; };
protected:
    ADisplayModule *ActualLib;
    std::vector<std::string> map;
    bool isMap;
    int score_value;
    int key;
};

#endif /* !IGAMES_HPP_ */
