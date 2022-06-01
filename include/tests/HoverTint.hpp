/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** HoverTint
*/

#pragma once

#include "ecs/World.hpp"
#include "ecs/System.hpp"

#include "Hoverable.hpp"

using Tint = ::Color;

class HoverTintUpdateSystem : public ecs::ASystem {
    public:
    HoverTintUpdateSystem() { _stage = ecs::Stages::RENDER_UPDATE; };

    void setSignature(ecs::ComponentManager &component)
    {
        _signature = component.generateSignature<Tint, Hoverable>();
    }

    void update(ecs::World &world)
    {
        for (ecs::Entity entity : _entities) {
            Hoverable &hover = world.getComponent<Hoverable>(entity);

            if (!hover.updated)
                continue;
            if (hover.isHover)
                world.getComponent<Tint>(entity) = YELLOW;
            else
                world.getComponent<Tint>(entity) = GREEN;
        }
    }
};
