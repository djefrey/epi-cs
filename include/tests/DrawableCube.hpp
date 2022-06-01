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
#include "raylib/rlgl.h"
#include "raylib/Matrix.hpp"
#include "ColorTexture.hpp"

struct DrawableCube {
    public:
    DrawableCube() {};

    void renderColor(Transform &transform, Color &color)
    {
        DrawCube(transform.translation, transform.scale.x, transform.scale.y, transform.scale.z, color);
    }

    void renderTexture(Transform &transform, raylib::Texture &texture)
    {
        DrawCubeTexture(texture.getTexture(), transform.translation, transform.scale.x, transform.scale.y, transform.scale.z, WHITE);
    }
};

class DrawColorCubeSystem : public ecs::ASystem {
    public:
    DrawColorCubeSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

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

            rlPushMatrix();
            rlMultMatrixf(MatrixToFloatV(raylib::Matrix::fromQuaternion(transform.rotation).getMatrix()).v);
            cube.renderColor(transform, tint);
            rlPopMatrix();
        }
        camera.end3DMode();
    }
};

class DrawTextureCubeSystem : public ecs::ASystem {
    public:
    DrawTextureCubeSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

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

            cube.renderTexture(transform, *textRef.texture);
        }
        camera.end3DMode();
    }
};
