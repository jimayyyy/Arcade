/*
** EPITECH PROJECT, 2022
** sdl2
** File description:
** header
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_
#include "IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class sdl2 : public ADisplayModule {
    public:
        sdl2();
        void init() override;
        void stop() override;
        void drawRectangle(int x, int y, int sizex, int sizey, color_t color) override;
        bool isRunning() override;
        void refresh() override;
        void close() override;
        void displaymenu() override;
        void drawCircle(int size, int x, int y, color_t color) override;
        int chooseGame() override;
        int getAllInput() override;
        void createMenu();
        void createLoose();
        void getScore(int score_value) override;
        void defeat() override;
        void victory() override;
        void createWin();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::string game_name;
        SDL_Event event;
        TTF_Font* font;
        SDL_Surface *image;
        SDL_Texture *texture;
        SDL_Surface *image_loose;
        SDL_Texture *texture_loose;
        SDL_Surface *image_win;
        SDL_Texture *texture_win;
        int c_menu;
        int c_defeat;
        int c_victory;
        bool isOpen;
};

#endif /* !SDL2_HPP_ */