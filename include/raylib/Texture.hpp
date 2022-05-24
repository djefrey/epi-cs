/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Texture
*/

#pragma once

#include <string>
#include <stdexcept>
#include "raylib.h"

namespace raylib {
    using RaylibTexture = ::Texture2D;

    class Texture {
        RaylibTexture _texture;

        public:
        Texture(const std::string &path) : _texture(LoadTexture(path.c_str()))
        {
            if (_texture.width == 0 || _texture.height == 0)
                throw std::runtime_error("Could not load texture " + path);
            SetTextureFilter(_texture, TEXTURE_FILTER_ANISOTROPIC_16X);
            SetTextureWrap(_texture, TEXTURE_WRAP_CLAMP);
        };
        ~Texture() { UnloadTexture(_texture); };
        Texture(Texture &texture) = delete;
        Texture(Texture &&texture) : _texture(texture._texture) { texture._texture = { 0 }; };

        RaylibTexture &getTexture() { return _texture; };
    };
}
