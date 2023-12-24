/*
** EPITECH PROJECT, 2022
** sfml
** File description:
** function
*/

#include "sfml.hpp"

extern "C" IDisplayModule* createGraphLib()
{
    return (new sfml());
}

sfml::sfml()
{
    this->name = "Lib Smlf";
    std::cout << "Loading sfml library\n";
    this->menu = true;
}

int sfml::chooseGame()
{
    this->mouse_pos = sf::Mouse::getPosition(*_window);
    if (mouse_pos.x > 78 && mouse_pos.x < 256 && mouse_pos.y > 386 && mouse_pos.y < 437) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            menu = false;
            return games::PACMAN;
        }
    }
    if (mouse_pos.x > 78 && mouse_pos.x < 262 && mouse_pos.y> 457 && mouse_pos.y < 506) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            menu = false;
            return games::NIBBLER;
        }
    }
    return 0;
}

void sfml::init()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(800, 600), this->name.c_str());
    this->_window->setFramerateLimit(60);
    this->font.loadFromFile("./images/Minecraft.ttf");
    this->score.setFont(this->font);
}

void sfml::stop()
{
    this->mouse_pos = sf::Mouse::getPosition(*_window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->ismenudisplayable() == true
        && mouse_pos.x >= 602 && mouse_pos.x <= 728
        && mouse_pos.y >= 462 && mouse_pos.y <= 525) {
            this->_window->close();
            return;
    }
}

void sfml::close()
{
    _window->close();
}

void sfml::refresh()
{
    this->_window->display();
}

void sfml::drawRectangle(int x, int y, int sizex, int sizey, color_t color)
{
    sf::RectangleShape rectangle(sf::Vector2f(sizex, sizey));
    rectangle.setFillColor(sf::Color(color.x, color.y, color.z));
    rectangle.setPosition(sf::Vector2f{static_cast<float>(x), static_cast<float>(y)});
    this->_window->draw(rectangle);
    return;
}

void sfml::drawCircle(int size, int x, int y, color_t color)
{
    sf::CircleShape circle(size);
    circle.setFillColor(sf::Color(color.x, color.y, color.z));
    circle.setPosition(sf::Vector2f{static_cast<float>(x), static_cast<float>(y)});
    this->_window->draw(circle);
    return;
}

void sfml::displaymenu()
{
    sf::Texture menu_t;
    sf::Sprite menu_s;
    menu_t.loadFromFile("./images/menu.png");
    menu_s.setTexture(menu_t);
    this->_window->draw(menu_s);
}

int sfml::getAllInput()
{
    while (_window->pollEvent(_event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            key_value = inputs::SWITCH_LIB_RIGHT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            key_value = inputs::SWITCH_LIB_LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && this->menu == false)
        {
            key_value = inputs::MOVE_UP;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && this->menu == false)
        {
            key_value = inputs::MOVE_LEFT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->menu == false)
        {
            key_value = inputs::MOVE_DOWN;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->menu == false)
        {
            key_value = inputs::MOVE_RIGHT;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && this->menu == false) {
            this->menu = true;
            key_value = inputs::RETURN_MENU;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && this->menu == false) {
            key_value = inputs::RESET_GAME;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && this->menu == false) {
            key_value = inputs::SWITCH_GAME;
        }
        if (this->_event.type == sf::Event::Closed) {
            this->_window->close();
            return 0;
        }
    }
    return key_value;
}

void sfml::getScore(int score_value)
{
    std::string s = std::to_string(score_value);
    this->score.setString("score : " + s);
    this->score.setCharacterSize(24);
    this->score.setFillColor(sf::Color::Yellow);
    this->score.setOrigin(sf::Vector2f{0, 0});
    this->_window->draw(this->score);
}

void sfml::defeat()
{
    if (this->lose) {
        sf::Texture loose_t;
        sf::Sprite loose_s;
        loose_t.loadFromFile("./images/loose.png");
        loose_s.setTexture(loose_t);
        this->_window->draw(loose_s);
        refresh();
    }
}

void sfml::victory()
{
    if (this->win) {
        sf::Texture win_t;
        sf::Sprite win_s;
        win_t.loadFromFile("./images/win.png");
        win_s.setTexture(win_t);
        this->_window->draw(win_s);
        refresh();
    }
}