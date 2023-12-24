/*
** EPITECH PROJECT, 2022
** sdl2
** File description:
** function
*/

#include "sdl2.hpp"

extern "C" IDisplayModule *createGraphLib()
{
    return (new sdl2());
}

sdl2::sdl2()
{
    this->name = "Lib SDL2";
    this->menu = true;
    this->key_value = 0;
    std::cout << "loading sdl2 library\n";
}

int sdl2::chooseGame()
{
    int x, y;
    Uint32 buttons;
    buttons = SDL_GetMouseState(&x, &y);

    if ((buttons & SDL_BUTTON_LMASK) != 0) {
        if (x > 78 && x < 256 && y > 386 && y < 437) {
            menu = false;
            return games::PACMAN;
        }
        if (x > 78 && x < 256 && y > 457 && y < 506) {
            menu = false;
            return games::NIBBLER;
        }
        if (x > 602 && x < 728 && y > 462 && y < 525) {
            this->close();
        }
    }
    return 0;
}

void sdl2::init()
{
    isOpen = true;
    this->window = (SDL_CreateWindow(this->name.c_str(),
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     800, 600, 0));
    this->renderer = (SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED));
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    this->c_menu = 0;
    this->c_defeat = 0;
    this->c_victory = 0;
    TTF_Init();
    this->font = TTF_OpenFont("images/Minecraft.ttf", 20);
    if (!this->window)
    {
        std::cout << "Failed to create window\n";
        return;
    }
    return;
}

void sdl2::stop()
{
    return;
}

bool sdl2::isRunning()
{
    return isOpen;
}

void sdl2::close()
{
    isOpen = false;
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

void sdl2::refresh()
{
    SDL_RenderClear(this->renderer);
}

void sdl2::drawRectangle(int x, int y, int sizex, int sizey, color_t color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = sizex;
    rect.h = sizey;
    SDL_SetRenderDrawColor(this->renderer, color.x, color.y, color.z, 255);
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

void sdl2::drawCircle(int size, int x, int y, color_t color)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = size;
    rect.h = size;

    SDL_SetRenderDrawColor(this->renderer, color.x, color.y, color.z, 255);
    SDL_RenderFillRect(this->renderer, &rect);
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

void sdl2::createMenu()
{
    IMG_Init(IMG_INIT_PNG);
    this->image = IMG_Load("images/menu_sdl.png");
    this->texture = SDL_CreateTextureFromSurface(renderer, this->image);
    this->c_menu = 500;
}

void sdl2::displaymenu()
{
    if (c_menu != 500) {
        createMenu();
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
};

int sdl2::getAllInput()
{
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
        {
            isOpen = false;
            this->close();
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
        {
            key_value = inputs::SWITCH_LIB_RIGHT;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
        {
            key_value = inputs::SWITCH_LIB_LEFT;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_z && this->menu == false)
        {
            key_value = inputs::MOVE_UP;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q && this->menu == false)
        {
            key_value = inputs::MOVE_LEFT;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s && this->menu == false)
        {
            key_value = inputs::MOVE_DOWN;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d && this->menu == false)
        {
            key_value = inputs::MOVE_RIGHT;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l && this->menu == false)
        {
            key_value = inputs::SWITCH_GAME;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r && this->menu == false)
        {
            key_value = inputs::RESET_GAME;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m && this->menu == false) {
            this->menu = true;
            key_value = inputs::RETURN_MENU;
        }
    }
    return key_value;
}

void sdl2::getScore(int score_value)
{
    SDL_Color Yellow = {250, 253, 15};
    SDL_Surface* SMessage = 
            TTF_RenderText_Solid(this->font, ("score :" + std::to_string(score_value)).c_str(), Yellow);
    SDL_Texture* Message =  SDL_CreateTextureFromSurface(this->renderer, SMessage);
    SDL_Rect Message_rect = {0, 0, 100, 100};
    SDL_RenderCopy(this->renderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(this->renderer);
}

void sdl2::createLoose()
{
    IMG_Init(IMG_INIT_PNG);
    this->image_loose = IMG_Load("images/loose.png");
    this->texture_loose = SDL_CreateTextureFromSurface(renderer, this->image_loose);
    this->c_defeat = 500;
}

void sdl2::defeat()
{
    if (c_defeat != 500) {
        createLoose();
    }
    SDL_RenderCopy(renderer, texture_loose, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void sdl2::createWin()
{
    IMG_Init(IMG_INIT_PNG);
    this->image_win = IMG_Load("images/win.png");
    this->texture_win = SDL_CreateTextureFromSurface(renderer, this->image_win);
    this->c_victory = 500;
}

void sdl2::victory()
{
    if (c_victory != 500) {
        createWin();
    }
    SDL_RenderCopy(renderer, texture_win, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}