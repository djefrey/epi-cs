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
