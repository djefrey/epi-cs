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
#include "Ressources.hpp"
#include "raylib/raylib.h"

namespace ecs {
    class EntityCommands;

    class World {
        EntityManager _entities;
        ComponentManager _components;
        SystemManager _systems;
        RessourcesManager _ressources;
        std::deque<Entity> _livingEntities;

        public:
        World() = default;
        ~World() = default;

        EntityManager &getEntityManager() { return _entities; };
        ComponentManager &getComponentManager() { return _components; };
        SystemManager &getSystemManager() { return _systems; };
        RessourcesManager &getRessourceManager() { return _ressources; };

        void update();
        void killAllEntities();

        std::unique_ptr<EntityCommands> spawn();
        std::unique_ptr<EntityCommands> getEntityCommands(Entity entity);

        template<typename T>
        T &getComponent(Entity entity)
        {
            return _components.getComponent<T>(entity);
        }

        template<typename T>
        T &getRessource()
        {
            return _ressources.getRessource<T>();
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

        std::deque<Entity> &getLivingEntities()
        {
            return _livingEntities;
        }
    };
}
