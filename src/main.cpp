/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include "ecs/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "tests/Physics.hpp"
#include "tests/DrawableCube.hpp"

int main()
{
    ecs::World world{};

    world.registerComponents<Transform, Velocity, DrawableCube>();
    world.registerSystems<PhysicsSystem, DrawCubeSystem>();
    world.getRessourceManager().insertRessource<raylib::Camera>();
    world.spawn()->insert(Transform { 0, 0, 2 }, Velocity {0, 0, 0.02}, DrawableCube(Vector3 { 1, 1, 1 }, GREEN));
    world.spawn()->insert(Transform { 1, 1, 2 }, Velocity {0, 0, 0.1}, DrawableCube(Vector3 { 1, 1, 1 }, RED));
    world.spawn()->insert(Transform { -1, -1, 2 }, Velocity {0, 0.01, 0}, DrawableCube(Vector3 { 1, 0.5, 1 }, YELLOW));

    InitWindow(640, 480, "Epitech Coding Style");
    SetTargetFPS(60);

    while (!WindowShouldClose())
        world.update();
}
