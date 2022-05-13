/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include "ecs/EntityCommands.hpp"

#include "tests/Physics.hpp"
#include "tests/Camera.hpp"
#include "tests/DrawableCube.hpp"

int main()
{
    ecs::World world{};

    world.registerComponents<Transform, Velocity, DrawableCube>();
    world.registerSystems<PhysicsSystem, DrawCubeSystem>();
    world.getRessourceManager().insertRessource<raylib::Camera>();
    world.spawn()->insert(Transform { 0, 0, 3 }, Velocity(1, 1, 1), DrawableCube(Vector3 { 1, 1, 1 }, GREEN));

    InitWindow(640, 480, "Epitech Coding Style");
    SetTargetFPS(60);

    while (!WindowShouldClose())
        world.update();
}
