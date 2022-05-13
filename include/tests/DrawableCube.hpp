/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawableCube
*/

#pragma once

#include "Camera.hpp"
#include "ecs/World.hpp"
#include "ecs/System.hpp"
#include "raylib/raylib.h"

struct DrawableCube {
    Vector3 _size;
    Color _color;

    public:
    DrawableCube() : _size(Vector3 {1, 1, 1}), _color(RED) {};
    DrawableCube(Vector3 size, Color color) : _size(size), _color(color) {};

    void render(Vector3 pos)
    {
        DrawCube(pos, _size.x, _size.y, _size.z, _color);
    }
};

class DrawCubeSystem : public ecs::ASystem {
    public:
    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, DrawableCube>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &camera = world.getRessource<raylib::Camera>();

        camera.begin3DMode();
        for (auto entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            DrawableCube &cube = world.getComponent<DrawableCube>(entity);

            std::cout << "Draw cube ! " << std::endl;

            cube.render(Vector3 { 0, 0, -1 });
        }
        camera.end3DMode();
    }
};