/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#pragma once

#include <memory>
#include "EntityManager.hpp"
#include "Component.hpp"
#include "System.hpp"

namespace ecs {
    class EntityCommands;

    class World {
        EntityManager _entities;
        ComponentManager _components;
        SystemManager _systems;

        public:
        World() = default;
        ~World() = default;

        EntityManager &getEntityManager() { return _entities; };
        ComponentManager &getComponentManager() { return _components; };
        SystemManager &getSystemManager() { return _systems; };

        std::unique_ptr<EntityCommands> spawn();
        std::unique_ptr<EntityCommands> getEntityCommands(Entity entity);

        void update() { _systems.updateSystems(*this); };

        template<typename T>
        T &getComponent(Entity entity)
        {
            return _components.getComponent<T>(entity);
        }

        template<typename T>
        void registerComponent()
        {
            _components.registerComponent<T>();
        }

        template<typename ...Ts>
        void registerComponents()
        {
            (_components.registerComponent<Ts>(), ...);
        }


        template<typename T>
        void registerSystem()
        {
            _systems.registerSystem<T>(_components);
        }

        template<typename ...Ts>
        void registerSystems()
        {
            (_systems.registerSystem<Ts>(_components), ...);
        }
    };
}
