/*
** EPITECH PROJECT, 2022
** $
** File description:
** DrawableMesh
*/

#pragma once

#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "raylib/Model.hpp"

struct ModelRef {
    raylib::Model *model;

    ModelRef(raylib::Model *model = nullptr) : model(model) {};
};

class DrawableModelSystem : public ecs::ASystem {
    public:
    DrawableModelSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, ModelRef>();
    }

    void update(ecs::World &world)
    {
        raylib::Camera &camera = world.getRessource<raylib::Camera>();

        camera.begin3DMode();
        for (auto entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            ModelRef &modelRef = world.getComponent<ModelRef>(entity);

            DrawModel(modelRef.model->getModel(), transform.translation, 1.0, WHITE);
        }
        camera.end3DMode();
    }
};
