/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include <iostream>
#include "ecs/engine/World.hpp"
#include "ecs/engine/EntityCommands.hpp"

void ecs::World::update()
{
    _systems.updateStage(*this, INPUT_UPDATE);
    _systems.updateStage(*this, UPDATE);
    _systems.updateStage(*this, RENDER_UPDATE);
    BeginDrawing();
    ClearBackground(SKYBLUE);
    _systems.updateStage(*this, DRAW_WORLD);
    _systems.updateStage(*this, DRAW_HUD);
    EndDrawing();
}

void ecs::World::killAllEntities()
{
    std::deque<Entity> cpy = _livingEntities;

     for (Entity entity : cpy)
        EntityCommands(entity, *this).despawn();
}

ecs::EntityCommands ecs::World::spawn()
{
    Entity entity = _entities.createEntity();

    _livingEntities.push_back(entity);
    return ecs::EntityCommands(entity, *this);
};

ecs::EntityCommands ecs::World::getEntityCommands(Entity entity)
{
    return ecs::EntityCommands(entity, *this);
}
