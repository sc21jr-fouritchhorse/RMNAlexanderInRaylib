//
// Created by qiaojun on 10/02/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "ECSDefs.h"


//I stands for Inheritied??
class IComponentArray
{
public:
    virtual ~IComponentArray() =default;
    virtual void EntityDestroyed(Entity e) = 0;
};
template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void InsertData(Entity e, T component);
    void RemoveData(Entity e);
    T& GetData(Entity e);
    void EntityDestroyed(Entity e) override;
private:
    std::array<T, MAX_ENTITIES> mComponentArray;
    std::unordered_map<Entity, size_t> mEnt2Ind;
    std::unordered_map<size_t, Entity> mInd2Ent;
    size_t mNumAvailableInds{};
};
class ComponentManager
{
public:
    template<typename T> void RegisterComponent();
    template<typename T> ComponentType GetComponentType();
    template<typename T>
    void AddComponent(Entity e, T compoenent);
    template<typename T>
    void RemoveComponent(Entity e);
    template<typename T>
    T& GetComponent(Entity e);
    void EntitiyDestroyed(Entity e);
private:
    std::unordered_map<const char*, ComponentType> mComponentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
    ComponentType mNextComponentType{};
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();
};


#endif //COMPONENTS_H
