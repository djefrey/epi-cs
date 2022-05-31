/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "ecs/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"

#include "tests/Physics.hpp"
#include "tests/DrawableCube.hpp"
#include "tests/DrawableModel.hpp"
#include "tests/Hitbox.hpp"
#include "tests/Clickable.hpp"
#include "tests/Hoverable.hpp"
#include "tests/HoverTint.hpp"

// #include "JSONParser.hpp"

void testClick(ecs::World &world, ecs::Entity entity)
{
    puts("CLICK !");
    world.getComponent<Tint>(entity) = RED;
}

int main()
{
    // std::ifstream file("test.json");
    // std::stringstream buf;
    // buf << file.rdbuf();
    // json::JSONParser parser(buf.str());
    // json::JSONObject root = parser.getRoot();

    // std::cout << "Name: " << root.getString("name") << std::endl;

    ecs::World world{};

    world.registerComponents<Transform, Velocity, DrawableCube, Tint, TextureRef, ModelRef, Hitbox, Clickable, Hoverable>();
    world.registerSystems<PhysicsSystem, DrawColorCubeSystem, DrawTextureCubeSystem, DrawableModelSystem, ClickUpdateSystem, HoverUpdateSystem, HoverTintUpdateSystem>();

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 2.0, -1.0}, Vector3 {0.0, 0.0, 4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();

// ---------------------------------

    raylib::TextureManager &textManager = world.getRessource<raylib::TextureManager>();
    raylib::Texture &woodPlanks = textManager.loadTexture("./assets/textures/planks.png");

    raylib::ModelManager &modelManager = world.getRessource<raylib::ModelManager>();
    raylib::Model &testModel = modelManager.loadModel("./assets/models/ecs-test.gltf");
    // testModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, woodPlanks);
    testModel.getMaterialView(1).setTexture(MATERIAL_MAP_DIFFUSE, woodPlanks);
    testModel.getMaterialView(2).setTexture(MATERIAL_MAP_DIFFUSE, woodPlanks);

    // raylib::AnimationManager &animManager = world.getRessource<raylib::AnimationManager>();
    // animManager.loadAnimation("")

// ---------------------------------

    world.spawn().insert(Transform { 0, 0, 2, 0, 0, 0, 0, 1, 1, 1 }, Velocity {0, 0, 0.02}, DrawableCube(Vector3 { 1, 1, 1 }), RED);
    world.spawn().insert(Transform { 1, 1, 2, 0, 0, 0, 0, 1, 1, 1 }, Velocity {0, 0, 0.1}, DrawableCube(Vector3 { 1, 1, 1 }), GREEN);
    world.spawn().insert(Transform { -1, -1, 2, 0, 0, 0, 0, 1, 1, 1 }, Velocity {0, 0.01, 0}, DrawableCube(Vector3 { 1, 0.5, 1 }), TextureRef { &woodPlanks });
    world.spawn().insert(Transform { 1, 1, 2, 0, 0, 0, 0, 1, 1, 1 }, Velocity {0, 0, 0.02}, ModelRef { &testModel });

    world.spawn().insert(Transform { 0, 2, 1, 0, 0, 0, 0, 1, 1, 1 }, DrawableCube { Vector3 {0.3, 0.3, 0.3} }, GREEN, Hitbox {{-0.15, -0.15, -0.15}, {0.15, 0.15, 0.15}}, Clickable {testClick}, Hoverable{});

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    while (!window.shouldClose())
        world.update();
}
