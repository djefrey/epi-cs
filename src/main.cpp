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

    world.registerComponents<Transform, Velocity, DrawableCube, Tint, TextureRef>();
    world.registerSystems<PhysicsSystem, DrawColorCubeSystem, DrawTextureCubeSystem>();

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 2.0, -1.0}, Vector3 {0.0, 0.0, 4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();

// ---------------------------------

    raylib::TextureManager &textManager = world.getRessource<raylib::TextureManager>();
    raylib::Texture &woodPlanks = textManager.loadTexture("./assets/textures/planks.png");

// ---------------------------------

    world.spawn().insert(Transform { 0, 0, 2 }, Velocity {0, 0, 0.02}, DrawableCube(Vector3 { 1, 1, 1 }), RED);
    world.spawn().insert(Transform { 1, 1, 2 }, Velocity {0, 0, 0.1}, DrawableCube(Vector3 { 1, 1, 1 }), GREEN);
    world.spawn().insert(Transform { -1, -1, 2 }, Velocity {0, 0.01, 0}, DrawableCube(Vector3 { 1, 0.5, 1 }), TextureRef { &woodPlanks });

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    while (!window.shouldClose())
        world.update();
}
