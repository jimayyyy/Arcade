/*
** EPITECH PROJECT, 2022
** ncurses
** File description:
** function
*/

#include "ncurses.hpp"

extern "C" IDisplayModule *createGraphLib()
{
    return (new ncurses());
}

ncurses::ncurses()
{
    this->name = "Lib ncurses";
    this->menu = true;
    std::cout << "loading ncurses library\n";
}

void draw_borders(WINDOW *screen)
{
    int x, y, i;
    getmaxyx(screen, y, x);
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1, x - 1, "+");
    for (i = 1; i < (y - 1); i++)
    {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }
    for (i = 1; i < (x - 1); i++)
    {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
    }
}

void ncurses::init()
{
    _isRunning = true;
    score_size = 3;
    print_score = "0";
    lose = false;
    win = false;
    cursor = 0;
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, parent_y, parent_x);
    field = newwin(parent_y - score_size, parent_x, 0, 0);
    score = newwin(score_size, parent_x, parent_y - score_size, 0);
}

void ncurses::getScore(int score_value)
{
    print_score = std::to_string(score_value);
}

void ncurses::defeat()
{
    clear();
    lose = true;
    if (getAllInput() != inputs::RETURN_MENU)
    {
        mvprintw(LINES / 2, COLS / 2 - 11, "You lost");
        refresh();
    }
}

void ncurses::victory()
{
    clear();
    win = true;
    if (getAllInput() != inputs::RETURN_MENU)
    {
        mvprintw(LINES / 2, COLS / 2 - 11, "You win !");
        refresh();
    }
}

void ncurses::refresh()
{
    if (_isRunning == true && lose == false && win == false)
    {
        draw_borders(field);
        draw_borders(score);
        getmaxyx(stdscr, new_y, new_x);
        if (new_y != parent_y || new_x != parent_x)
        {
            parent_x = new_x;
            parent_y = new_y;
            wresize(field, new_y - score_size, new_x);
            wresize(score, score_size, new_x);
            mvwin(score, new_y - score_size, 0);
            wclear(stdscr);
            wclear(field);
            wclear(score);
            draw_borders(field);
            draw_borders(score);
        }
        mvwprintw(score, 1, 1, "Score : ");
        mvwprintw(score, 1, 10, print_score.c_str());
        mvwprintw(score, 1, 20, "Press 'space' to quit");
        wrefresh(field);
        wrefresh(score);
    }
    stop();
}

void ncurses::close()
{
    endwin();
    _isRunning = false;
}

void ncurses::stop()
{
    return;
}

int ncurses::chooseGame()
{
    if (key_value == inputs::ENTER && (cursor == 0 || cursor == 1))
    {
        menu = false;
        print_score = "0";
        if (cursor == 0)
            return games::PACMAN;
        if (cursor == 1)
            return games::NIBBLER;
    }
    return 0;
}

void ncurses::displaymenu()
{
    int ch = getAllInput();

    std::vector<std::string> option = {"Pacman <--", "Nibbler <--", "Quit <--"};
    mvwprintw(field, 1, 1, "Pacman");
    mvwprintw(field, 2, 1, "Nibbler");
    mvwprintw(field, 3, 1, "Quit");
    wrefresh(field);
    if (ch == inputs::MOVE_UP)
    {
        this->setInput(inputs::RESET_INPUT);
        cursor--;
        if (cursor < 0)
            cursor = 0;
    }
    if (ch == inputs::MOVE_DOWN)
    {
        this->setInput(inputs::RESET_INPUT);
        cursor++;
        if (cursor > 2)
            cursor = 2;
    }
    mvwprintw(field, 1, 1, "Pacman     ");
    mvwprintw(field, 2, 1, "Nibbler      ");
    mvwprintw(field, 3, 1, "Quit        ");
    mvwprintw(field, cursor + 1, 1, option[cursor].c_str());
    wrefresh(field);
    if (ch == inputs::ENTER && cursor == 2) {
        close();
    }
    return;
}

void ncurses::drawCircle(int size, int x, int y, color_t color)
{
    int value = (color.x + color.y + color.z) / 3 + 1;
    start_color();
    init_color(COLOR_YELLOW, color.x * 3, color.y * 3, color.z * 3);
    init_pair(value, COLOR_YELLOW, COLOR_BLACK);
    wattron(field, COLOR_PAIR(value));
    mvwprintw(field, y + 1, x + 1, "o");
    wattroff(field, COLOR_PAIR(value));
}

void ncurses::drawRectangle(int x, int y, int sizex, int sizey, color_t color)
{
    x /= 19;
    y /= 37;
    int value = 0;
    if (color.x > color.y && color.x > color.z)
    {
        value = 1;
        init_color(COLOR_RED, color.x * 3, color.y, color.z);
        init_pair(value, COLOR_RED, COLOR_BLACK);
    }
    else if (color.y > color.x && color.y > color.z)
    {
        value = 2;
        init_color(COLOR_GREEN, color.x, color.y * 3, color.z);
        init_pair(value, COLOR_GREEN, COLOR_BLACK);
    }
    else if (color.z > color.x && color.z > color.y)
    {
        value = 3;
        init_color(COLOR_BLUE, color.x, color.y, color.z * 3);
        init_pair(value, COLOR_BLUE, COLOR_BLACK);
    }
    else if (color.z == color.x && color.z == color.y && color.x == 0 && color.y == 0 && color.z == 0)
    {
        value = 4;
        init_color(COLOR_CYAN, color.x * 3, color.y * 3, color.z * 3);
        init_pair(value, COLOR_CYAN, COLOR_BLACK);
    }
    else if (color.x == 0 && color.y == 0 && color.z == 0)
    {
        value = 5;
        init_color(COLOR_BLACK, color.x, color.y, color.z);
        init_pair(value, COLOR_BLACK, COLOR_BLACK);
    }
    else if (color.x == color.y && color.y > color.z)
    {
        value = 6;
        init_color(COLOR_YELLOW, color.x * 3, color.y * 3, color.z);
        init_pair(value, COLOR_YELLOW, COLOR_BLACK);
    }
    start_color();
    wattron(field, COLOR_PAIR(value));
    mvwprintw(field, y + 1, x + 1, "#");
    wattroff(field, COLOR_PAIR(value));
}

int ncurses::getAllInput()
{
    int key = getch();

    if (key == ' ')
    {
        close();
    }
    if (key == 68)
    {
        key_value = inputs::SWITCH_LIB_LEFT;
    }
    if (key == 67)
    {
        key_value = inputs::SWITCH_LIB_RIGHT;
    }
    if (key == 'z')
        key_value = inputs::MOVE_UP;
    if (key == 'q' && this->menu == false)
        key_value = inputs::MOVE_LEFT;
    if (key == 's')
        key_value = inputs::MOVE_DOWN;
    if (key == 'd' && this->menu == false)
        key_value = inputs::MOVE_RIGHT;
    if (key == '\n')
        key_value = inputs::ENTER;
    if (key == 'l' && this->menu == false)
        key_value = inputs::SWITCH_GAME;
    if (key == 'r' && this->menu == false)
        key_value = inputs::RESET_GAME;
    if (key == 'm' && this->menu == false)
    {
        werase(field);
        this->menu = true;
        lose = false;
        win = false;
        key_value = inputs::RETURN_MENU;
    }
    return key_value;
}