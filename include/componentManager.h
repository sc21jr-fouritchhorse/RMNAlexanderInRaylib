//
// Created by qiaojun on 11/02/24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "components.h"

class ComponentManager
{
public:
    template <class T>
    void EntityDestroyed(Entity e) const;
    template<typename T> void RegisterComponent();
    template<typename T> ComponentType GetComponentType();
    template<typename T>
    void AddComponent(Entity e, T compoenent);
    template<typename T>
    void RemoveComponent(Entity e);
    template<typename T>
    T& GetComponent(Entity e);
    void EntityDestroyed(Entity e) const;

private:
    std::unordered_map<const char*, ComponentType> mComponentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
    ComponentType mNextComponentType{};
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();
};



#endif //COMPONENTMANAGER_H
