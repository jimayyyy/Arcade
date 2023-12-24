/*
** EPITECH PROJECT, 2022
** pacman
** File description:
** games
*/

#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "pacman.hpp"

extern "C" AGamesModule *createGameLib()
{
    return (new pacman());
}

pacman::pacman()
{
    std::cout << "Loading pacman game" << std::endl;
    return;
}

void pacman::createEnemy(std::vector<std::string> map)
{
    enemy_t temp_enemy;
    enemy.clear();
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].length(); j++)
        {
            if (map[i][j] == 'C' || map[i][j] == 'R' || map[i][j] == 'P' || map[i][j] == 'O')
            {
                temp_enemy.pos.y = i,
                temp_enemy.pos.x = j;
                temp_enemy.name = map[i][j];
                enemy.push_back(temp_enemy);
            }
        }
    }
}

void pacman::moveEnemy()
{
    for (int i = 0; i != enemy.size(); i++)
    {
        int value = rand() % 4;
        usleep(10000);
        if (value == 0)
            enemy_movement(enemy[i], -1, 0);
        if (value == 1)
            enemy_movement(enemy[i], 0, -1);
        if (value == 2)
            enemy_movement(enemy[i], 1, 0);
        if (value == 3)
            enemy_movement(enemy[i], 0, 1);
    }
    return;
}

void pacman::enemy_movement(enemy_t enemy, int y, int x)
{
    pos_t position;
    if (map[enemy.pos.y + y][enemy.pos.x + x] == ' ')
    {
        map[enemy.pos.y + y][enemy.pos.x + x] = enemy.name;
        map[enemy.pos.y][enemy.pos.x] = ' ';
    }
    if (map[enemy.pos.y + y][enemy.pos.x + x] == '.')
    {
        map[enemy.pos.y + y][enemy.pos.x + x] = enemy.name;
        map[enemy.pos.y][enemy.pos.x] = '.';
    }
    if (map[enemy.pos.y + y][enemy.pos.x + x] == 'M')
    {
        // lose
    }
}

int nbLines(std::string path)
{
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(path);

    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}

void pacman::createmap(std::string path)
{
    std::ifstream file(path);
    std::string line;
    score_value = 0;
    berserk = false;
    C_alive = true;
    P_alive = true;
    O_alive = true;
    R_alive = true;
    berserk_time = 0;
    C_respawn = 0;
    P_respawn = 0;
    O_respawn = 0;
    R_respawn = 0;
    if (!file.is_open())
        return;
    if (map.size() >= nbLines(path))
        map.clear();
    while (getline(file, line))
    {
        map.push_back(line);
    }
    this->isMap = true;
    countScore(map);
    file.close();
}

void pacman::createPac(std::vector<std::string> map)
{
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].length(); j++)
        {
            if (map[i][j] == 'M')
            {
                pac_pos.y = i,
                pac_pos.x = j;
            }
        }
    }
}

void pacman::countScore(std::vector<std::string> map)
{
        for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].length(); j++)
        {
            if (map[i][j] == '.')
            {
                win_condition += 1;
            }
        }
    }
}

void pacman::manageRespawn()
{
    if (C_alive == false)
        C_respawn += 1;
    if (P_alive == false)
        P_respawn += 1;
    if (O_alive == false)
        O_respawn += 1;
    if (R_alive == false)
        R_respawn += 1;
    if (C_respawn == 50)
    {
        C_alive = true;
        C_respawn = 0;
        map[C_death.y][C_death.x] = 'C';
    }
    if (P_respawn == 50)
    {
        P_alive = true;
        P_respawn = 0;
        map[P_death.y][P_death.x] = 'P';
    }
    if (O_respawn == 50)
    {
        O_alive = true;
        O_respawn = 0;
        map[O_death.y][O_death.x] = 'O';
    }
    if (R_respawn == 50)
    {
        R_alive = true;
        R_respawn = 0;
        map[R_death.y][R_death.x] = 'R';
    }
}

void pacman::manageBerserk()
{
    if (berserk == true)
        berserk_time += 1;
    if (berserk_time == 100)
    {
        berserk = false;
        berserk_time = 0;
    }
}

