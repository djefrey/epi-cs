/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include "ecs/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"

#include "tests/Physics.hpp"
#include "tests/DrawableCube.hpp"

int main()
{
    ecs::World world{};

    world.registerComponents<Transform, Velocity, DrawableCube>();
    world.registerSystems<PhysicsSystem, DrawCubeSystem>();

    world.getRessourceManager().insertRessource<raylib::Window>();
    world.getRessourceManager().insertRessource<raylib::Camera>();
    world.getRessourceManager().insertRessource<raylib::TextureManager>();
    world.getRessourceManager().insertRessource<raylib::ModelManager>();
    world.getRessourceManager().insertRessource<raylib::AnimationManager>();

// ---------------------------------

    world.spawn().insert(Transform { 0, 0, 2 }, Velocity {0, 0, 0.02}, DrawableCube(Vector3 { 1, 1, 1 }, GREEN));
    world.spawn().insert(Transform { 1, 1, 2 }, Velocity {0, 0, 0.1}, DrawableCube(Vector3 { 1, 1, 1 }, RED));
    world.spawn().insert(Transform { -1, -1, 2 }, Velocity {0, 0.01, 0}, DrawableCube(Vector3 { 1, 0.5, 1 }, YELLOW));

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    while (!window.shouldClose())
        world.update();
}
