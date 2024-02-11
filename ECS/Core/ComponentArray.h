#pragma once
#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <array>
#include <cassert>
#include <unordered_map>

#include "../ecsDefinitions.h"


class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray
{
public:
    void InsertData(Entity entity, T component);
    void RemoveData(Entity entity);
    T& GetData(Entity entity);
    void EntityDestroyed(Entity entity);

private:
    std::array<T, MAX_ENTITIES> m_ComponentArray;
    std::unordered_map<Entity, size_t> m_EntityToIndexMap;
    std::unordered_map<size_t, Entity> m_IndexToEntityMap;
    size_t m_Size = 0;
};

#endif // COMPONENT_ARRAY_H


