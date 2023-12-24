/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-jimy.xu
** File description:
** pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGamesModule.hpp"
#include "IDisplayModule.hpp"
#include <vector>

typedef struct pos_s
{
    int x;
    int y;
} pos_t;

typedef struct enemy_s
{
    char name;
    pos_t pos;
} enemy_t;

class pacman : public AGamesModule
{
public:
    pacman();
    void drawmap() override;
    void getInput() override;
    void movement(int y, int x);
    void enemy_movement(enemy_t enemy, int y, int x);
    void moveEnemy();
    void createPac(std::vector<std::string> map);
    void createmap(std::string path) override;
    std::string getName() override {return "pacman";};
    void createEnemy(std::vector<std::string> map);
    color_t setColor(int x, int y, int z);
    void movement_berserk(int y, int x);
    void manageRespawn();
    void manageBerserk();
    void countScore(std::vector<std::string> map);
private:
    pos_t pac_pos;
    std::vector<enemy_t> enemy;
    bool berserk;
    bool C_alive;
    bool P_alive;
    bool O_alive;
    bool R_alive;
    int berserk_time;
    int C_respawn;
    int P_respawn;
    int O_respawn;
    int R_respawn;
    pos_t C_death;
    pos_t P_death;
    pos_t O_death;
    pos_t R_death;
    int win_condition;
};

#endif /* !PACMAN_HPP_ */
