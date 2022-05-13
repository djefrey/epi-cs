/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include "ecs/World.hpp"
#include "ecs/Physics.hpp"
#include "ecs/EntityCommands.hpp"

int main()
{
    ecs::World world{};

    world.registerComponents<Transform, Velocity>();
    world.registerSystems<PhysicsSystem>();
    world.spawn()->insert(Transform(), Velocity(1, 1, 1));
    world.update();
}