void pacman::drawmap()
{
    manageRespawn();
    manageBerserk();
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].size(); j++)
        {
            if (map[i][j] == ' ')
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(0, 0, 0));
            }
            if (map[i][j] == '#')
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(0, 0, 255));
            }
            if (map[i][j] == 'C' && C_alive == true)
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(0, 255, 255));
            }
            if (map[i][j] == 'P' && P_alive == true)
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(255, 192, 203));
            }
            if (map[i][j] == 'O' && O_alive == true)
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(255, 127, 0));
            }
            if (map[i][j] == 'R' && R_alive == true)
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(255, 0, 0));
            }
            if (map[i][j] == 'x' && this->ActualLib->getName().compare("Lib ncurses") != 0)
            {
                this->ActualLib->drawCircle(5, ((j * 19) + 3), ((i * 37) + 6), setColor(255, 0, 0));
            }
            else if (map[i][j] == 'x' && this->ActualLib->getName().compare("Lib ncurses") == 0)
                this->ActualLib->drawCircle(5, j, i, setColor(255, 0, 0));
            if (map[i][j] == '.' && this->ActualLib->getName().compare("Lib ncurses") != 0)
            {
                this->ActualLib->drawCircle(5, ((j * 19) + 3), ((i * 37) + 6), setColor(255, 255, 255));
            }
            else if (map[i][j] == '.' && this->ActualLib->getName().compare("Lib ncurses") == 0)
                this->ActualLib->drawCircle(5, j, i, setColor(255, 255, 255));
        }
    }
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].size(); j++)
        {
            if (berserk == false)
            {
                if (map[i][j] == 'M' && this->ActualLib->getName().compare("Lib ncurses") != 0)
                {
                    this->ActualLib->drawCircle(19, (j * 19), (i * 37), setColor(255, 255, 0));
                }
                else if (map[i][j] == 'M' && this->ActualLib->getName().compare("Lib ncurses") == 0)
                    this->ActualLib->drawCircle(19, j, i, setColor(255, 255, 0));
            }
            else
            {
                if (map[i][j] == 'M' && this->ActualLib->getName().compare("Lib ncurses") != 0)
                {
                    this->ActualLib->drawCircle(19, (j * 19), (i * 37), setColor(255, 0, 0));
                }
                else if (map[i][j] == 'M' && this->ActualLib->getName().compare("Lib ncurses") == 0)
                    this->ActualLib->drawCircle(19, j, i, setColor(255, 0, 0));
            }
        }
    }
    this->ActualLib->getScore(score_value);
    createPac(map);
    createEnemy(map);
    moveEnemy();
}

color_t pacman::setColor(int x, int y, int z)
{
    color_t color;

    color.x = x;
    color.y = y;
    color.z = z;
    return color;
}

void pacman::getInput()
{
    usleep(100000);
    if (this->ActualLib->getAllInput() == inputs::MOVE_UP)
        if (berserk == false)
            movement(-1, 0);
        else
            movement_berserk(-1, 0);
    if (this->ActualLib->getAllInput() == inputs::MOVE_LEFT)
        if (berserk == false)
            movement(0, -1);
        else
            movement_berserk(0, -1);
    if (this->ActualLib->getAllInput() == inputs::MOVE_DOWN)
        if (berserk == false)
            movement(1, 0);
        else
            movement_berserk(1, 0);
    if (this->ActualLib->getAllInput() == inputs::MOVE_RIGHT)
        if (berserk == false)
            movement(0, 1);
        else
            movement_berserk(0, 1);
    if (this->ActualLib->getAllInput() == inputs::RESET_GAME)
    {
        this->map.clear();
        this->createmap(PACMAN_PATH);
    }
    return;
}

void pacman::movement(int y, int x)
{
    if (map[pac_pos.y + y][pac_pos.x + x] == '#')
        return;
    if (map[pac_pos.y + y][pac_pos.x + x] != 'C' && map[pac_pos.y + y][pac_pos.x + x] != 'R' && map[pac_pos.y + y][pac_pos.x + x] != 'P' && map[pac_pos.y + y][pac_pos.x + x] != 'O')
    {
        if (map[pac_pos.y + y][pac_pos.x + x] == 'x')
            berserk = true;
        if (map[pac_pos.y + y][pac_pos.x + x] == '.')
            score_value += 1;
        map[pac_pos.y + y][pac_pos.x + x] = 'M';
        map[pac_pos.y][pac_pos.x] = ' ';
        if (score_value == win_condition) {
            this->ActualLib->setWin(true);
            this->ActualLib->setInput(inputs::RESET_GAME);
            this->getInput();
            this->map.clear();
            score_value = 0;
            this->createmap(PACMAN_PATH);
        }
    }
    else
    {
        // lose
        this->ActualLib->setLoose(true);
        this->ActualLib->setInput(inputs::RESET_GAME);
        this->getInput();
        this->map.clear();
        this->createmap(PACMAN_PATH);
    }
}

void pacman::movement_berserk(int y, int x)
{
    if (map[pac_pos.y + y][pac_pos.x + x] != '#')
    {
        if (map[pac_pos.y + y][pac_pos.x + x] == '.')
            score_value += 1;
        if (map[pac_pos.y + y][pac_pos.x + x] == 'x')
            berserk = true;
        if (map[pac_pos.y + y][pac_pos.x + x] == 'C') {
            C_alive = false;
            C_death.y = pac_pos.y;
            C_death.x = pac_pos.x;
        }
        if (map[pac_pos.y + y][pac_pos.x + x] == 'P') {
            P_alive = false;
            P_death.y = pac_pos.y;
            P_death.x = pac_pos.x;
        }
        if (map[pac_pos.y + y][pac_pos.x + x] == 'O') {
            O_alive = false;
            O_death.y = pac_pos.y;
            O_death.x = pac_pos.x;
        }
        if (map[pac_pos.y + y][pac_pos.x + x] == 'R') {
            R_alive = false;
            R_death.y = pac_pos.y;
            R_death.x = pac_pos.x;
        }
        map[pac_pos.y + y][pac_pos.x + x] = 'M';
        map[pac_pos.y][pac_pos.x] = ' ';
        if (score_value == win_condition) {
            this->ActualLib->setWin(true);
            this->ActualLib->setInput(inputs::RESET_GAME);
            this->getInput();
            this->map.clear();
            score_value = 0;
            this->createmap(PACMAN_PATH);
        }
    }
}