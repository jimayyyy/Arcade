/*
** EPITECH PROJECT, 2022
** main
** File description:
** arcade
*/

#include "Core.hpp"
#include "DLLoader.hpp"
#include <unistd.h>
#include <experimental/filesystem>

void core_setup(ADisplayModule *lib, Core core, char *path)
{
    core._lib.push_back(lib);
    core.ActualLib = lib;
    bool execDLLoader = true;

    for (const auto &file : std::experimental::filesystem::directory_iterator("lib/")) {
        std::string test = std::string(file.path());
        if (test.compare(std::string(path)) != 0) {
            DLLoader<ADisplayModule *()> load(file.path());
            auto p = load.getInstance("createGraphLib");
            if (p == nullptr) {
                DLLoader<AGamesModule *()> load(file.path());
                auto p = load.getInstance("createGameLib");
                core._games.push_back(p());
            } else {
                lib = p();
                core._lib.push_back(lib);
            }
        }
    }
    core.run();
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << ".so is needed as second arg" << std::endl;
        return 84;
    }
    Core core;
    DLLoader<ADisplayModule *()> load(av[1]);
    auto p = load.getInstance("createGraphLib");
    if (p == NULL) {
        std::cout << "Not a graphic librarie !" << std::endl;
        return 84;
    }
    ADisplayModule *lib = p();
    core_setup(lib, core, av[1]);
    return 0;
}