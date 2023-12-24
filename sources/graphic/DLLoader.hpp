/*
** EPITECH PROJECT, 2022
** DLLoader
** File description:
** header
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include "./sfml/sfml.hpp"
#include "IDisplayModule.hpp"
#include <iostream>
#include <dlfcn.h>
#include <functional>

template <typename T>
class DLLoader {
public:
    DLLoader(const std::string &path)
    {
        void *lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!lib) {
            this->lib = nullptr;
            return;
        }
        this->lib = lib;
    };
    std::function<T> getInstance(const std::string &name)
    {
        T *p = NULL;
        p = (T*)(dlsym(this->lib, name.c_str()));
        if (!p)
            return nullptr;
        return std::function<T>(p);
    };
private:
    void *lib;
};

#endif /* !DLLOADER_HPP_ */
