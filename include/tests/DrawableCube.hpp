/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawableCube
*/

#pragma once

#include "ecs/World.hpp"
#include "ecs/System.hpp"
#include "raylib/Camera.hpp"
#include "raylib/Texture.hpp"
#include "raylib/raylib.h"

using Tint = ::Color;

struct TextureRef {
    raylib::Texture *texture;

    TextureRef(raylib::Texture *texture = nullptr) : texture(texture) {};
};

struct DrawableCube {
    Vector3 _size;

    public:
    DrawableCube(Vector3 size = {1, 1, 1}) : _size(size) {};

    void renderColor(Vector3 &pos, Color &color)
    {
        DrawCube(pos, _size.x, _size.y, _size.z, color);
    }

    void renderTexture(Vector3 &pos, raylib::Texture &texture)
    {
        DrawCubeTexture(texture.getTexture(), pos, _size.x, _size.y, _size.z, WHITE);
    }
};

class DrawColorCubeSystem : public ecs::ASystem {
    public:
    DrawColorCubeSystem() : ecs::ASystem() { _stage = ecs::DRAW; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, DrawableCube, Tint>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &camera = world.getRessource<raylib::Camera>();

        camera.begin3DMode();
        for (auto entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            DrawableCube &cube = world.getComponent<DrawableCube>(entity);
            Tint &tint = world.getComponent<Tint>(entity);

            cube.renderColor(transform.translation, tint);
        }
        camera.end3DMode();
    }
};

class DrawTextureCubeSystem : public ecs::ASystem {
    public:
    DrawTextureCubeSystem() : ecs::ASystem() { _stage = ecs::DRAW; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, DrawableCube, TextureRef>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &camera = world.getRessource<raylib::Camera>();

        camera.begin3DMode();
        for (auto entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            DrawableCube &cube = world.getComponent<DrawableCube>(entity);
            TextureRef &textRef = world.getComponent<TextureRef>(entity);

            cube.renderTexture(transform.translation, *textRef.texture);
        }
        camera.end3DMode();
    }
};
