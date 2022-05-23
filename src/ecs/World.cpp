/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include <iostream>
#include "ecs/World.hpp"
#include "ecs/EntityCommands.hpp"

void ecs::World::update()
{
    ClearBackground(SKYBLUE);
    _systems.updateStage(*this, UPDATE);
    BeginDrawing();
    _systems.updateStage(*this, DRAW);
    EndDrawing();
}

void ecs::World::killAllEntities()
{
    std::deque<Entity> cpy = _livingEntities;

     for (Entity entity : cpy)
        EntityCommands(entity, *this).despawn();
}

std::unique_ptr<ecs::EntityCommands> ecs::World::spawn()
{
    Entity entity = _entities.createEntity();

    _livingEntities.push_back(entity);
    return std::make_unique<ecs::EntityCommands>(entity, *this);
};

std::unique_ptr<ecs::EntityCommands> ecs::World::getEntityCommands(Entity entity)
{
    return std::make_unique<ecs::EntityCommands>(entity, *this);
}
