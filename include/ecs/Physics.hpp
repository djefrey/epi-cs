/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Physics
*/

#pragma once

#include "ecs/System.hpp"
#include "ecs/World.hpp"

struct Transform {
    float x;
    float y;
    float z;

    Transform() : x(0), y(0), z(0) {};
    Transform(float x, float y, float z) : x(x), y(y), z(z) {};
};

struct Velocity {
    float x;
    float y;
    float z;

    Velocity() : x(0), y(0), z(0) {};
    Velocity(float x, float y, float z) : x(x), y(y), z(z) {};
};

class PhysicsSystem : public ecs::ASystem
{
    public:
    PhysicsSystem(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Transform, Velocity>();
    }

    void update(ecs::World &world)
    {
        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            Velocity &velocity = world.getComponent<Velocity>(entity);

            transform.x += velocity.x;
            transform.y += velocity.y;
            transform.z += velocity.z;
        }
    }
};
