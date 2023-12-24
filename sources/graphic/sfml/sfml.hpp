/*
** EPITECH PROJECT, 2022
** sfml
** File description:
** header
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IDisplayModule.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class sfml : public ADisplayModule {
    public:
        sfml();
        void init() override;
        void stop() override;
        void drawRectangle(int x, int y, int sizex, int sizey, color_t color) override;
        void close() override;
        void refresh() override;
        bool isRunning() override {return _window->isOpen();};
        void displaymenu() override;
        void drawCircle(int size, int x, int y, color_t color) override;
        int chooseGame() override;
        int getAllInput() override;
        void getScore(int score_value) override;
        void defeat() override;
        void victory() override;
    private:
        sf::RenderWindow *_window;
        sf::Event _event;
        sf::Keyboard _keyboard;
        sf::Vector2i mouse_pos;
        sf::Text score;
        sf::Font font;
        std::string game_name;
};
#endif /* !SFML_HPP_ */
