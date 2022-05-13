/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include "ecs/World.hpp"
#include "ecs/EntityCommands.hpp"

#include "tests/Physics.hpp"
#include "tests/TestRessources.hpp"

int main()
{
    ecs::World world{};

    world.registerComponents<Transform, Velocity>();
    world.registerSystems<PhysicsSystem>();
    world.getRessourceManager().insertRessource<TestRessource>(42);
    world.spawn()->insert(Transform(), Velocity(1, 1, 1));
    world.update();

    std::cout << world.getRessource<TestRessource>().test << std::endl;
}
