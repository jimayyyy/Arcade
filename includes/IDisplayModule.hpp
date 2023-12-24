/*
** EPITECH PROJECT, 2022
** Display
** File description:
** Interface
*/

#pragma once

#include <iostream>

typedef struct color_s {
    int x;
    int y;
    int z;
}color_t;

enum games {
    NONE,
    PACMAN,
    NIBBLER
};

enum inputs {
    RESET_INPUT,
    SWITCH_LIB_RIGHT,
    SWITCH_LIB_LEFT,
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_DOWN,
    RETURN_MENU,
    SWITCH_GAME,
    RESET_GAME,
    ENTER
};

class IDisplayModule {
public:
    virtual ~IDisplayModule() = default;
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual const std::string &getName() const = 0;
    virtual void close() = 0;
    virtual bool isRunning() = 0;
    virtual void drawRectangle(int x, int y, int sizex, int sizey, color_t color) = 0;
    virtual void drawCircle(int size, int x, int y, color_t color) = 0;
    virtual void refresh() = 0;
    virtual std::string game() = 0;
    virtual void displaymenu() = 0;
    virtual bool ismenudisplayable() = 0;
    virtual int chooseGame() = 0;
    virtual void setGame(std::string game) = 0;
    virtual void setMenu(int change) = 0;
    virtual int getAllInput() = 0;
    virtual void setInput(int key) = 0;
    virtual void getScore(int score_value) = 0;
    virtual void defeat() = 0;
    virtual void victory() = 0;
    virtual bool getLoose() = 0;
    virtual void setLoose(bool status) = 0;
    virtual bool getWin() = 0;
    virtual void setWin(bool status) = 0;
};

class ADisplayModule : public IDisplayModule {
public:
    const std::string &getName() const override {return name;};
    bool ismenudisplayable() override {return this->menu;};
    void setGame(std::string game) override {this->game_chosed = game;};
    void setMenu(int change) override {this->menu = change;}
    std::string game() override {return this->game_chosed;};
    void setInput(int key) override {this->key_value = key;};
    bool getLoose() override {return this->lose;};
    void setLoose(bool status) override {this->lose = status;};
    bool getWin() override {return this->win;};
    void setWin(bool status) override {this->win = status;};
protected:
    bool menu;
    int key_value;
    std::string game_chosed;
    std::string name;
    bool lose;
    bool win;
};