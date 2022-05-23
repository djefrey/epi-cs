/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Texture
*/

#pragma once

#include <string>
#include "raylib.h"

namespace raylib {
    using RaylibTexture = ::Texture2D;

    class Texture {
        RaylibTexture _texture;

        public:
        Texture(const std::string &path) : _texture(LoadTexture(path.c_str())) {};
        ~Texture() { UnloadTexture(_texture); };
        Texture(Texture &texture) = delete;
        Texture(Texture &&texture) : _texture(texture._texture) {};

        RaylibTexture &getTexture() { return _texture; };
    };
}
