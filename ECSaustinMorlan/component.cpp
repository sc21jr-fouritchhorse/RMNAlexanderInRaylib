//
// Created by qiaojun on 10/02/24.
//
#include "components.h"


template <typename T>
void ComponentArray<T>::InsertData(Entity e, T component)
{
    static_assert(mEnt2Ind.find(e) == mEnt2Ind.end() && "Already added this component to the entitiy");

    size_t newIndex = mNumAvailableInds;
    mEnt2Ind[e] = newIndex;


    mInd2Ent[newIndex] = e;
    mComponentArray[newIndex] = component;
    ++mNumAvailableInds;
}

template <typename T>
void ComponentArray<T>::RemoveData(Entity e)
{
    static_assert(mEnt2Ind.find(e) == mEnt2Ind.end() && "Removing component that doesn't exist");

    size_t e_i = mEnt2Ind[e];
    size_t last_i = mNumAvailableInds - 1;
    mComponentArray[e_i] = mComponentArray[e_i];

    Entity last_e = mInd2Ent[last_i];
    mEnt2Ind[last_e] = e_i;
    mEnt2Ind[e_i] = last_e;

    mEnt2Ind.erase(e);
    mInd2Ent.erase(last_e);

    --mNumAvailableInds;
}

template <typename T>
T& ComponentArray<T>::GetData(Entity e)
{
    static_assert(mEnt2Ind.find(e) != mEnt2Ind.end() && "Retrieving non-existent component.");
    return mComponentArray[mEnt2Ind[e]];
}

template <typename T>
void ComponentArray<T>::EntityDestroyed(Entity e)
{
    if(mEnt2Ind.find(e) != mEnt2Ind.end())
        RemoveData(e);
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
