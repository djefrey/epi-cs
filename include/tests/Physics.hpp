/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Physics
*/

#pragma once

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "raylib/raylib.h"

struct Velocity {
    float x;
    float y;
    float z;

    Velocity() : x(0), y(0), z(0) {};
    Velocity(float x, float y, float z) : x(x), y(y), z(z) {};
};

class PhysicsSystem : public ecs::ASystem{
    public:
    PhysicsSystem() { _stage = ecs::Stages::UPDATE; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, Velocity>();
    }

    void update(ecs::World &world)
    {
        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Velocity &velocity = world.getComponent<Velocity>(entity);

            transform.translation.x += velocity.x;
            transform.translation.y += velocity.y;
            transform.translation.z += velocity.z;
        }
    }
};
