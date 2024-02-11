//
// Created by qiaojun on 11/02/24.
//

#include "componentManager.h"



template <typename T>
void ComponentManager::EntityDestroyed(Entity e) const
{
    for (auto const& pair : mComponentArrays)
    {
        auto const& component = pair.second;

        component->EntityDestroyed(e);
    }
}


template <typename T>
void ComponentManager::RegisterComponent()
{
    const char* typeName = typeid(T).name();
    assert(mComponentTypes.find(typeName) == mComponentTypes.end() &&
        "Registering a previously registered compoent type");
    mComponentTypes.insert({typeName, std::make_shared<ComponentArray<T>>()});
    mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    ++mNextComponentType;
}

template <typename T>
ComponentType ComponentManager::GetComponentType()
{
    const char* typeName = typeid(T).name();
    assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
        "Referencing compoenent before use");
    return mComponentTypes[typeName];
}


template <typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
    const char* typeName = typeid(T).name();
    assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
        "Component array used before registration");
    return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
}
