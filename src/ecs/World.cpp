/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include <iostream>
#include "ecs/World.hpp"
#include "ecs/EntityCommands.hpp"

std::unique_ptr<ecs::EntityCommands> ecs::World::spawn()
{
    Entity entity = _entities.createEntity();

    return std::make_unique<ecs::EntityCommands>(entity, *this);
};

std::unique_ptr<ecs::EntityCommands> ecs::World::getEntityCommands(Entity entity)
{
    return std::make_unique<ecs::EntityCommands>(entity, *this);
}
