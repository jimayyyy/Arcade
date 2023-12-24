/*
** EPITECH PROJECT, 2022
** Core
** File description:
** functions
*/

#include "Core.hpp"
#include "DLLoader.hpp"
#include "IGamesModule.hpp"
#include "IDisplayModule.hpp"
#include <unistd.h>

void Core::setActualGame(std::string game)
{
    for (int i = 0; i != this->_games.size(); i++) {
        if (this->_games[i]->getName().compare(game) == 0) {
            this->ActualGame = this->_games[i];
            ActualGame->setLib(this->ActualLib);
            return;
        } 
    }
}

void Core::runGame(std::string game, bool createmap)
{
    this->ActualLib->setGame(game);
    this->ActualLib->drawRectangle(0, 0, 1000, 1000, {0, 0, 0});

    if (this->ActualLib->game().compare("nibbler") == 0) {
        setActualGame("nibbler");
        if (createmap == true && this->ActualGame->ismapexists() != true) {
            this->ActualGame->createmap(NIBBLER_PATH);
            createmap = false;
        }
    } else if (this->ActualLib->game().compare("pacman") == 0) {
        setActualGame("pacman");
        if (createmap == true && this->ActualGame->ismapexists() != true) {
            this->ActualGame->createmap(PACMAN_PATH);
            createmap = false;
        }
    }
    ActualGame->getInput();
    ActualGame->drawmap();
    ActualGame->returnmap().clear();
}

void Core::setMenu(int change)
{
    for (int i = 0; i != this->_lib.size(); i++) {
        this->_lib[i]->setMenu(change);
    }
}

bool Core::change(int i)
{
    if (this->ActualLib->getAllInput() == inputs::SWITCH_LIB_RIGHT) {
        this->ActualLib->close();
        if (i == (this->_lib.size()-1)) {
            this->ActualLib = this->_lib[0];
        } else {
            this->ActualLib = this->_lib[i+1];
        }
        if (this->ActualLib->ismenudisplayable() == false) {
            this->ActualGame->setLib(this->ActualLib);
        }
        for (int j = 0; j != this->_lib.size(); j++) {
            this->_lib[i]->setInput(inputs::RESET_INPUT);
        }
        usleep(10000);
        return true;
    }
    if (this->ActualLib->getAllInput() == inputs::SWITCH_LIB_LEFT) {
        this->ActualLib->close();
        if (i == 0) {
            this->ActualLib = this->_lib[(this->_lib.size()-1)];
        } else {
            this->ActualLib = this->_lib[(i - 1)];
        }
        if (this->ActualLib->ismenudisplayable() == false) {
            this->ActualGame->setLib(this->ActualLib);
        }
        for (int j = 0; j != this->_lib.size(); j++) {
            this->_lib[i]->setInput(inputs::RESET_INPUT);
        }
        usleep(10000);
        return true;
    }
    return false;
}

bool Core::changeGame(std::string game)
{
    if(this->ActualLib->getAllInput() == inputs::SWITCH_GAME) {
        this->ActualLib->setInput(inputs::RESET_INPUT);
        return true;
    }
    return false;
}

void Core::run()
{
    std::string game;
    std::string oldGame;
    bool createmap = true;

    for (int i = 0; i != this->_lib.size(); i++) {
        if (this->_lib[i] == this->ActualLib) {
            this->_lib[i]->init();
            while (this->ActualLib->isRunning()) { // tant que la window est ouverte
                this->ActualLib->refresh();
                if (this->ActualLib->ismenudisplayable()) {
                    if (this->ActualLib->chooseGame() == games::PACMAN) {
                        game = "pacman";
                        this->ActualLib->setGame(game);
                    }
                    if (this->ActualLib->chooseGame() == games::NIBBLER) {
                        game = "nibbler";
                        this->ActualLib->setGame(game);
                    }
                    this->ActualLib->displaymenu();
                    this->ActualLib->refresh();
                    if (this->change(i)) {
                        i = (-1);
                        break;
                    }
                }
                if (this->ActualLib->ismenudisplayable() == false) {
                    this->setMenu(this->ActualLib->ismenudisplayable());
                    if (this->change(i)) {
                        i = (-1);
                        break;
                    }
                    if (changeGame(game) == true) {
                        if (game.compare("nibbler") == 0) {
                            game = "pacman";
                        } else if (game.compare("pacman") == 0) {
                            game = "nibbler";
                        }
                        createmap = true;
                    }
                    if (this->ActualLib->getWin() != true && this->ActualLib->getLoose() != true) { 
                        runGame(game, createmap);
                    }
                    createmap = false;
                    if (this->ActualLib->getLoose()) {
                        this->ActualLib->defeat();
                        this->ActualLib->refresh();
                    }
                    if (this->ActualLib->getWin()) {
                        this->ActualLib->victory();
                        this->ActualLib->refresh();
                    }
                    if (this->ActualLib->getAllInput() == inputs::RETURN_MENU) {
                        if (this->ActualLib->getLoose() == true) {
                            this->ActualLib->setLoose(false);
                        }
                        if (this->ActualLib->getWin() == true) {
                            this->ActualLib->setWin(false);
                        }
                        this->ActualGame->returnmap().clear();
                        this->ActualLib->setInput(inputs::RESET_INPUT);
                        this->setMenu(true);
                        createmap = true;
                    }
                }
                this->ActualLib->stop();
            }
        }
    }
}