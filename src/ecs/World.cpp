/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include "ecs/World.hpp"
#include "ecs/EntityCommands.hpp"

std::unique_ptr<ecs::EntityCommands> ecs::World::spawn()
{
    Entity entity = _entities.createEntity();

    return std::unique_ptr<ecs::EntityCommands>(new EntityCommands(entity, *this));
};

std::unique_ptr<ecs::EntityCommands> ecs::World::getEntityCommands(Entity entity)
{
    return std::unique_ptr<ecs::EntityCommands>(new EntityCommands(entity, *this));
}
