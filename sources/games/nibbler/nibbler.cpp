/*
** EPITECH PROJECT, 2022
** Nibbler
** File description:
** game
*/

#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "nibbler.hpp"

extern "C" AGamesModule *createGameLib()
{
    return (new nibbler());
}

nibbler::nibbler()
{
    std::cout << "loading nibbler game\n";
    return;
}

void nibbler::create_worm(std::vector<std::string> map)
{
    pos_t position;

    worm.clear();
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].length(); j++)
        {
            if (map[i][j] == 'o')
            {
                position.y = i,
                position.x = j;
                worm.insert(worm.begin(), position);
            }
        }
    }
    for (int i = 0; i != map.size(); i++)
    {
        for (int j = 0; j != map[i].length(); j++)
        {
            if (map[i][j] == '<' || map[i][j] == '^' || map[i][j] == '>' || map[i][j] == 'v')
            {
                position.y = i,
                position.x = j;
                worm.insert(worm.begin(), position);
            }
        }
    }
}

color_t nibbler::setColor(int x, int y, int z)
{
    color_t color;

    color.x = x;
    color.y = y;
    color.z = z;
    return color;
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

void nibbler::createmap(std::string path)
{
    std::ifstream file(path);
    std::string line;
    apple_rate = 0;
    score_value = 0;
    if (!file.is_open())
        return;
    if (map.size() >= nbLines(path))
        map.clear();
    while (getline(file, line))
    {
        map.push_back(line);
    }
    this->isMap = true;
    create_worm(map);
    file.close();
}

void nibbler::drawmap()
{
    apple_rate += 1;
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
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(255, 0, 0));
            }
            if (map[i][j] == 'o')
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(0, 0, 255));
            }
            if (map[i][j] == '<' || map[i][j] == '>' || map[i][j] == '^' || map[i][j] == 'v')
            {
                this->ActualLib->drawRectangle((j * 19), (i * 37), 19, 37, setColor(85, 85, 85));
            }
        }
    }
    for (int i = 0; i != map.size(); i++) {
        for (int j = 0; j != map[i].size(); j++) {
            if (map[i][j] == 'x' && this->ActualLib->getName().compare("Lib ncurses") != 0) {
                this->ActualLib->drawCircle(19, ((j * 19)-10), (i * 37), setColor(0, 255, 0));
            } else if (map[i][j] == 'x' && this->ActualLib->getName().compare("Lib ncurses") == 0)
                this->ActualLib->drawCircle(19, j, i, setColor(0, 255, 0));
        }
    }
    this->ActualLib->getScore(score_value);
    if (apple_rate == 10) {
        spawnApple();
        apple_rate = 0;
    }
}

void nibbler::getInput()
{
    usleep(100000);
    if (this->ActualLib->getAllInput() == inputs::MOVE_UP) // haut
        movement(-1, 0);
    if (this->ActualLib->getAllInput() == inputs::MOVE_LEFT) // left
        movement(0, -1);
    if (this->ActualLib->getAllInput() == inputs::MOVE_DOWN) // bas
        movement(1, 0);
    if (this->ActualLib->getAllInput() == inputs::MOVE_RIGHT) // droite
        movement(0, 1);
    if (this->ActualLib->getAllInput() == inputs::RESET_GAME) {
        this->map.clear();
        this->createmap(NIBBLER_PATH);
    }
    return;
}

void nibbler::spawnApple()
{
    int rand_y = rand() % map.size();
    int rand_x = rand() % map[rand_y].size();

    if (map[rand_y][rand_x] == ' ')
        map[rand_y][rand_x] = 'x';
}

void nibbler::movement(int y, int x)
{
    pos_t temp;
    pos_t temp2;
    bool grow = false;

    if (map[worm[0].y + y][worm[0].x + x] != '#' && map[worm[0].y + y][worm[0].x + x] != 'o')
    {
        if (map[worm[0].y + y][worm[0].x + x] == 'x') {
            grow = true;
            score_value += 1;
        }
        temp = worm[0];
        worm[0].y += y;
        worm[0].x += x;
        map[worm[0].y][worm[0].x] = 'v';
        for (int i = 1; i != worm.size(); i++)
        {
            if (grow == true)
            {
                worm.push_back(temp);
                grow = false;
            }
            map[worm[i].y][worm[i].x] = ' ';
            temp2 = worm[i];
            worm[i] = temp;
            temp = temp2;
        }
        for (int i = 1; i != worm.size(); i++)
        {
            map[worm[i].y][worm[i].x] = 'o';
        }
    } else  {
        //lose;
        this->ActualLib->setLoose(true);
        this->map.clear();
        this->createmap(NIBBLER_PATH);
    }
    //std::cout << "worm size: " << worm.size() << std::endl;
}