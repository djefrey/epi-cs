/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** System
*/

#pragma once

#include <set>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"

namespace ecs {
    class World;

    class ASystem {
        protected:
        std::set<Entity> _entities;
        Signature _signature;

        public:
        void addEntity(Entity entity) { _entities.insert(entity); };
        void removeEntity(Entity entity) { _entities.erase(entity); };

        virtual void setSignature(ComponentManager &component) = 0;
        virtual void update(World &world) = 0;

        const Signature &getSignature() { return _signature; };

        protected:
    };

    class SystemAlreadyExists {};

    class SystemManager {
        using SystemHash = std::size_t;

        std::map<SystemHash, std::unique_ptr<ASystem>> _systems;

        public:
        template<class T>
        void registerSystem(ComponentManager &component)
        {
            std::unique_ptr<ASystem> system = std::make_unique<T>();
            SystemHash hash = typeid(system).hash_code();

            if (_systems.find(hash) != _systems.end())
                throw SystemAlreadyExists();
            system->setSignature(component);
            _systems[hash] = std::move(system);
        }

        void updateSystems(World &world)
        {
            for (auto &pair : _systems)
                pair.second->update(world);
        }

        void updateEntitySignature(Entity entity, Signature &signature)
        {
            for (auto &pair : _systems) {
                const Signature &systemSig = pair.second->getSignature();

                if ((systemSig & signature) == systemSig)
                    pair.second->addEntity(entity);
                else
                    pair.second->removeEntity(entity);
            }
        }

        void removeEntity(Entity entity)
        {
            for (auto &pair : _systems)
                pair.second->removeEntity(entity);
        }
    };
}
