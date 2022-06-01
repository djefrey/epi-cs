/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Clickable
*/

#pragma once

#include "ecs/Entity.hpp"
#include "ecs/World.hpp"
#include "ecs/System.hpp"

#include "raylib/Window.hpp"
#include "raylib/Camera.hpp"

#include "2D.hpp"
#include "Hitbox.hpp"

using ClickCallbackFct = void (*)(ecs::World &world, ecs::Entity entity);

struct Clickable {
    ClickCallbackFct callback;

    Clickable() : callback(nullptr) {};
    Clickable(ClickCallbackFct callback) : callback(callback) {};
};

class ClickUpdateSystem : public ecs::ASystem {
    public:
    ClickUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, Clickable, Hitbox>();
    }

    void update(ecs::World &world)
    {
        raylib::Window &window = world.getRessource<raylib::Window>();

        if (!window.isMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return;

        raylib::Camera &cam = world.getRessource<raylib::Camera>();
        raylib::Ray ray = cam.getMouseRay(window.getMousePos());

        Clickable *hitClick = nullptr;
        float hitDist = MAXFLOAT;
        ecs::Entity hitEntity;

        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Hitbox &hitbox = world.getComponent<Hitbox>(entity);
            BoundingBox box = hitbox.getBoundingBox(transform);
            RayCollision collision = ray.getCollisionBox(box);

            if (collision.hit && collision.distance < hitDist) {
                hitClick = &world.getComponent<Clickable>(entity);
                hitDist = collision.distance;
                hitEntity = entity;
            }
        }

        if (hitClick)
            hitClick->callback(world, hitEntity);
    }
};

class Click2DUpdateSystem : public ecs::ASystem {
    public:
    Click2DUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Position2D, Clickable, Hitbox2D>();
    }

    void update(ecs::World &world)
    {
        raylib::Window &window = world.getRessource<raylib::Window>();

        if (!window.isMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return;

        Vector2 mousePos = window.getMousePos();

        for (ecs::Entity entity : _entities) {
            Position2D &pos = world.getComponent<Position2D>(entity);
            Hitbox2D &hitbox = world.getComponent<Hitbox2D>(entity);

            if (mousePos.x >= pos.x && mousePos.x <= pos.x + hitbox.width
            && mousePos.y >= pos.y && mousePos.y <= pos.y + hitbox.height) {
                world.getComponent<Clickable>(entity).callback(world, entity);
                return;
            }
        }
    }
};
