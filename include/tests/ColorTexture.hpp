/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** ColorTexture
*/

#pragma once

#include "raylib.h"
#include "raylib/Texture.hpp"

using Tint = ::Color;

struct TextureRef {
    raylib::Texture *texture;

    TextureRef(raylib::Texture *texture = nullptr) : texture(texture) {};
};
