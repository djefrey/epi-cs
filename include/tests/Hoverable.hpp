/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hoverable
*/

#pragma once

#include "ecs/Entity.hpp"
#include "ecs/World.hpp"
#include "ecs/System.hpp"

#include "raylib/Window.hpp"
#include "raylib/Camera.hpp"
#include "Hitbox.hpp"

struct Hoverable {
    bool isHover;
    bool updated;

    Hoverable() : isHover(false), updated(false) {};
};

class HoverUpdateSystem : public ecs::ASystem {
    public:
    HoverUpdateSystem()
    {
        _stage = ecs::Stages::INPUT_UPDATE;
    };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, Hoverable, Hitbox>();
    }

    void update(ecs::World &world)
    {
        raylib::Window &window = world.getRessource<raylib::Window>();
        raylib::Camera &cam = world.getRessource<raylib::Camera>();
        raylib::Ray ray = cam.getMouseRay(window.getMousePos());

        Hoverable *hitHover = nullptr;
        float hitDist = MAXFLOAT;
        ecs::Entity hitEntity;

        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Hitbox &hitbox = world.getComponent<Hitbox>(entity);
            Hoverable &hover = world.getComponent<Hoverable>(entity);

            BoundingBox box = hitbox.getBoundingBox(transform);
            RayCollision collision = ray.getCollisionBox(box);

            hover.updated = hover.isHover != false;
            hover.isHover = false;
            if (collision.hit && collision.distance < hitDist) {
                hitHover = &hover;
                hitDist = collision.distance;
                hitEntity = entity;
            }
        }

        if (hitHover) {
            hitHover->isHover = true;
            hitHover->updated = !hitHover->updated;
        }
    }
};
