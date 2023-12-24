/*
** EPITECH PROJECT, 2022
** ncurses
** File description:
** header
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IDisplayModule.hpp"
#include <ncurses.h>
#include <vector>

class ncurses : public ADisplayModule {
    public:
        ncurses();
        void init() override;
        void stop() override;
        void drawRectangle(int x, int y, int sizex, int sizey, color_t color) override;
        bool isRunning() override {return _isRunning;};
        void close() override;
        void refresh();
        void displaymenu() override;
        void drawCircle(int size, int x, int y, color_t color) override;
        int chooseGame() override;
        int getAllInput() override;
        void getScore(int score_value) override;
        void defeat() override;
        void victory() override;
    private:
        WINDOW *score;
        WINDOW *field;
        int ch;
        bool _isRunning;
        int parent_x;
        int parent_y;
        int new_x;
        int new_y;
        int score_size;
        int cursor;
        std::string print_score;
};

#endif /* !NCURSES_HPP_ */