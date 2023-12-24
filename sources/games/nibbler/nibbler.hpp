/*
** EPITECH PROJECT, 2022
** nibbler
** File description:
** header
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "IGamesModule.hpp"
#include "IDisplayModule.hpp"

typedef struct pos_s
{
    int x;
    int y;
} pos_t;

class nibbler : public AGamesModule
{
public:
    nibbler();
    void createmap(std::string path) override;
    void drawmap() override;
    void getInput() override;
    void create_worm(std::vector<std::string> map);
    void movement(int y, int x);
    void spawnApple();
    color_t setColor(int x, int y, int z);
    std::string getName() override {return "nibbler";};
private:
    std::vector<pos_t> worm;
    int apple_rate;
};

#endif /* !NIBBLER_HPP_ */
